#pragma once
#include "ReceiverTransmitter.h"

#include <RadioHead-master\RH_RF95.h>

#define FREQUENCY 868.0

class RadioModule : public ReceiverTransmitter
{
	RH_RF95 m_rf95;

public:
	RadioModule();
	~RadioModule();

	bool init() override;
	bool send(const byte data[]) override;
};
