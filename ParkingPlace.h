#pragma once
#include <PCF8574\PCF8574.h>
#include <SonarI2C\SonarI2C.h>

#define PIN_TRIG 0
#define PIN_ECHO 1
#define PIN_IS_FREE 2
#define PIN_IS_BOOKED 3

#define CAR_DISTANCE 10		// ��������� �� ���������� (��)


class ParkingPlace
{
	byte m_id;

	bool m_isReserved;
	bool m_isFree;

	long m_reservationTime;

	PCF8574 *m_pcf;
	SonarI2C *m_sensor;

public:
	ParkingPlace() = default;
	~ParkingPlace();

	void init(const byte id);
	// ��������� � ���������� ������ � �������
	// ���������� true ��� ��������� ���������
	bool monitor();
	bool isFree() const;

	void reserve(uint16_t time);
	void cancelReservation();

private:
	void setIsFree(const bool isFree);
	void setReserve(const bool isReserve);
};

