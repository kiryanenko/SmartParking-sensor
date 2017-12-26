#pragma once

#include <Arduino-EEPROMEx\EEPROMex.h>

#define PARKING_PLACES_COUNT 1
#define PIN_RESET_LORA 9
#define PIN_INT_SONAR 3

#define KEYPAD_I2C_ADDR 0x20
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define TIMEOUT 120000
#define MSG_SHOW_TIME 5000

#define DEBUG


class Parameters
{
    uint32_t m_id; // Идентификатор устройства
    uint16_t m_sensorSamplingPeriod; // Период опроса датчиков
    uint16_t m_sendingPeriod; // Период отправки сообщений

    uint16_t m_dayCost; // Дневная тариф
    uint16_t m_nightCost; // Ночная ториф
    uint16_t m_dayStartTime; // Время (количество минут с 00:00) со скольки включается дневной тариф
    uint16_t m_nightStartTime; // Время (количество минут с 00:00) со скольки включается ночной тариф

    const int adress_id = 0;
    const int adress_sensor_sampling_period = adress_id + sizeof(m_id);
    const int adress_sending_period = adress_sensor_sampling_period + sizeof(m_sensorSamplingPeriod);

    const int adress_day_cost = adress_sending_period + sizeof(m_sendingPeriod);
    const int adress_night_cost = adress_day_cost + sizeof(m_dayCost);
    const int adress_day_start_time = adress_night_cost + sizeof(m_nightCost);
    const int adress_night_start_time = adress_day_start_time + sizeof(m_dayStartTime);

public:
    static Parameters& instance();

    uint32_t getId() const;
    uint16_t getSensorSamplingPeriod() const;
    uint16_t getSendingPeriod() const;

    uint16_t getDayCost() const;
    uint16_t getNightCost() const;
    uint16_t getDayStartTime() const;
    uint16_t getNightStartTime() const;

    void setId(uint32_t id);
    void setSendingPeriod(uint16_t sendingPeriod);
    void setSensorSamplingPeriod(uint16_t samplingPeriod);

    void setDayCost(uint16_t cost);
    void setNightCost(uint16_t cost);
    void setDayStartTime(uint16_t time);
    void setNightStartTime(uint16_t time);

private:
    Parameters();
    Parameters(const Parameters& root);
    Parameters& operator=(const Parameters&);

    template <typename T>
    void save(T &field, const T &data, int adress);
};
