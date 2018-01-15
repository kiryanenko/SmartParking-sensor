#include "ReceiveMessageHandler.h"

#include <DS3232RTC.h>

ReceiveMessageHandler::ReceiveMessageHandler(ParkingPlace *parkingPlaces, const uint8_t parkingPlacesCount) :
	m_parkingPlaces(parkingPlaces), m_parkingPlacesCount(parkingPlacesCount)
{
}


ReceiveMessageHandler::~ReceiveMessageHandler()
{
}


void ReceiveMessageHandler::onSetIdMsg(const uint32_t id)
{
	auto& params = Parameters::instance();
	params.setId(id);
}


void ReceiveMessageHandler::onSetSamplingPeriodMsg(const uint16_t period)
{
	auto& params = Parameters::instance();
	params.setSensorSamplingPeriod(period);
}


void ReceiveMessageHandler::onSetSendingPeriodMsg(const uint16_t period)
{
	auto& params = Parameters::instance();
	params.setSendingPeriod(period);
}

void ReceiveMessageHandler::onSetTime(const time_t time)
{
    RTC.set(time);
    setSyncProvider(RTC.get);
}


void ReceiveMessageHandler::onReserveMsg(const uint8_t parkingPlaceId, const uint16_t time)
{
#ifdef DEBUG
	Serial.print(F("[DEBUG] Reserve parking place "));
	Serial.print(parkingPlaceId);
	Serial.print(F(" on time "));
	Serial.println(time);
#endif

	if (parkingPlaceId > 0 && parkingPlaceId <= m_parkingPlacesCount) {
		m_parkingPlaces[parkingPlaceId - 1].reserve(time);
	}
}


void ReceiveMessageHandler::onCancelReservationMsg(const uint8_t parkingPlaceId)
{
	if (parkingPlaceId < m_parkingPlacesCount) {
		m_parkingPlaces[parkingPlaceId].cancelReservation();
	}
}

void ReceiveMessageHandler::onSetDayCost(const uint16_t cost)
{
    auto& params = Parameters::instance();
    params.setDayCost(cost);
}

void ReceiveMessageHandler::onSetNightCost(const uint16_t cost)
{
    auto& params = Parameters::instance();
    params.setNightCost(cost);
}

void ReceiveMessageHandler::onSetDayStartTime(const uint16_t time)
{
    auto& params = Parameters::instance();
    params.setDayStartTime(time);
}

void ReceiveMessageHandler::onSetNightStartTime(const uint16_t time)
{
    auto& params = Parameters::instance();
    params.setNightStartTime(time);
}
