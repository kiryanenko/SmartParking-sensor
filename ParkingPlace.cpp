#include "ParkingPlace.h"

#define PIN_TRIG 0
#define PIN_ECHO 1
#define PIN_IS_FREE 2
#define PIN_IS_BOOKED 3

#define CAR_DISTANCE 50		// Дистанция до автомобиля (см)


ParkingPlace::ParkingPlace(const byte id)
{
	m_id = id;
	m_isBooked = false;

	m_pcf = new PCF8574;
	m_pcf->begin(id);

	m_pcf->pinMode(PIN_TRIG, OUTPUT);
	m_pcf->pinMode(PIN_ECHO, INPUT);
	m_sensor = new Ultrasonic(PIN_TRIG, PIN_ECHO);

	m_pcf->pinMode(PIN_IS_FREE, OUTPUT);
	m_pcf->pinMode(PIN_IS_BOOKED, OUTPUT);

	monitor();
}


ParkingPlace::~ParkingPlace()
{
	delete m_pcf;
	delete m_sensor;
}


void ParkingPlace::setIsBooked(const bool isBooked)
{
	m_isBooked = isBooked;
}


bool ParkingPlace::monitor()
{
	float dist = m_sensor->Ranging(CM);
	m_isFree = dist > CAR_DISTANCE;
	return m_isFree;
}
