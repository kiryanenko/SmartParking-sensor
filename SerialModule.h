#pragma once
#include "ReceiverTransmitter.h"


class SerialModule : public ReceiverTransmitter
{
public:
	SerialModule();
	~SerialModule();

	bool send(const byte data[]) override;
};

