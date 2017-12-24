#pragma once

#include <Arduino-EEPROMEx\EEPROMex.h>

#define PARKING_PLACES_COUNT 1
#define PIN_RESET_LORA 9
#define PIN_INT_SONAR 3

#define KEYPAD_I2C_ADDR 0x20
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define DEBUG( msg ) Serial.print("[DEBUG] "); Serial.println( ( msg ) );


class Parameters
{
	uint32_t m_id; // Идентификатор устройства
	uint16_t m_sensorSamplingPeriod; // Период опроса датчиков
	uint16_t m_sendingPeriod; // Период отправки сообщений

	const int adress_id = 0;
	const int adress_sensor_sampling_period = adress_id + sizeof(m_id);
	const int adress_sending_period = adress_id + sizeof(m_id) + sizeof(m_sensorSamplingPeriod);

public:
	static Parameters& instance();

	uint32_t getId() const;
	uint16_t getSensorSamplingPeriod() const;
	uint16_t getSendingPeriod() const;

	void setId(uint32_t id);
	void setSendingPeriod(uint16_t sendingPeriod);
	void setSensorSamplingPeriod(uint16_t samplingPeriod);

private:
	Parameters();
	Parameters(const Parameters& root);
	Parameters& operator=(const Parameters&);
};
