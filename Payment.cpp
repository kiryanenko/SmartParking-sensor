#include "Payment.h"

Payment::Payment() : m_keypad(KEYPAD_I2C_ADDR, KEYPAD_ROWS, KEYPAD_COLS)
{
}

Payment::~Payment()
{
}

void Payment::exec()
{
}
