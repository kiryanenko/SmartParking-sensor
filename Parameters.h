#pragma once
#include <Arduino-EEPROMEx\EEPROMex.h>

class Parameters
{
	uint32_t m_id = 0;							// Идентификатор устройства
	uint16_t m_sensorSamplingPeriod = 500;		// Период опроса датчиков
	uint16_t m_sendingPeriod = 2000;			// Период отправки сообщений

	const int adress_id = 0;
	const int adress_sensor_sampling_period = adress_id + sizeof(m_id);
	const int adress_sending_period = adress_id + sizeof(m_id) + sizeof(m_sensorSamplingPeriod);

public:
	Parameters();
	~Parameters();

	uint32_t getId() const;
	uint16_t getSensorSamplingPeriod() const;
	uint16_t getSendingPeriod() const;

	void setId(uint32_t id);
	void setSendingPeriod(uint16_t sendingPeriod);
	void setSensorSamplingPeriod(uint16_t samplingPeriod);
};
