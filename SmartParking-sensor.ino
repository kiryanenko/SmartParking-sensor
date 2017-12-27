#include <Wire.h>
#include <PCF8574.h>
#include <SonarI2C.h>
#include <SPI.h>
#include <RadioHead\RH_RF95.h>
#include <Arduino-EEPROMEx\EEPROMex.h>
#include <Time\TimeLib.h>
#include <Time.h>
#include <DS3232RTC.h>
#include <i2ckeypad.h>
#include <ASOLED.h>
#include <DS3232RTC.h>
#include "MemUtils.h"
#include "ParkingPlace.h"
#include "ReceiverTransmitter.h"
#include "SerialModule.h"
#include "RadioModule.h"
#include "Parameters.h"
#include "ReceiveMessageHandler.h"
#include "RadioModuleHandler.h"
#include "Display.h"
#include "Payment.h"


// Singleton instances
ReceiverTransmitter *receiverTransmitter;
ParkingPlace parkingPalces[PARKING_PLACES_COUNT];
Parameters &parameters = Parameters::instance();
SerialModule serialModule(new ReceiveMessageHandler(parkingPalces, PARKING_PLACES_COUNT));
Display display;
Payment *payment;


void setup()
{
	Serial.begin(9600);

#ifdef DEBUG
	// ��������� ���������� � ������ �� � ������
	parameters.setId(1);
	parameters.setSendingPeriod(2000);
	parameters.setSensorSamplingPeriod(100);

    parameters.setDayCost(200);
    parameters.setNightCost(100);
    parameters.setDayStartTime(6 * 60 * 60);     // 06:00
    parameters.setNightStartTime(22 * 60 * 60);  // 22:00
#endif

/* #ifdef DEBUG
    // ��������� ���� � �������
    tmElements_t tm;
    tm.Year = CalendarYrToTm(2017);
    tm.Month = 12;
    tm.Day = 27;
    tm.Hour = 0;
    tm.Minute = 33;
    tm.Second = 0;
    RTC.set(makeTime(tm));
#endif // DEBUG */

    setSyncProvider(RTC.get);

	RadioModule *radioModule = new RadioModule(
		PIN_RESET_LORA, 
		parameters.getSendingPeriod() / PARKING_PLACES_COUNT, 
		new RadioModuleHandler(parkingPalces, PARKING_PLACES_COUNT)
	);
	if (radioModule->init()) {
		receiverTransmitter = radioModule;
		Serial.println(F("[INFO] RF95 init success!"));
	} else {
		Serial.println(F("[WARN] RF95 init failed!"));
		delete radioModule;
		receiverTransmitter = &serialModule;
		Serial.println(F("[INFO] Serial module init success!"));
	}
	
	SonarI2C::begin(PIN_INT_SONAR);
	for (int i = 0; i < PARKING_PLACES_COUNT; ++i) {
		parkingPalces[i].init(i + 1);
	}

    display.init();

    payment = new Payment(&display, parkingPalces, receiverTransmitter);
    payment->init();

	delay(300);
	receiverTransmitter->sendInitStatus(parameters.getId());
}

void loop()
{
	SonarI2C::doSonar();  // call every cycle, SonarI2C handles the spacing
	static Timer sendingPeriod;
	for (byte i = 0; i < PARKING_PLACES_COUNT; ++i) {
		if (parkingPalces[i].monitor() || sendingPeriod.isFinished()) {
            sendingPeriod.start(parameters.getSendingPeriod());
			receiverTransmitter->sendParkingStatus(parameters.getId(), i, parkingPalces[i].isFree());
		}
	}
	receiverTransmitter->handleRecieveMessages();
	serialModule.handleRecieveMessages();

    payment->exec();
    
    static Timer sec;
    if (sec.isFinished()) {
        sec.start(1000);
        display.drawClock();
    }

	delay(parameters.getSensorSamplingPeriod());
}