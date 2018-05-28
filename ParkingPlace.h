#pragma once
#include <PCF8574\PCF8574.h>
#include <SonarI2C\SonarI2C.h>
#include "Timer.h"

#define PIN_TRIG 0
#define PIN_IS_FREE 1
#define PIN_IS_BOOKED 2

#define CAR_DISTANCE 10		// Дистанция до автомобиля (см)


class ParkingPlace
{
	byte m_id;

	bool m_isReserved;
	bool m_isFree;

    Timer m_reservationTimer;

	PCF8574 *m_pcf;
	SonarI2C *m_sensor;

public:
	ParkingPlace() = default;
	~ParkingPlace();

	void init(const byte id);
	// Считывает и возвращает данные с сенсора
	// Возвращает true при изменении состояния
	bool monitor();
	bool isFree() const;

	void reserve(uint32_t time);
	void cancelReservation();

private:
	void setIsFree(const bool isFree);
	void setReserve(const bool isReserve);
};

