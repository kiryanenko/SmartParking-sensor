#pragma once
#include <PCF8574\PCF8574.h>
#include <SonarI2C\SonarI2C.h>

#define PIN_TRIG 0
#define PIN_ECHO 1
#define PIN_IS_FREE 2
#define PIN_IS_BOOKED 3

#define CAR_DISTANCE 10		// Дистанция до автомобиля (см)


class ParkingPlace
{
	bool m_isBooked;
	bool m_isFree;

	byte m_id;

	PCF8574 *m_pcf;
	SonarI2C *m_sensor;

	void setIsFree(const bool isFree);

public:
	ParkingPlace() = default;

	void init(const byte id);
	~ParkingPlace();

	void setIsBooked(const bool isBooked);

	// Считывает и возвращает данные с сенсора
	// Возвращает true при изменении состояния
	bool monitor();

	bool isFree() const;
};

