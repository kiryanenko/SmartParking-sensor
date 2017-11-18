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
	* \param id - ������������� ����������
	* \param parkingPlaceId - ����� ������������ �����
	* \param isFree - �������� �� ����������� �����
	*/
	void sendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree);

protected:
	const byte* dataToSendParkingStatus(uint16_t id, byte parkingPlaceId, bool isFree) const;
};

