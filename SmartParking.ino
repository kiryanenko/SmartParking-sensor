#include <SPI\src\SPI.h>
#include <RadioHead-master\RH_RF95.h>


// Singleton instance of the radio driver
RH_RF95 rf95;

void setup()
{
	Serial.begin(9600);
	if (!rf95.init()) {
		Serial.println("Init failed!");
	} else {
		Serial.println("Init success!");
	}
}

void loop()
{
	PCF8574 pcf1;
	rf95.send(dataoutgoing, sizeof(dataoutgoing));

}