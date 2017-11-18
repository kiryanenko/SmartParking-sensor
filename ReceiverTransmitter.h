#pragma once


class ReceiverTransmitter
{
	const byte type_send_msg_parking_status = 'M';

public:
	ReceiverTransmitter();
	virtual ~ReceiverTransmitter();

	virtual bool init();
	virtual bool send(const byte data[]) = 0;
	/**
	* \brief
	* \param id - идентификатор устройства
	* \param parkingPlaceId - номер парковочного места
	* \param isFree - свободно ли парковочное место
	*/
	void sendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree);

protected:
	const byte* dataToSendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree) const;
};

