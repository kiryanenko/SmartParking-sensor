#include "Payment.h"

#include "Parameters.h"

Payment::Payment(Display* display) :
    m_display(display),
    m_keypad(KEYPAD_I2C_ADDR, KEYPAD_ROWS, KEYPAD_COLS),
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
        switch (m_state)
        {
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

    if (m_state != START && m_state != ERROR && m_timeout.isFinished())
    {
        setState(ERROR);
        m_display->showError("Таймоут.");
    }
}

void Payment::startState(const char key)
{
    if (key == '1')
    {
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
    if (key >= '0' && key <= '9')
    {
        m_inputStr += key;
        m_display->drawInput(m_inputStr);
    }
    else if (key == '*')
    {
        if (m_inputStr.length() > 0)
        {
            void onSuccess();
        }
        else
        {
            setState(ERROR);
            m_display->showError("Данные не введены.");
        }
    }
    else if (key == '#')
    {
        setState(ERROR);
        m_display->showError("Платеж отменен.");
    }
}

void Payment::onSuccessInputParkingPlace()
{
    m_parkingPlace = atoi(m_inputStr.c_str());
    if (m_parkingPlace <= 1 || m_parkingPlace >= PARKING_PLACES_COUNT)
    {
        setState(ERROR);
        m_display->showError("Парковка не найдена.");
    }

    setState(ENTER_TIME);
    m_display->showEnterTimePage();
}

void Payment::onSuccessInputTime()
{
    m_totalCost = countingCost(atoi(m_inputStr.c_str()));
    setState(PAYMENT);
    m_display->showPaymentPage(m_totalCost);
}

void Payment::onSuccessInputPayment()
{
    const float payment = atoi(m_inputStr.c_str());
    const auto change = payment - m_totalCost;
    if (change < 0) {
        setState(ERROR);
        m_display->showError("Недостаточно средств.");
    }

    setState(SUCCESS_PAYMENT);
    m_display->showSuccessPaymentPage(m_totalCost);
}

void Payment::setState(const State state)
{
    m_inputStr = "";
    switch (state)
    {
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

float Payment::countingCost(time_t time)
{
    return 123.10;
}
