#include "RadioModule.h"


RadioModule::RadioModule(const int pinResetLora, const int timeout)
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
		return m_rf95.setFrequency(FREQUENCY);
	}
	return false;
}

bool RadioModule::send(const byte *data, size_t size)
{
	m_rf95.send(data, size);
	const auto isSend = m_rf95.waitPacketSent(m_timeout);

	if (!isSend) {
		Serial.println("[ERROR] RF95 not send data");
		reset();
	}

	return isSend;
}

void RadioModule::reset() const
{
	digitalWrite(m_pinResetLora, LOW);
	delay(1000);
	digitalWrite(m_pinResetLora, HIGH);
}
