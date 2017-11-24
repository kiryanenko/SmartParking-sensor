#pragma once
#include <Arduino.h>
#include "AbstractReceiveMessageHandler.h"
#include "Parameters.h"

class ReceiverTransmitter
{
	const char type_of_send_msg_parking_status = 'S';
	const char type_of_send_msg_init_status = 'I';

	const char type_of_recv_msg_set_id = 'i';
	const char type_of_recv_msg_set_sensor_sampling_period = 's';
	const char type_of_recv_msg_set_sending_period = 'p';
	const char type_of_recv_msg_reserve = 'r';
	const char type_of_recv_msg_cancel_reservation = 'R';

	AbstractReceiveMessageHandler *m_handler;

public:
	explicit ReceiverTransmitter(AbstractReceiveMessageHandler *handler);
	virtual ~ReceiverTransmitter();

	virtual bool init();
	virtual bool send(const byte *data, size_t size) = 0;
	virtual bool available() = 0;
	virtual byte* recv(size_t &size) = 0;

	void handleRecieveMessages();

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

private:
	void handleRecvMsgSetId(const byte *msg, size_t size);
	void handleRecvMsgSetSamplingPeriod(const byte *msg, size_t size);
	void handleRecvMsgSetSendingPeriod(const byte *msg, size_t size);
	void handleRecvMsgReserve(const byte *msg, size_t size);
	void handleRecvMsgCancelReservation(const byte *msg, size_t size);
};

