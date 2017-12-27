#include "ReceiverTransmitter.h"
#include "MemUtils.h"
#include "Parameters.h"

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
		size_t msgSize;
		const byte *msg = recv(msgSize);
		if (msg) {
#ifdef DEBUG
			Serial.print(F("[DEBUG] Recv msg: "));
			for (size_t i = 0; i < msgSize; ++i) {
				Serial.print(msg[i]);
				Serial.print(' ');
			}
			Serial.println();
#endif

			const auto id = getReverseData<uint32_t>(msg);
			if (id == Parameters::instance().getId()) {
				const auto type = msg[sizeof(id)];
				size_t headerSize = sizeof(id) + sizeof(type);
				size_t bodySize = msgSize - headerSize;
				auto body = msg + headerSize;

#ifdef DEBUG
				Serial.print(F("[DEBUG] Recv msg type = "));
				Serial.print(type);
				Serial.print(F("; bodySize = "));
				Serial.println(bodySize);
#endif

				if (type == type_of_recv_msg_set_id) {
					handleRecvMsgSetId(body, bodySize);
				} else if (type == type_of_recv_msg_set_sensor_sampling_period) {
					handleRecvMsgSetSamplingPeriod(body, bodySize);
				} else if (type == type_of_recv_msg_set_sending_period) {
					handleRecvMsgSetSendingPeriod(body, bodySize);
				} else if (type == type_of_recv_msg_reserve) {
					handleRecvMsgReserve(body, bodySize);
				} else if (type == type_of_recv_msg_cancel_reservation) {
					handleRecvMsgCancelReservation(body, bodySize);
				}
			} else {
#ifdef DEBUG
				Serial.print("[DEBUG] Msg for other sensor with id = ");
				Serial.println(id);
#endif
			}
			delete[] msg;
		}
	}
}


void ReceiverTransmitter::sendInitStatus(const uint32_t id)
{
#ifdef DEBUG
	Serial.print(F("[SEND] "));
	Serial.print(type_of_send_msg_init_status);
	Serial.print(' ');
	Serial.println(id);
#endif

	size_t bufSize;
	const auto data = dataToSendInitStatus(id, bufSize);
	send(data, bufSize);
	delete[] data;
}


void ReceiverTransmitter::sendParkingStatus(const uint32_t id, const uint8_t parkingPlaceId, const bool isFree)
{
#ifdef DEBUG
	Serial.print(F("[SEND] "));
	Serial.print(type_of_send_msg_parking_status);
	Serial.print(' ');
	Serial.print(id);
	Serial.print(' ');
	Serial.print(parkingPlaceId);
	Serial.print(' ');
	Serial.println(isFree);
#endif

	size_t bufSize;
	const auto data = dataToSendParkingStatus(id, parkingPlaceId, isFree, bufSize);
	send(data, bufSize);
	delete[] data;
}

void ReceiverTransmitter::sendPayment(
    const uint32_t id, 
    const uint8_t parkingPlaceId, 
    const uint16_t time,
    const uint16_t totalCost)
{
#ifdef DEBUG
    Serial.print(F("[SEND] "));
    Serial.print(type_of_send_msg_payment);
    Serial.print(' ');
    Serial.print(id);
    Serial.print(' ');
    Serial.print(parkingPlaceId);
    Serial.print(' ');
    Serial.println(time);
    Serial.print(' ');
    Serial.println(totalCost);
#endif

    size_t bufSize;
    const auto data = dataToSendPayment(id, parkingPlaceId, time, totalCost,  bufSize);
    send(data, bufSize);
    delete[] data;
}


const byte* ReceiverTransmitter::dataToSendInitStatus(const uint32_t id, size_t &bufSize) const
{
	bufSize = 1 + 4;
	const auto dataToSend = new byte[bufSize];
	cpyReverseData(dataToSend, type_of_send_msg_init_status);
	cpyReverseData(dataToSend + 1, id);
	return dataToSend;
}

const byte* ReceiverTransmitter::dataToSendParkingStatus(const uint32_t id, const uint8_t parkingPlaceId, bool isFree, size_t &bufSize) const
{
	bufSize = 1 + 4 + 1 + 1;
	const auto dataToSend = new byte[bufSize];
	cpyReverseData(dataToSend, type_of_send_msg_parking_status);
	cpyReverseData(dataToSend + 1, id);
	cpyReverseData(dataToSend + 1 + 4, parkingPlaceId);
	cpyReverseData(dataToSend + 1 + 4 + 1, isFree);
	return dataToSend;
}

const byte* ReceiverTransmitter::dataToSendPayment(const uint32_t id, const uint8_t parkingPlaceId, uint16_t time, uint16_t totalCost, size_t &bufSize) const
{
    bufSize = 1 + 4 + 1 + 2 + 2;
    const auto dataToSend = new byte[bufSize];
    cpyReverseData(dataToSend, type_of_send_msg_payment);
    cpyReverseData(dataToSend + 1, id);
    cpyReverseData(dataToSend + 1 + 4, parkingPlaceId);
    cpyReverseData(dataToSend + 1 + 4 + 1, time);
    cpyReverseData(dataToSend + 1 + 4 + 1 + 2, totalCost);
    return dataToSend;
}


void ReceiverTransmitter::handleRecvMsgSetId(const byte* msg, size_t size)
{
	if (size == sizeof(uint32_t)) {
		const auto id = getReverseData<uint32_t>(msg);
		m_handler->onSetIdMsg(id);
	}
}


void ReceiverTransmitter::handleRecvMsgSetSamplingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = getReverseData<uint16_t>(msg);
		m_handler->onSetSamplingPeriodMsg(period);
	}
}


void ReceiverTransmitter::handleRecvMsgSetSendingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = getReverseData<uint16_t>(msg);
		m_handler->onSetSendingPeriodMsg(period);
	}
}


void ReceiverTransmitter::handleRecvMsgReserve(const byte* msg, size_t size)
{
#ifdef DEBUG
	Serial.println(F("[DEBUG] handleRecvMsgReserve"));
#endif

	if (size == sizeof(uint8_t) + sizeof(uint16_t)) {
		const auto placeId = getReverseData<uint8_t>(msg);
		const auto time = getReverseData<uint16_t>(msg + sizeof(placeId));
		m_handler->onReserveMsg(placeId, time);
	}
}


void ReceiverTransmitter::handleRecvMsgCancelReservation(const byte* msg, size_t size)
{
	if (size == sizeof(uint8_t)) {
		const auto placeId = getReverseData<uint8_t>(msg);
		m_handler->onCancelReservationMsg(placeId);
	}
}
