#include "Payment.h"

Payment::Payment(const int keypadI2CAddr, const int keypadRows, const int keypadCols) : 
    m_keypad(keypadI2CAddr, keypadRows, keypadCols), 
    m_state(START)
{
}

Payment::~Payment()
{
}

void Payment::exec()
{
}
