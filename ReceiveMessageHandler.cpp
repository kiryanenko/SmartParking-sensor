#include "ReceiveMessageHandler.h"


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
	params.setId(period);
}


void ReceiveMessageHandler::onSetSendingPeriodMsg(const uint16_t period)
{
	auto& params = Parameters::instance();
	params.setId(period);
}


void ReceiveMessageHandler::onReserveMsg(const uint8_t parkingPlaceId, const uint16_t time)
{
	Serial.print("[DEBUG] Reserve parking place ");
	Serial.print(parkingPlaceId);
	Serial.print(" on time ");
	Serial.println(time);

	if (parkingPlaceId < m_parkingPlacesCount) {
		m_parkingPlaces[parkingPlaceId].reserve(time);
	}
}


void ReceiveMessageHandler::onCancelReservationMsg(const uint8_t parkingPlaceId)
{
	if (parkingPlaceId < m_parkingPlacesCount) {
		m_parkingPlaces[parkingPlaceId].cancelReservation();
	}
}
