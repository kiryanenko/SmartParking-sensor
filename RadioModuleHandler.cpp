#include "RadioModuleHandler.h"



RadioModuleHandler::RadioModuleHandler(ParkingPlace *parkingPlaces, const uint8_t parkingPlacesCount) :
	ReceiveMessageHandler(parkingPlaces, parkingPlacesCount)
{
}


RadioModuleHandler::~RadioModuleHandler()
{
}
