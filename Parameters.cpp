#include "Parameters.h"

Parameters::Parameters()
{
	m_id = EEPROM.readLong(adress_id);
	m_sendingPeriod = EEPROM.readInt(adress_sending_period);
	m_sensorSamplingPeriod = EEPROM.readInt(adress_sensor_sampling_period);
}


Parameters& Parameters::instance()
{
	static Parameters theSingleInstance;
	return theSingleInstance;
}


uint32_t Parameters::getId() const
{
	return m_id;
}


uint16_t Parameters::getSensorSamplingPeriod() const
{
	return m_sensorSamplingPeriod;
}

uint16_t Parameters::getSendingPeriod() const
{
	return m_sendingPeriod;
}

uint16_t Parameters::getDayCost() const
{
	return m_dayCost;
}

uint16_t Parameters::getNightCost() const
{
	return m_nightCost;
}

uint16_t Parameters::getDayStartTime() const
{
	return m_dayStartTime;
}

uint16_t Parameters::getNightStartTime() const
{
	return m_nightStartTime;
}

void Parameters::setId(const uint32_t id)
{
	if (m_id != id) {
		m_id = id;
		EEPROM.write(adress_id, id);
	}
}

void Parameters::setSendingPeriod(const uint16_t sendingPeriod)
{
	if (m_sendingPeriod != sendingPeriod) {
		m_sendingPeriod = sendingPeriod;
		EEPROM.write(adress_sending_period, sendingPeriod);
	}
}

void Parameters::setSensorSamplingPeriod(const uint16_t samplingPeriod)
{
	if (m_sendingPeriod != samplingPeriod) {
		m_sensorSamplingPeriod = samplingPeriod;
		EEPROM.write(adress_sensor_sampling_period, samplingPeriod);
	}
}

void Parameters::setDayCost(uint16_t cost)
{
	if (m_dayCost != cost) {
		m_dayCost = cost;
		EEPROM.write(adress_id, cost);
	}
}

void Parameters::setNightCost(uint16_t cost)
{
	if (m_nightCost != cost) {
		m_nightCost = cost;
		EEPROM.write(adress_id, cost);
	}
}

void Parameters::setDayStartTime(uint16_t time)
{
	if (m_dayStartTime != time) {
		m_dayStartTime = time;
		EEPROM.write(adress_id, time);
	}
}

void Parameters::setNightStartTime(uint16_t time)
{
    if (m_nightStartTime != time) {
        m_nightStartTime = time;
        EEPROM.write(adress_id, time);
    }
}
