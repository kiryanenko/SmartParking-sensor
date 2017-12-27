#include "ParkingPlace.h"
#include "Parameters.h"

void ParkingPlace::setIsFree(const bool isFree)
{
	m_isFree = isFree;
	m_pcf->digitalWrite(PIN_IS_FREE, m_isFree);
}


void ParkingPlace::init(const byte id)
{
	m_id = id;
	m_isReserved = false;

	m_pcf = new PCF8574;
	const auto adress = 0x20 + id;
	m_pcf->begin(adress);

	m_sensor = new SonarI2C(adress, PIN_TRIG, 4000);
	m_sensor->init();

	m_pcf->pinMode(PIN_IS_FREE, OUTPUT);
	m_pcf->pinMode(PIN_IS_BOOKED, OUTPUT);

#ifdef DEBUG
	Serial.print(F("[INFO] Parking place [")); 
    Serial.print(m_id); 
    Serial.println(F("] init success!"));
#endif
	monitor();
}


ParkingPlace::~ParkingPlace()
{
	delete m_pcf;
	delete m_sensor;
}


bool ParkingPlace::monitor()
{
	const auto dist = m_sensor->cm();
#ifdef DEBUG
	Serial.print(F("[DEBUG] Distance ")); Serial.println(dist);
#endif
	const auto isFree = dist > CAR_DISTANCE;
	const auto isChangeState = isFree != m_isFree;
	setIsFree(isFree);

	if (m_isReserved && m_reservationTimer.isFinished()) {
		setReserve(false);
	}

	return isChangeState;
}


bool ParkingPlace::isFree() const
{
	return m_isFree;
}


void ParkingPlace::reserve(const uint16_t time)
{
    m_reservationTimer.start(time * 1000);
	setReserve(true);
}

void ParkingPlace::cancelReservation()
{
	setReserve(false);
}


void ParkingPlace::setReserve(const bool isReserve)
{
	m_isReserved = isReserve;
	m_pcf->digitalWrite(PIN_IS_BOOKED, m_isReserved);
}
