#pragma once

#include <Arduino.h>
#include <Time.h>

class Display
{
public:
    Display();
    ~Display();

    void init();

    void setTime(time_t time);

    void showStartPage();
    void showEnterParkingPlacePage();
    void showEnterTimePage();
    void showPaymentPage(float cost);
    void showSuccessPaymentPage(float change);
    void showError(const char *error = "");

    void drawInput(String &inputStr);

private:
    void draw();
    void showHelp();
};

