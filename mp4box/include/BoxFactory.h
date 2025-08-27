#pragma once

#include "Box.h"
#include <stdint.h>

class BoxFactory
{
public:
    static Box* GetBoxByType(const char* type);
};