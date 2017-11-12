#pragma once
#include <PCF8574\PCF8574.h>
#include <SonarI2C\SonarI2C.h>


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

	// ��������� � ���������� ������ � �������
	// ���������� true ��� ��������� ���������
	bool monitor();

	bool isFree() const;
};

