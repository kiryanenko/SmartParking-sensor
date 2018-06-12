#include "Payment.h"

#include <Time.h>
#include "Parameters.h"

Payment::Payment(Display *display, ParkingPlace *parkingPlaces, Driver *driver) :
    m_display(display),
    m_keypad(KEYPAD_I2C_ADDR, KEYPAD_ROWS, KEYPAD_COLS),
    m_parkingPlaces(parkingPlaces),
    m_driver(driver),
    m_state(START)
{
}

Payment::~Payment()
{
}

void Payment::init()
{
    m_keypad.init();
    m_display->showStartPage();
}

void Payment::exec()
{
    const auto key = m_keypad.get_key();
    if (key != '\0')
    {
#ifdef DEBUG
        Serial.print(F("[DEBUG] Enter key = "));
        Serial.println(key);
#endif

        switch (m_state) {
        case START:
            startState(key);
            break;
        case ENTER_PARKING_PLACE:
            inputState(key, &onSuccessInputParkingPlace);
            break;
        case ENTER_TIME:
            inputState(key, &onSuccessInputTime);
            break;
        case PAYMENT:
            inputState(key, &onSuccessInputPayment);
            break;
        case SUCCESS_PAYMENT:
            successPaymentState(key);
            break;
        case ERROR:
            errorState(key);
            break;
        }
    }

    if (m_state == ERROR && m_timeout.isFinished()) {
        setState(START);
        m_display->showStartPage();
    } else if (m_state != START && m_state != ERROR && m_timeout.isFinished()) {
        setState(ERROR);
        m_display->showError(PSTR("Таймоут."));
    }
}

void Payment::startState(const char key)
{
    if (key == '1') {
        setState(ENTER_PARKING_PLACE);
        m_display->showEnterParkingPlacePage();
    }
}

void Payment::errorState(char key)
{
    setState(START);
    m_display->showStartPage();
}

void Payment::successPaymentState(char key)
{
    setState(START);
    m_display->showStartPage();
}

void Payment::inputState(const char key, void (Payment::* onSuccess)())
{
    if (key >= '0' && key <= '9') {
        m_inputStr += key;
        m_display->drawInput(m_inputStr);
    } else if (key == '*') {
        if (m_inputStr.length() > 0) {
#ifdef DEBUG
            Serial.println(F("[DEBUG] Success input"));
#endif
            (void) (this->*onSuccess)();
        } else {
            setState(ERROR);
            m_display->showError(PSTR("Данные не введены."));
        }
    } else if (key == '#') {
        setState(ERROR);
        m_display->showError(PSTR("Платеж отменен."));
    }
}

void Payment::onSuccessInputParkingPlace()
{
#ifdef DEBUG
    Serial.println(F("[DEBUG] success input parking place"));
#endif

    m_parkingPlace = atoi(m_inputStr.c_str());
    if (m_parkingPlace < 1 || m_parkingPlace > PARKING_PLACES_COUNT) {
        setState(ERROR);
        m_display->showError(PSTR("Парковка не найдена."));
        return;
    }

    setState(ENTER_TIME);
    m_display->showEnterTimePage();
}

void Payment::onSuccessInputTime()
{
    m_timeReserve = atoi(m_inputStr.c_str()) * 60;
    m_totalCost = countingCost(m_timeReserve);
    setState(PAYMENT);
    m_display->showPaymentPage(m_totalCost);
}

void Payment::onSuccessInputPayment()
{
    const float payment = atoi(m_inputStr.c_str());
    const auto change = payment - m_totalCost;

    if (change < 0) {
        setState(ERROR);
        m_display->showError(PSTR("Недостаточно средств."));
        return;
    }

    auto& params = Parameters::instance();
    m_driver->sendPayment(params.getId(), m_parkingPlace, m_timeReserve, payment, m_totalCost);
    m_parkingPlaces[m_parkingPlace - 1].reserve(m_timeReserve * 60);

    setState(SUCCESS_PAYMENT);
    m_display->showSuccessPaymentPage(change);
}

void Payment::setState(const State state)
{
    m_inputStr = "";
    switch (state) {
    case ENTER_PARKING_PLACE:
    case ENTER_TIME:
        m_timeout.start(TIMEOUT);
        break;
    case PAYMENT:
        m_timeout.start(3 * TIMEOUT);
        break;
    case SUCCESS_PAYMENT:
        m_timeout.start(3 * MSG_SHOW_TIME);
        break;
    case ERROR:
        m_timeout.start(MSG_SHOW_TIME);
        break;
    }
    m_state = state;
}

float Payment::countingCost(const time_t time) const
{
    auto& params = Parameters::instance();
    const auto now = static_cast<time_t>(hour()) * 60 * 60 + minute() * 60 + second();    // Секунды прошедшие с начала дня
#ifdef DEBUG
    Serial.print(F("[DEBUG] Now=")); Serial.print(now); 
    Serial.print(F(" DayStartTime=")); Serial.print(params.getDayStartTime()); 
    Serial.print(F(" NightStartTime=")); Serial.print(params.getNightStartTime());
#endif
    uint16_t cost;
    if (now >= params.getDayStartTime() && 
        (now < params.getNightStartTime() || params.getNightStartTime() < params.getDayStartTime())) {
        cost = params.getDayCost();
    } else {
        cost = params.getNightCost();
    }
    return time * cost / 3600.0;
}
