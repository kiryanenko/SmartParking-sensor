#pragma once

#include <i2ckeypad.h>

class Payment
{
    i2ckeypad m_keypad;

    enum State {
        START,
        ENTER_PARKING_PLACE_NUMBER,
        ENTER_TIME,
        PAYMENT,
        WAITING
    } m_state;

public:
    Payment();
    ~Payment();

    void init();

    void exec();
};
