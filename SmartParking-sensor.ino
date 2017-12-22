#include <Wire.h>
#include <PCF8574.h>
#include <SonarI2C.h>
#include <SPI.h>
#include <RadioHead\RH_RF95.h>
#include <Arduino-EEPROMEx\EEPROMex.h>
#include <OLED_I2C.h>
#include <Time\TimeLib.h>
#include <Time.h>
#include <DS3232RTC.h>
#include "ParkingPlace.h"
#include "ReceiverTransmitter.h"
#include "SerialModule.h"
#include "RadioModule.h"
#include "Parameters.h"
#include "ReceiveMessageHandler.h"
#include "RadioModuleHandler.h"
#include "Display.h"

#define PARKING_PLACES_COUNT 1
#define PIN_RESET_LORA 9
#define PIN_INT_SONAR 3


// Singleton instances
ReceiverTransmitter *receiverTransmitter;
ParkingPlace parkingPalces[PARKING_PLACES_COUNT];
Parameters &parameters = Parameters::instance();
SerialModule serialModule(new ReceiveMessageHandler(parkingPalces, PARKING_PLACES_COUNT));
Display display;

void setup()
{
	Serial.begin(9600);

	// Установка параметров и запись их в память
	parameters.setId(1);
	parameters.setSendingPeriod(2000);
	parameters.setSensorSamplingPeriod(500);

	RadioModule *radioModule = new RadioModule(
		PIN_RESET_LORA, 
		parameters.getSendingPeriod() / PARKING_PLACES_COUNT, 
		new RadioModuleHandler(parkingPalces, PARKING_PLACES_COUNT)
	);
	if (radioModule->init()) {
		receiverTransmitter = radioModule;
		Serial.println("[INFO] RF95 init success!");
	} else {
		Serial.println("[WARN] RF95 init failed!");
		delete radioModule;
		receiverTransmitter = &serialModule;
		Serial.println("[INFO] Serial module init success!");
	}
	
	SonarI2C::begin(PIN_INT_SONAR);
	for (int i = 0; i < PARKING_PLACES_COUNT; ++i) {
		parkingPalces[i].init(i + 1);
	}

    display.init();

	delay(300);
	receiverTransmitter->sendInitStatus(parameters.getId());
}

void loop()
{
	Serial.println("[DEBUG] LOOP");
	SonarI2C::doSonar();  // call every cycle, SonarI2C handles the spacing
	static unsigned long time = millis();
	for (byte i = 0; i < PARKING_PLACES_COUNT; ++i) {
		if (parkingPalces[i].monitor() || millis() - time > parameters.getSendingPeriod()) {
			time = millis();
			receiverTransmitter->sendParkingStatus(parameters.getId(), i, parkingPalces[i].isFree());
		}
	}
	receiverTransmitter->handleRecieveMessages();
	serialModule.handleRecieveMessages();

    display.drawTime(12);

	delay(parameters.getSensorSamplingPeriod());
}