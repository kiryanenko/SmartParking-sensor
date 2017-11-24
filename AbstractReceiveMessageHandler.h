#pragma once
#include <Arduino.h>

class AbstractReceiveMessageHandler
{
public:
	AbstractReceiveMessageHandler();
	virtual ~AbstractReceiveMessageHandler();

	virtual void onRecvMsgSetId(uint32_t id) = 0;
	virtual void onRecvMsgSetSamplingPeriod(uint16_t period) = 0;
	virtual void onRecvMsgSetSendingPeriod(uint16_t period) = 0;
};

