#include "Driver.h"
#include "MemUtils.h"
#include "Parameters.h"

Driver::Driver(AbstractReceiveMessageHandler *handler)
{
	m_handler = handler;
}


Driver::~Driver()
{
}

bool Driver::init()
{
	return true;
}


void Driver::handleRecieveMessages()
{
	while (available()) {
		size_t msgSize;
		const byte *msg = recv(msgSize);
		if (msg) {
#ifdef DEBUG
			Serial.print(F("[DEBUG] Recv msg[")); Serial.print(msgSize); Serial.print(F("]: "));
			for (size_t i = 0; i < msgSize; ++i) {
				Serial.print(msg[i]);
				Serial.print(' ');
			}
			Serial.println();
#endif
            const auto type = msg[0];
			const auto id = getReverseData<uint32_t>(msg + sizeof type);
			if (id == Parameters::instance().getId()) {
				size_t headerSize = sizeof id + sizeof type;
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
                } else if (type == type_of_recv_msg_set_time) {
                    handleRecvMsgSetTime(body, bodySize);
				} else if (type == type_of_recv_msg_reserve) {
					handleRecvMsgReserve(body, bodySize);
				} else if (type == type_of_recv_msg_cancel_reservation) {
					handleRecvMsgCancelReservation(body, bodySize);
				} else if (type == type_of_recv_msg_set_day_cost) {
					handleRecvMsgSetDayCost(body, bodySize);
				} else if (type == type_of_recv_msg_set_night_cost) {
					handleRecvMsgSetNightCost(body, bodySize);
				} else if (type == type_of_recv_msg_set_day_start_time) {
                    handleRecvMsgSetDayStartTime(body, bodySize);
				} else if (type == type_of_recv_msg_set_night_start_time) {
                    handleRecvMsgSetNightStartTime(body, bodySize);
				} else if (type == type_of_recv_msg_set_settings) {
                    handleRecvMsgSetSettings(body, bodySize);
				}

                if (type == type_of_recv_msg_set_sensor_sampling_period ||
                    type == type_of_recv_msg_set_sending_period ||
                    type == type_of_recv_msg_set_time ||
                    type == type_of_recv_msg_set_day_cost ||
                    type == type_of_recv_msg_set_night_cost ||
                    type == type_of_recv_msg_set_day_start_time ||
                    type == type_of_recv_msg_set_night_start_time ||
                    type == type_of_recv_msg_set_settings) {
                    auto& parameters = Parameters::instance();
                    sendInit(
                        parameters.getId(),
                        parameters.getSensorSamplingPeriod(),
                        parameters.getSendingPeriod(),
                        parameters.getDayCost(),
                        parameters.getNightCost(),
                        parameters.getDayStartTime(),
                        parameters.getNightStartTime()
                    );
                }
			} else {
#ifdef DEBUG
				Serial.print(F("[DEBUG] Msg for other sensor with id = "));
				Serial.println(id);
#endif
			}
			delete[] msg;
		}
	}
}


void Driver::sendInit(
    const uint32_t id,
    const uint16_t samplingPeriod,
    const uint16_t sendingPeriod,
    const uint16_t dayCost,
    const uint16_t nightCost,
    const uint32_t dayStartTime,
    const uint32_t nightStartTime)
{
#ifdef DEBUG
	Serial.print(F("[SEND] "));
	Serial.print(type_of_send_msg_init); Serial.print(' ');
    Serial.print(id); Serial.print(' ');
    Serial.print(samplingPeriod); Serial.print(' ');
    Serial.print(sendingPeriod); Serial.print(' ');
    Serial.print(dayCost); Serial.print(' ');
    Serial.print(nightCost); Serial.print(' ');
    Serial.print(dayStartTime); Serial.print(' ');
	Serial.println(nightStartTime);
#endif

	size_t bufSize;
	const auto data = dataToSendInit(
        id, 
        samplingPeriod,
        sendingPeriod,
        dayCost,
        nightCost,
        dayStartTime,
        nightStartTime,
        bufSize);
	send(data, bufSize);
	delete[] data;
}


void Driver::sendParkingStatus(const uint32_t id, const uint8_t parkingPlaceId, const bool isFree)
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

void Driver::sendPayment(
    const uint32_t id, 
    const uint8_t parkingPlaceId, 
    const uint32_t time,
    const uint16_t payment,
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
    const auto data = dataToSendPayment(id, parkingPlaceId, time, payment, totalCost,  bufSize);
    send(data, bufSize);
    delete[] data;
}


const byte* Driver::dataToSendInit(
    const uint32_t id,
    const uint16_t samplingPeriod,
    const uint16_t sendingPeriod,
    const uint16_t dayCost,
    const uint16_t nightCost,
    const uint32_t dayStartTime,
    const uint32_t nightStartTime, 
    size_t &bufSize) const
{
	bufSize = 1 + 4 + 2 + 2 + 2 + 2 + 4 + 4;
	const auto dataToSend = new byte[bufSize];
	cpyReverseData(dataToSend, type_of_send_msg_init);
	cpyReverseData(dataToSend + 1, id);
    cpyReverseData(dataToSend + 1 + 4, samplingPeriod);
    cpyReverseData(dataToSend + 1 + 4 + 2, sendingPeriod);
    cpyReverseData(dataToSend + 1 + 4 + 2 + 2, dayCost);
    cpyReverseData(dataToSend + 1 + 4 + 2 + 2 + 2, nightCost);
    cpyReverseData(dataToSend + 1 + 4 + 2 + 2 + 2 + 2, dayStartTime);
    cpyReverseData(dataToSend + 1 + 4 + 2 + 2 + 2 + 2 + 4, nightStartTime);
	return dataToSend;
}

