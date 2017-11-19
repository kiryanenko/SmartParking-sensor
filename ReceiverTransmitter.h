#pragma once
#include <Arduino.h>

class ReceiverTransmitter
{
	const char type_send_msg_parking_status = 'M';

public:
	ReceiverTransmitter();
	virtual ~ReceiverTransmitter();

	virtual bool init();
	virtual bool send(const byte *data, size_t size) = 0;
	/**
	* \brief
	* \param id - идентификатор устройства
	* \param parkingPlaceId - номер парковочного места
	* \param isFree - свободно ли парковочное место
	*/
	void sendParkingStatus(const uint64_t id, const uint8_t parkingPlaceId, const bool isFree);

protected:
	const byte* dataToSendParkingStatus(uint64_t id, uint8_t parkingPlaceId, bool isFree, size_t &bufSize) const;
};

