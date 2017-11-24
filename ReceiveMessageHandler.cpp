#include "ReceiveMessageHandler.h"



ReceiveMessageHandler::ReceiveMessageHandler()
{
}


ReceiveMessageHandler::~ReceiveMessageHandler()
{
}


void ReceiveMessageHandler::onRecvMsgSetId(const uint32_t id)
{
	auto& params = Parameters::instance();
	params.setId(id);
}


void ReceiveMessageHandler::onRecvMsgSetSamplingPeriod(const uint16_t period)
{
	auto& params = Parameters::instance();
	params.setId(period);
}


void ReceiveMessageHandler::onRecvMsgSetSendingPeriod(const uint16_t period)
{
	auto& params = Parameters::instance();
	params.setId(period);
}
