#include "SerialModule.h"


SerialModule::SerialModule(AbstractReceiveMessageHandler *handler) :
	ReceiverTransmitter(handler)
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


bool SerialModule::available()
{
	return Serial.available() > 0;
}


byte* SerialModule::recv(size_t &size)
{
	size = 0;
	const auto len = Serial.read();

	if (len <= 0) {
		return nullptr;
	}

	const auto buf = new uint8_t[len];
	for (; size < len && available(); ++size) {
		buf[size] = Serial.read();
	}

	if (size != len) {
		delete[] buf;
		return nullptr;
	}

	return buf;
}
