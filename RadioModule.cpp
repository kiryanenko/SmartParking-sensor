#include "RadioModule.h"



RadioModule::RadioModule()
{
}


RadioModule::~RadioModule()
{
}

bool RadioModule::init()
{
	return m_rf95.init();
}

void RadioModule::sendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree)
{
	Serial.print("[SEND] ");
	Serial.print(type_send_msg_parking_status); Serial.print(' ');
	Serial.print(id); Serial.print(' ');
	Serial.print(parkingPlaceId);  Serial.print(' ');
	Serial.println(isFree);

	byte dataToSend[1 + 4 + 1 + 1];
	memcpy(dataToSend, &type_send_msg_parking_status, 1);
	memcpy(dataToSend + 1, &id, 4);
	memcpy(dataToSend + 1 + 4, &parkingPlaceId, 1);
	memcpy(dataToSend + 1 + 4 + 1, &isFree, 1);
	//m_rf95.send(dataToSend, sizeof(dataToSend));
}
