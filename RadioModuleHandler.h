#pragma once
#include "ReceiveMessageHandler.h"
class RadioModuleHandler :
	public ReceiveMessageHandler
{
public:
	RadioModuleHandler();
	~RadioModuleHandler();

	void onRecvMsgSetId(uint32_t id) override {}
};

