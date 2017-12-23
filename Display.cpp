#include "Display.h"


Display::Display()
{
}


Display::~Display()
{
}

void Display::init()
{
    OzOled.init();  //initialze Oscar OLED display
}

void Display::drawTime(time_t time)
{
}

void Display::draw()
{
    OzOled.clearDisplay();
    OzOled.printString("Hello World!"); //Print the String
}
