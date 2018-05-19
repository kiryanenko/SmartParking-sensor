#include "RadioModule.h"


RadioModule::RadioModule(const int pinResetLora, const int timeout, AbstractReceiveMessageHandler *handler) :
	Driver(handler)
{
	m_pinResetLora = pinResetLora;
	m_timeout = timeout;
}


RadioModule::~RadioModule()
{
}


bool RadioModule::init()
{
	pinMode(m_pinResetLora, OUTPUT);
	// reset lora module first. to make sure it will works properly
	reset();

	if (m_rf95.init()) {
		m_rf95.setFrequency(FREQUENCY);
		m_rf95.setTxPower(14, false);
		m_rf95.setPromiscuous(true);
		return true;
	}
	return false;
}


bool RadioModule::send(const byte *data, size_t size)
{
#ifdef DEBUG
	Serial.print(F("[DEBUG] SEND DATA: "));
	for (int i = 0; i < size; ++i) {
		Serial.print(data[i]);
		Serial.print(' ');
	}
	Serial.println();
#endif

	m_rf95.send(data, size);
	const auto isSend = m_rf95.waitPacketSent(m_timeout);

	if (!isSend) {
#ifdef DEBUG
		Serial.println(F("[ERROR] RF95 not send data"));
#endif
		reset();
	}

	return isSend;
}


bool RadioModule::available()
{
	return m_rf95.available();
}


byte* RadioModule::recv(size_t &size)
{
	uint8_t *buf = new uint8_t[RH_RF95_MAX_MESSAGE_LEN];
	uint8_t len = sizeof(buf);
	if (!m_rf95.recv(buf, &len)) {
		delete[] buf;
		size = 0;
		return NULL;
	}
	size = len;
	return buf;
}


void RadioModule::reset() const
{
	digitalWrite(m_pinResetLora, LOW);
	delay(1000);
	digitalWrite(m_pinResetLora, HIGH);
}
