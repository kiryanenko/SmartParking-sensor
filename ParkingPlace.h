#pragma once
#include <PCF8574\PCF8574.h>
#include <Ultrasonic/Ultrasonic.h>


class ParkingPlace
{
private:
	bool m_isBooked;
	bool m_isFree;

	byte m_id;

	PCF8574 *m_pcf;
	Ultrasonic *m_sensor;

public:
	explicit ParkingPlace(const byte id);
	~ParkingPlace();

	void setIsBooked(const bool isBooked);

	// Считывает и возвращает данные с сенсора
	// true если парковка свободна
	bool monitor();
};

