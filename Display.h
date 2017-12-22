#pragma once

#include <OLED_I2C.h>
#include <Time.h>

class Display
{
    OLED  *m_oled;
public:
    Display();
    ~Display();

    void init();

    void drawTime(time_t time);
};

