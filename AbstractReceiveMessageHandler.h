#pragma once
#include <Arduino.h>

class AbstractReceiveMessageHandler
{
public:
	AbstractReceiveMessageHandler();
	virtual ~AbstractReceiveMessageHandler();

	virtual void onSetIdMsg(uint32_t id) = 0;
	virtual void onSetSamplingPeriodMsg(uint16_t period) = 0;
	virtual void onSetSendingPeriodMsg(uint16_t period) = 0;

	virtual void onReserveMsg(uint8_t parkingPlaceId, uint16_t time) = 0;
	virtual void onCancelReservationMsg(uint8_t parkingPlaceId) = 0;
};
