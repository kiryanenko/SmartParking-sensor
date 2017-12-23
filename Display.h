#pragma once

#include <OzOLED.h>
#include <Time.h>

class Display
{
public:
    Display();
    ~Display();

    void init();

    void drawTime(time_t time);

    void draw();
};

