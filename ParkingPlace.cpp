#include "ParkingPlace.h"

#define PIN_TRIG 0
#define PIN_ECHO 1
#define PIN_IS_FREE 2
#define PIN_IS_BOOKED 3

#define CAR_DISTANCE 10		// Дистанция до автомобиля (см)


void ParkingPlace::setIsFree(const bool isFree)
{
	m_isFree = isFree;
	m_pcf->digitalWrite(PIN_IS_FREE, m_isFree);
}


void ParkingPlace::init(const byte id)
{
	m_id = id;
	m_isBooked = false;

	m_pcf = new PCF8574;
	const auto adress = 0x20 + id;
	m_pcf->begin(adress);

//	m_pcf->pinMode(PIN_TRIG, OUTPUT);
//	m_pcf->pinMode(PIN_ECHO, INPUT);
	m_sensor = new SonarI2C(adress, PIN_TRIG, 4000);
	m_sensor->init();

	m_pcf->pinMode(PIN_IS_FREE, OUTPUT);
	m_pcf->pinMode(PIN_IS_BOOKED, OUTPUT);

	Serial.print("[INFO] Parking place ["); Serial.print(m_id); Serial.println("] init success!");
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
	m_pcf->digitalWrite(PIN_IS_BOOKED, m_isBooked);
}


bool ParkingPlace::monitor()
{
	const auto dist = m_sensor->cm();
	Serial.print("[DEBUG] Distance "); Serial.println(dist);
	const auto isFree = dist > CAR_DISTANCE;
	const auto isChangeState = isFree != m_isFree;
	setIsFree(isFree);
	return isChangeState;
}

bool ParkingPlace::isFree() const
{
	return m_isFree;
}
