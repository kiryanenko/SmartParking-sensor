#pragma once
#include <Arduino.h>
#include "AbstractReceiveMessageHandler.h"

class ReceiverTransmitter
{
	const uint8_t type_of_send_msg_parking_status = 'S';
	const uint8_t type_of_send_msg_init_status = 'I';
    const uint8_t type_of_send_msg_payment = 'P';


	const uint8_t type_of_recv_msg_set_id = 'i';
	const uint8_t type_of_recv_msg_set_sensor_sampling_period = 's';
	const uint8_t type_of_recv_msg_set_sending_period = 'p';

	const uint8_t type_of_recv_msg_reserve = 'r';
	const uint8_t type_of_recv_msg_cancel_reservation = 'c';

    const uint8_t type_of_recv_msg_set_day_cost = 'q';
    const uint8_t type_of_recv_msg_set_night_cost = 'w';
    const uint8_t type_of_recv_msg_set_day_start_time = 'd';
    const uint8_t type_of_recv_msg_set_night_start_time = 'n';


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
    void sendPayment(const uint32_t id, const uint8_t parkingPlaceId, const uint16_t time, const uint16_t totalCost);

protected:
	const byte* dataToSendInitStatus(uint32_t id, size_t &bufSize) const;
	const byte* dataToSendParkingStatus(uint32_t id, uint8_t parkingPlaceId, bool isFree, size_t &bufSize) const;
    const byte* dataToSendPayment(uint32_t id, uint8_t parkingPlaceId, uint16_t time, uint16_t totalCost, size_t &bufSize) const;

private:
	void handleRecvMsgSetId(const byte *msg, size_t size);
	void handleRecvMsgSetSamplingPeriod(const byte *msg, size_t size);
	void handleRecvMsgSetSendingPeriod(const byte *msg, size_t size);
	void handleRecvMsgReserve(const byte *msg, size_t size);
	void handleRecvMsgCancelReservation(const byte *msg, size_t size);

    void handleRecvMsgSetDayCost(const byte *msg, size_t size);
    void handleRecvMsgSetNightCost(const byte *msg, size_t size);
    void handleRecvMsgSetDayStartTime(const byte *msg, size_t size);
    void handleRecvMsgSetNightStartTime(const byte *msg, size_t size);
};

