#include <Wire.h>
#include <PCF8574\PCF8574.h>
#include <SonarI2C\SonarI2C.h>
#include <SPI.h>
#include <RadioHead-master\RH_RF95.h>
#include "ParkingPlace.h"
#include "ReceiverTransmitter.h"
#include "SerialModule.h"s
#include "RadioModule.h"

#define PARKING_PLACES_COUNT 1
#define PIN_RESET_LORA 9

uint16_t sensorSamplingPeriod = 500;		// Период опроса датчиков
uint16_t SendingPeriod = 2000;				// Период отправки сообщений
uint64_t ID = 0;

// Singleton instance of the radio driver
ReceiverTransmitter *receiverTransmitter;

ParkingPlace parkingPalces[PARKING_PLACES_COUNT];


void setup()
{
	Serial.begin(9600);

	pinMode(PIN_RESET_LORA, OUTPUT);
	// reset lora module first. to make sure it will works properly
	digitalWrite(PIN_RESET_LORA, LOW);
	delay(1000);
	digitalWrite(PIN_RESET_LORA, HIGH);

	RadioModule *radioModule = new RadioModule();
	if (radioModule->init) {
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
		if (parkingPalces[i].monitor() || millis() - time > SendingPeriod) {
			time = millis();
			receiverTransmitter->sendParkingStatus(ID, i, parkingPalces[i].isFree());
		}
	}
	delay(sensorSamplingPeriod);
}