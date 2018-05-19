#pragma once

#include <Arduino.h>
#include <i2ckeypad.h>
#include "Display.h"
#include "Timer.h"
#include  "ParkingPlace.h"
#include  "Driver.h"

class Payment
{
    i2ckeypad m_keypad;
    Display *m_display;

    ParkingPlace *m_parkingPlaces;
    Driver *m_driver;

    String m_inputStr;
    Timer m_timeout;

    uint8_t m_parkingPlace;
    uint16_t m_timeReserve;
    float m_totalCost;

    enum State
    {
        START,
        ERROR,
        ENTER_PARKING_PLACE,
        ENTER_TIME,
        PAYMENT,
        SUCCESS_PAYMENT
    } m_state;

public:
    Payment(Display* display, ParkingPlace *parkingPlaces, Driver *driver);
    ~Payment();

    void init();

    void exec();

private:
    void startState(char key);
    void errorState(char key);
    void successPaymentState(char key);

    void inputState(char key, void(Payment::* onSuccess)());

    void onSuccessInputParkingPlace();
    void onSuccessInputTime();
    void onSuccessInputPayment();

    void setState(State state);

    float countingCost(time_t time) const;
};
