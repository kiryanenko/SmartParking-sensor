#include "SerialModule.h"



SerialModule::SerialModule()
{
}


SerialModule::~SerialModule()
{
}

bool SerialModule::send(const byte data[])
{
	const auto sendedCount = Serial.println(reinterpret_cast<const char *>(data));
	return sendedCount == sizeof(data);
}
