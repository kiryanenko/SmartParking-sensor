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
		if (msg) {
			if (msg[0] == type_of_recv_msg_set_id) {
				handleRecvMsgSetId(msg, size);
			} else if (msg[0] == type_of_recv_msg_set_sensor_sampling_period) {
				handleRecvMsgSetSamplingPeriod(msg, size);
			} else if (msg[0] == type_of_recv_msg_set_sending_period) {
				handleRecvMsgSetSendingPeriod(msg, size);
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
	byte* dataToSend = new byte[bufSize];
	memcpy(dataToSend, &type_of_send_msg_init_status, 1);
	memcpy(dataToSend + 1, &id, 4);
	return dataToSend;
}


const byte* ReceiverTransmitter::dataToSendParkingStatus(uint32_t id, uint8_t parkingPlaceId, bool isFree, size_t &bufSize) const
{
	bufSize = 1 + 4 + 1 + 1;
	byte* dataToSend = new byte[bufSize];
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
		m_handler->onRecvMsgSetId(id);
	}
}


void ReceiverTransmitter::handleRecvMsgSetSamplingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = reinterpret_cast<uint16_t>(msg);
		m_handler->onRecvMsgSetSamplingPeriod(period);
	}
}


void ReceiverTransmitter::handleRecvMsgSetSendingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = reinterpret_cast<uint16_t>(msg);
		m_handler->onRecvMsgSetSendingPeriod(period);
	}
}
