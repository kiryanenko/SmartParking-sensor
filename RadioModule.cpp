#include "RadioModule.h"


RadioModule::RadioModule()
{
}


RadioModule::~RadioModule()
{
}

bool RadioModule::init()
{
	if (m_rf95.init()) {
		m_rf95.setFrequency(FREQUENCY);
		return true;
	}
	return false;
}

bool RadioModule::send(const byte data[])
{
	if (!m_rf95.available()) {
		Serial.println("[ERROR] RF95 is not available");
		return false;
	}

	m_rf95.send(data, sizeof(data));
	const auto isSend = m_rf95.waitPacketSent();

	if (!isSend) {
		Serial.println("[ERROR] RF95 not send data");
	}

	return isSend;
}