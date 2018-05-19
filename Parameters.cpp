#include "Parameters.h"

Parameters::Parameters()
{
	m_id = EEPROM.readLong(adress_id);
	m_sendingPeriod = EEPROM.readInt(adress_sending_period);
	m_sensorSamplingPeriod = EEPROM.readInt(adress_sensor_sampling_period);

    m_dayCost = EEPROM.readInt(adress_day_cost);
    m_nightCost = EEPROM.readInt(adress_night_cost);
    m_dayStartTime = EEPROM.readInt(adress_day_start_time);
    m_nightStartTime = EEPROM.readInt(adress_night_start_time);
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

uint32_t Parameters::getDayStartTime() const
{
	return m_dayStartTime;
}

uint32_t Parameters::getNightStartTime() const
{
	return m_nightStartTime;
}

void Parameters::setId(const uint32_t id)
{
    save(m_id, id, adress_id);
}

void Parameters::setSendingPeriod(const uint16_t period)
{
    save(m_sendingPeriod, period, adress_sending_period);
}

void Parameters::setSensorSamplingPeriod(const uint16_t period)
{
    save(m_sensorSamplingPeriod, period, adress_sensor_sampling_period);
}

void Parameters::setDayCost(const uint16_t cost)
{
    save(m_dayCost, cost, adress_day_cost);
}

void Parameters::setNightCost(const uint16_t cost)
{
    save(m_nightCost, cost, adress_night_cost);
}

void Parameters::setDayStartTime(const uint32_t time)
{
    save(m_dayStartTime, time, adress_day_start_time);
}

void Parameters::setNightStartTime(const uint32_t time)
{
    save(m_nightStartTime, time, adress_night_start_time);
}

template <typename T>
void Parameters::save(T& field, const T& data, int adress)
{
    if (field != data) {
        field = data;
        EEPROM.write(adress, data);
    }
}