const byte* Driver::dataToSendParkingStatus(
    const uint32_t id, 
    const uint8_t parkingPlaceId, 
    const bool isFree,
    size_t& bufSize) const
{
	bufSize = 1 + 4 + 1 + 1;
	const auto dataToSend = new byte[bufSize];
	cpyReverseData(dataToSend, type_of_send_msg_parking_status);
	cpyReverseData(dataToSend + 1, id);
	cpyReverseData(dataToSend + 1 + 4, parkingPlaceId);
	cpyReverseData(dataToSend + 1 + 4 + 1, isFree);
	return dataToSend;
}

const byte* Driver::dataToSendPayment(
    const uint32_t id, 
    const uint8_t parkingPlaceId,
    const uint32_t time,
    const uint16_t payment,
    const uint16_t totalCost, 
    size_t &bufSize) const
{
    bufSize = 1 + 4 + 1 + 4 + 2 + 2;
    const auto dataToSend = new byte[bufSize];
    cpyReverseData(dataToSend, type_of_send_msg_payment);
    cpyReverseData(dataToSend + 1, id);
    cpyReverseData(dataToSend + 1 + 4, parkingPlaceId);
    cpyReverseData(dataToSend + 1 + 4 + 1, time);
    cpyReverseData(dataToSend + 1 + 4 + 1 + 4, payment);
    cpyReverseData(dataToSend + 1 + 4 + 1 + 4 + 2, totalCost);
    return dataToSend;
}


void Driver::handleRecvMsgSetId(const byte* msg, size_t size)
{
	if (size == sizeof(uint32_t)) {
		const auto id = getReverseData<uint32_t>(msg);
		m_handler->onSetIdMsg(id);
	}
}


void Driver::handleRecvMsgSetSamplingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = getReverseData<uint16_t>(msg);
		m_handler->onSetSamplingPeriodMsg(period);
	}
}


void Driver::handleRecvMsgSetSendingPeriod(const byte* msg, size_t size)
{
	if (size == sizeof(uint16_t)) {
		const auto period = getReverseData<uint16_t>(msg);
		m_handler->onSetSendingPeriodMsg(period);
	}
}


void Driver::handleRecvMsgSetTime(const byte* msg, size_t size)
{
    if (size == sizeof(uint16_t)) {
        const auto time = getReverseData<uint32_t>(msg);
        m_handler->onSetTime(time);
    }
}

void Driver::handleRecvMsgSetSettings(const byte * msg, size_t size)
{
    if (size == sizeof(uint8_t) + sizeof(uint32_t)) {
        const auto samplingPeriod = getReverseData<uint16_t>(msg);
        const auto sandingPeriod = getReverseData<uint16_t>(msg + sizeof(samplingPeriod));
        const auto dayCost = getReverseData<uint16_t>(msg + sizeof(samplingPeriod) + sizeof(sandingPeriod));
        const auto nightCost = getReverseData<uint16_t>(msg + sizeof(samplingPeriod) + sizeof(sandingPeriod) + sizeof(dayCost));
        const auto dayStartTime = getReverseData<uint32_t>(msg + sizeof(samplingPeriod) + sizeof(sandingPeriod) + 
            sizeof(dayCost) + sizeof(nightCost));
        const auto nightStartTime = getReverseData<uint32_t>(msg + sizeof(samplingPeriod) + sizeof(sandingPeriod) +
            sizeof(dayCost) + sizeof(nightCost) + sizeof(dayStartTime));
        m_handler->onSetSettings(samplingPeriod, sandingPeriod, dayCost, nightCost, dayStartTime, nightStartTime);
    }
}


void Driver::handleRecvMsgReserve(const byte* msg, size_t size)
{
#ifdef DEBUG
	Serial.println(F("[DEBUG] Handle recv msg reserve"));
#endif

	if (size == sizeof(uint8_t) + sizeof(uint32_t)) {
		const auto placeId = getReverseData<uint8_t>(msg);
		const auto time = getReverseData<uint32_t>(msg + sizeof(placeId));
		m_handler->onReserveMsg(placeId, time);
	}
}


void Driver::handleRecvMsgCancelReservation(const byte* msg, size_t size)
{
	if (size == sizeof(uint8_t)) {
		const auto placeId = getReverseData<uint8_t>(msg);
		m_handler->onCancelReservationMsg(placeId);
	}
}


void Driver::handleRecvMsgSetDayCost(const byte* msg, size_t size)
{
    if (size == sizeof(uint16_t)) {
        const auto cost = getReverseData<uint16_t>(msg);
        m_handler->onSetDayCost(cost);
    }
}

void Driver::handleRecvMsgSetNightCost(const byte* msg, size_t size)
{
    if (size == sizeof(uint16_t)) {
        const auto cost = getReverseData<uint16_t>(msg);
        m_handler->onSetNightCost(cost);
    }
}

void Driver::handleRecvMsgSetDayStartTime(const byte* msg, size_t size)
{
    if (size == sizeof(uint16_t)) {
        const auto time = getReverseData<uint16_t>(msg);
        m_handler->onSetDayStartTime(time);
    }
}

void Driver::handleRecvMsgSetNightStartTime(const byte* msg, size_t size)
{
    if (size == sizeof(uint16_t)) {
        const auto time = getReverseData<uint16_t>(msg);
        m_handler->onSetNightStartTime(time);
    }
}
