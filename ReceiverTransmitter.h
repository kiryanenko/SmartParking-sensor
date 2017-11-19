#pragma once
#include <Arduino.h>

class ReceiverTransmitter
{
	const char type_send_msg_parking_status = 'M';
	const char type_send_msg_init_status = 'I';

public:
	ReceiverTransmitter();
	virtual ~ReceiverTransmitter();

	virtual bool init();
	virtual bool send(const byte *data, size_t size) = 0;
	void sendInitStatus(const uint32_t id);
	/**
	* \brief
	* \param id - идентификатор устройства
	* \param parkingPlaceId - номер парковочного места
	* \param isFree - свободно ли парковочное место
	*/
	void sendParkingStatus(const uint32_t id, const uint8_t parkingPlaceId, const bool isFree);

protected:
	const byte* dataToSendInitStatus(uint32_t id, size_t &bufSize) const;
	const byte* dataToSendParkingStatus(uint32_t id, uint8_t parkingPlaceId, bool isFree, size_t &bufSize) const;
};

