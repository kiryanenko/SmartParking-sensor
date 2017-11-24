#include "RadioModuleHandler.h"



RadioModuleHandler::RadioModuleHandler(ParkingPlace *parkingPlaces, uint8_t parkingPlacesCount) :
	ReceiveMessageHandler(parkingPlaces, parkingPlacesCount)
{
}


RadioModuleHandler::~RadioModuleHandler()
{
}
