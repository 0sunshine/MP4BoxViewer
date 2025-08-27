#pragma once

#include "Box.h"

struct FullBox: public Box
{
    uint8_t _version = 0;
    uint32_t _flags = 0; //24bit

    virtual int64_t Parse(IOBase* io);
};