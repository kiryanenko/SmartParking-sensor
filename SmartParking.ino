#include <Wire.h>
#include <PCF8574\PCF8574.h>
#include <SonarI2C\SonarI2C.h>
#include <SPI.h>
#include <RadioHead-master\RH_RF95.h>
#include <Arduino-EEPROMEx\EEPROMex.h>
#include "ParkingPlace.h"
#include "ReceiverTransmitter.h"
#include "SerialModule.h"
#include "RadioModule.h"
#include "Parameters.h"

#define PARKING_PLACES_COUNT 1
#define PIN_RESET_LORA 9


// Singleton instances
ReceiverTransmitter *receiverTransmitter;
ParkingPlace parkingPalces[PARKING_PLACES_COUNT];
Parameters parameters;


void setup()
{
	Serial.begin(9600);

	RadioModule *radioModule = new RadioModule(PIN_RESET_LORA);
	if (radioModule->init()) {
		receiverTransmitter = radioModule;
		Serial.println("[INFO] RF95 init success!");
	} else {
		Serial.println("[WARN] RF95 init failed!");
		receiverTransmitter = new SerialModule();
		Serial.println("[INFO] Serial module init success!");
	}
	
	for (int i = 0; i < PARKING_PLACES_COUNT; ++i) {
		parkingPalces[i].init(i);
	}
	SonarI2C::begin();

	delay(300);
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
	delay(parameters.getSensorSamplingPeriod);
}