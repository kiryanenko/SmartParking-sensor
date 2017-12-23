#pragma once

#include <i2ckeypad.h>

class Payment
{
	i2ckeypad m_keypad;

	enum State {
		START,
		ENTER_PARKING_PLACE_NUMBER,
		ENTER_TIME,
        PAYMENT
	} m_state;

public:
	Payment(int keypadI2CAddr, int keypadRows, int keypadCols);
	~Payment();

	void exec();
};

