#pragma once

#include <i2ckeypad.h>

class Payment
{
	i2ckeypad m_keypad;

	enum STATE {
		START,
		ENTER_PARKING_PLACE,
		ENTER_PARKING_
	} m_state;

public:
	Payment();
	~Payment();

	void exec();
};

