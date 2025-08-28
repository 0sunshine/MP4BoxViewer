#pragma once

#include <stdint.h>

class IOBase
{
public:
    enum class SeeKDirection
    {
        Begin,
        Curr
    };

    virtual bool SeekTo(int64_t pos, SeeKDirection dir = SeeKDirection::Begin) = 0;
    virtual int64_t GetCurrPos() = 0;

    virtual bool Read(uint8_t* buffer, int64_t wantSize) = 0;

    virtual bool Eof() = 0;
};