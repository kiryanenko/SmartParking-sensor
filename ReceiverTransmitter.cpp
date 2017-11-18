#include "ReceiverTransmitter.h"



ReceiverTransmitter::ReceiverTransmitter()
{
}


ReceiverTransmitter::~ReceiverTransmitter()
{
}

bool ReceiverTransmitter::init()
{
	return true;
}

void ReceiverTransmitter::sendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree)
{
	Serial.print("[SEND] ");
	Serial.print(type_send_msg_parking_status);
	Serial.print(' ');
	Serial.print(id);
	Serial.print(' ');
	Serial.print(parkingPlaceId);
	Serial.print(' ');
	Serial.println(isFree);

	const byte *data = dataToSendParkingStatus(id, parkingPlaceId, isFree);
	send(data);
}

const byte* ReceiverTransmitter::dataToSendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree) const
{
	byte dataToSend[1 + 4 + 1 + 1];
	memcpy(dataToSend, &type_send_msg_parking_status, 1);
	memcpy(dataToSend + 1, &id, 4);
	memcpy(dataToSend + 1 + 4, &parkingPlaceId, 1);
	memcpy(dataToSend + 1 + 4 + 1, &isFree, 1);
	return dataToSend;
}
