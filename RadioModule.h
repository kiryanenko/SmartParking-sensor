#pragma once

#include <RadioHead-master/RH_RF95.h>


class RadioModule
{
	RH_RF95 m_rf95;

	const byte type_send_msg_parking_status = 'M';

public:
	RadioModule();
	~RadioModule();

	bool init();
	void sendParkingStatus(uint16_t ID, byte parkingPlaceId, bool isFree);
};

