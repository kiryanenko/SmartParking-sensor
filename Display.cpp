#include "Display.h"

#include <ASOLED.h>

Display::Display()
{
}


Display::~Display()
{
}

void Display::init()
{
    LD.init();
}

void Display::showStartPage()
{
    draw();
    LD.printString_6x8("Для оплаты парковки,", 0, 0);
    LD.printString_6x8("введите 1", 0, 1);
}

void Display::showEnterParkingPlacePage()
{
    draw();
    LD.printString_6x8("Введите номер", 0, 0);
    LD.printString_6x8("парковки:", 0, 1);
    showHelp();
}

void Display::showEnterTimePage()
{
    draw();
    LD.printString_6x8("Введите время (мин):", 0, 0);
    showHelp();
}

void Display::showPaymentPage(const float cost)
{
    draw();
    LD.printString_6x8("Сумма к оплате:", 0, 1);
    LD.printNumber(cost, 2, 0, 2);
    LD.printString_6x8("руб", 109, 2);
    showHelp();
}

void Display::showSuccessPaymentPage(const float change)
{
    draw();
    LD.printString_6x8("Оплата произведена.", 0, 1);
    LD.printString_6x8("Сдача: ", 0, 1);
    LD.printNumber(change, 2, 42, 2);
    LD.printString_6x8("руб", 109, 2);
    LD.printString_6x8("Нажмите любую клавишу", 0, 6);
}

void Display::showError(const char* error)
{
    draw();
    LD.printString_6x8("Ошибка!", 0, 0);
    LD.printString_6x8(error, 0, 1);
    LD.printString_6x8("Нажмите любую клавишу", 0, 6);
}

void Display::drawInput(String& inputStr)
{
    LD.printString_6x8("                        ", 0, 3);
    LD.printString_6x8(inputStr.c_str(), (128 - inputStr.length()) / 2 - 1, 3);
}

void Display::draw()
{
    LD.clearDisplay();
}

void Display::showHelp()
{
    LD.printString_6x8("* - Далее", 0, 5);
    LD.printString_6x8("# - Отмена", 0, 6);
}

void Display::setTime(time_t time)
{
}
