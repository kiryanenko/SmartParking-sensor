#include "RadioModule.h"


RadioModule::RadioModule(const int pinResetLora)
{
	m_pinResetLora = pinResetLora;
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
		return true;
	}
	return false;
}

bool RadioModule::send(const byte *data, size_t size)
{
	if (!m_rf95.available()) {
		Serial.println("[ERROR] RF95 is not available");
		return false;
	}

	m_rf95.send(data, size);
	const auto isSend = m_rf95.waitPacketSent();

	if (!isSend) {
		Serial.println("[ERROR] RF95 not send data");
	}

	return isSend;
}

void RadioModule::reset() const
{
	digitalWrite(m_pinResetLora, LOW);
	delay(1000);
	digitalWrite(m_pinResetLora, HIGH);
}
