#include "Display.h"



Display::Display()
{
}


Display::~Display()
{
}

void Display::init()
{
    m_oled = new OLED(SDA, SCL);
    m_oled->begin();
    extern uint8_t SmallFont[];
    m_oled->setFont(SmallFont);
}

void Display::drawTime(time_t time)
{

    m_oled->print("time", 10, 10);
    m_oled->update();
}
