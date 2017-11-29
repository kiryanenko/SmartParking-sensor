#pragma once

template <typename T>
T getReverseData(const void *src)
{
	size_t size = sizeof(T);
	T res;
	memcpy(&res, src, size);
	auto p = (uint8_t *) &res;
	for (size_t i = 0; i < size / 2; ++i) {
		uint8_t temp = p[i];
		p[i] = p[size - i - 1];
		p[size - i - 1] = temp;
	}
	return res;
}


template <typename T>
void cpyReverseData(void *dst, const T &data)
{
	T reverseData = getReverseData<T>(data);
	memcpy(dst, reverseData, sizeof(T));
}
