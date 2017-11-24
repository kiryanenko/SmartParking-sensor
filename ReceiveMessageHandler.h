#pragma once
#include "AbstractReceiveMessageHandler.h"
#include "Parameters.h"

class ReceiveMessageHandler :
	public AbstractReceiveMessageHandler
{
public:
	ReceiveMessageHandler();
	~ReceiveMessageHandler();

	void onRecvMsgSetId(uint32_t id) override;
	void onRecvMsgSetSamplingPeriod(uint16_t period) override;
	void onRecvMsgSetSendingPeriod(uint16_t period) override;
};

