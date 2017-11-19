#include "SerialModule.h"



SerialModule::SerialModule()
{
}


SerialModule::~SerialModule()
{
}

bool SerialModule::send(const byte *data, size_t size)
{
	const auto sendedCount = Serial.write(data, size);
	Serial.println();
	return sendedCount == size;
}
