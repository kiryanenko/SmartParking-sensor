#pragma once
#include "ReceiverTransmitter.h"


class SerialModule : public ReceiverTransmitter
{
public:
	SerialModule(AbstractReceiveMessageHandler *handler);
	~SerialModule();

	bool send(const byte *data, size_t size) override;
	bool available() override;
	byte* recv(size_t &size) override;
};

