#include "ReceiverTransmitter.h"


ReceiverTransmitter::ReceiverTransmitter(AbstractReceiveMessageHandler *handler)
{
	m_handler = handler;
}


ReceiverTransmitter::~ReceiverTransmitter()
{
}

bool ReceiverTransmitter::init()
{
	return true;
}


void ReceiverTransmitter::handleRecieveMessages()
{
	while (available()) {
		size_t size;
		const byte *msg = recv(size);
		if (msg && size >= sizeof(uint32_t) + sizeof(byte)) {
			const auto id = reinterpret_cast<uint32_t>(msg);
			if (id == Parameters::instance().getId()) {
				const auto type = msg[sizeof(id)];
				auto body = msg + sizeof(id) + sizeof(type);
				if (type == type_of_recv_msg_set_id) {
					handleRecvMsgSetId(body, size);
				} else if (type == type_of_recv_msg_set_sensor_sampling_period) {
					handleRecvMsgSetSamplingPeriod(body, size);
				} else if (type == type_of_recv_msg_set_sending_period) {
					handleRecvMsgSetSendingPeriod(body, size);
				} else if (type == type_of_recv_msg_reserve) {
					handleRecvMsgReserve(body, size);
				} else if (type == type_of_recv_msg_cancel_reservation) {
					handleRecvMsgCancelReservation(body, size);
				}
			}
			delete[] msg;
		}
	}
}


void ReceiverTransmitter::sendInitStatus(const uint32_t id)
{
	Serial.print("[SEND] ");
	Serial.print(type_of_send_msg_init_status);
	Serial.print(' ');
	Serial.println(id);

	size_t bufSize;
	const auto data = dataToSendInitStatus(id, bufSize);
	send(data, bufSize);
	delete[] data;
}


void ReceiverTransmitter::sendParkingStatus(const uint32_t id, const uint8_t parkingPlaceId, const bool isFree)
{
	Serial.print("[SEND] ");
	Serial.print(type_of_send_msg_parking_status);
	Serial.print(' ');
	Serial.print(id);
	Serial.print(' ');
	Serial.print(parkingPlaceId);
	Serial.print(' ');
	Serial.println(isFree);

	size_t bufSize;
	const auto data = dataToSendParkingStatus(id, parkingPlaceId, isFree, bufSize);
	send(data, bufSize);
	delete[] data;
}


const byte* ReceiverTransmitter::dataToSendInitStatus(uint32_t id, size_t &bufSize) const
{
	bufSize = 1 + 4;
	const auto dataToSend = new byte[bufSize];
	memcpy(dataToSend, &type_of_send_msg_init_status, 1);
	memcpy(dataToSend + 1, &id, 4);
	return dataToSend;
}


const byte* ReceiverTransmitter::dataToSendParkingStatus(uint32_t id, uint8_t parkingPlaceId, bool isFree, size_t &bufSize) const
{
	bufSize = 1 + 4 + 1 + 1;
	const auto dataToSend = new byte[bufSize];
	memcpy(dataToSend, &type_of_send_msg_parking_status, 1);
	memcpy(dataToSend + 1, &id, 4);
	memcpy(dataToSend + 1 + 4, &parkingPlaceId, 1);
	memcpy(dataToSend + 1 + 4 + 1, &isFree, 1);
	return dataToSend;
}


void ReceiverTransmitter::handleRecvMsgSetId(const byte* msg, size_t size)
{
	if (size == sizeof(uint32_t)) {
		const auto id = reinterpret_cast<uint32_t>(msg);
		m_handler->onSetIdMsg(id);
	}
}


void ReceiverTransmitter::handleRecvMsgSetSamplingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = reinterpret_cast<uint16_t>(msg);
		m_handler->onSetSamplingPeriodMsg(period);
	}
}


void ReceiverTransmitter::handleRecvMsgSetSendingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = reinterpret_cast<uint16_t>(msg);
		m_handler->onSetSendingPeriodMsg(period);
	}
}


void ReceiverTransmitter::handleRecvMsgReserve(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto placeId = reinterpret_cast<uint8_t>(msg);
		const auto time = reinterpret_cast<uint16_t>(msg + sizeof(placeId));
		m_handler->onReserveMsg(placeId, time);
	}
}


void ReceiverTransmitter::handleRecvMsgCancelReservation(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto placeId = reinterpret_cast<uint8_t>(msg);
		m_handler->onCancelReservationMsg(placeId);
	}
}
