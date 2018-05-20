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
    virtual void onSetSettings(uint16_t samplingPeriod, uint16_t sendingPeriod, 
        uint16_t dayCost, uint16_t nightCost, uint32_t dayStartTime, uint32_t nightStartTime) = 0;

	virtual void onReserveMsg(uint8_t parkingPlaceId, uint32_t time) = 0;
	virtual void onCancelReservationMsg(uint8_t parkingPlaceId) = 0;

    virtual void onSetDayCost(uint16_t cost) = 0;
    virtual void onSetNightCost(uint16_t cost) = 0;
    virtual void onSetDayStartTime(uint16_t time) = 0;
    virtual void onSetNightStartTime(uint16_t time) = 0;
};

