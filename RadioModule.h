#pragma once
#include "Driver.h"

#include <RadioHead\RH_RF95.h>

#define FREQUENCY 868.0

class RadioModule : public Driver
{
	RH_RF95 m_rf95;
	int m_pinResetLora;
	int m_timeout;

public:
	RadioModule(int pinResetLora, int timeout, AbstractReceiveMessageHandler *handler);
	~RadioModule();

	bool init() override;
	bool send(const byte *data, size_t size) override;
	bool available() override;
	byte* recv(size_t &size) override;

private:
	void reset() const;
};
