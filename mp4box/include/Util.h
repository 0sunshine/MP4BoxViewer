#pragma once

#include <type_traits>
#include <vector>

template<typename T>
void ByteOrderReverse(T& value)
{
    static_assert(std::is_integral_v<T>, "must be a integral");

    T copy = value;
    char* pCopy = reinterpret_cast<char*>(&copy);

    char* pValue = reinterpret_cast<char*>(&value);

    for (int i = 0; i < sizeof(T); ++i)
    {
        pValue[i] = pCopy[sizeof(T) - i - 1];
    }
}

void ByteOrderReverse(uint8_t* p, int len);