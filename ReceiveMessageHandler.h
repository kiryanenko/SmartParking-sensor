#pragma once
#include "AbstractReceiveMessageHandler.h"
#include "ParkingPlace.h"

class ReceiveMessageHandler :
    public AbstractReceiveMessageHandler
{
    ParkingPlace* m_parkingPlaces;
    uint8_t m_parkingPlacesCount;

public:
    ReceiveMessageHandler(ParkingPlace* parkingPlaces, uint8_t parkingPlacesCount);
    ~ReceiveMessageHandler() = default;

    void onSetIdMsg(uint32_t id) override;
    void onSetSamplingPeriodMsg(uint16_t period) override;
    void onSetSendingPeriodMsg(uint16_t period) override;
    void onSetTime(time_t time) override;

    void onReserveMsg(uint8_t parkingPlaceId, uint32_t time) override;
    void onCancelReservationMsg(uint8_t parkingPlaceId) override;

    void onSetDayCost(uint16_t cost) override;
    void onSetNightCost(uint16_t cost) override;
    void onSetDayStartTime(uint16_t time) override;
    void onSetNightStartTime(uint16_t time) override;
};
