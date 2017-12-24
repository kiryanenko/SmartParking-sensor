#include "Payment.h"

#include "Parameters.h"

Payment::Payment() : 
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
}

void Payment::exec()
{
    const auto key = m_keypad.get_key();
    if (key != '\0') {
#ifdef DEBUG
        Serial.print("[DEBUG] Enter key: ");
        Serial.println(key);
#endif


    }
}
