#pragma once
#include "ReceiveMessageHandler.h"
class RadioModuleHandler :
	public ReceiveMessageHandler
{
public:
	RadioModuleHandler(ParkingPlace *parkingPlaces, uint8_t parkingPlacesCount);
	~RadioModuleHandler();

	void onSetIdMsg(uint32_t id) override {}
};

