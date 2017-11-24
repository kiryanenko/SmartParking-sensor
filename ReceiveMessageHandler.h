#pragma once
#include "AbstractReceiveMessageHandler.h"
#include "Parameters.h"
#include "ParkingPlace.h"

class ReceiveMessageHandler :
	public AbstractReceiveMessageHandler
{
	ParkingPlace *m_parkingPlaces;
	uint8_t m_parkingPlacesCount;

public:
	ReceiveMessageHandler(ParkingPlace *parkingPlaces, uint8_t parkingPlacesCount);
	~ReceiveMessageHandler();

	void onSetIdMsg(uint32_t id) override;
	void onSetSamplingPeriodMsg(uint16_t period) override;
	void onSetSendingPeriodMsg(uint16_t period) override;

	void onReserveMsg(uint8_t parkingPlaceId, uint16_t time) override;
	void onCancelReservationMsg(uint8_t parkingPlaceId) override;
};

