#pragma once

#include "Box.h"

struct FullBox: public Box
{
    uint8_t _version;
    uint8_t _bit[3];
};