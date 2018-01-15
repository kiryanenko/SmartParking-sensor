#pragma once
#include <Arduino.h>
#include <Time.h>

class AbstractReceiveMessageHandler
{
public:
	AbstractReceiveMessageHandler();
	virtual ~AbstractReceiveMessageHandler();

	virtual void onSetIdMsg(uint32_t id) = 0;
	virtual void onSetSamplingPeriodMsg(uint16_t period) = 0;
	virtual void onSetSendingPeriodMsg(uint16_t period) = 0;
    virtual void onSetTime(time_t time) = 0;

	virtual void onReserveMsg(uint8_t parkingPlaceId, uint16_t time) = 0;
	virtual void onCancelReservationMsg(uint8_t parkingPlaceId) = 0;

    virtual void onSetDayCost(uint16_t cost) = 0;
    virtual void onSetNightCost(uint16_t cost) = 0;
    virtual void onSetDayStartTime(uint16_t time) = 0;
    virtual void onSetNightStartTime(uint16_t time) = 0;
};

