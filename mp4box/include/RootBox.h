#pragma once

#include "Box.h"

struct RootBox:public Box
{
    int64_t Parse(IOBase* io) override;
};