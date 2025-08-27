#pragma once

#include "Box.h"

struct ContainerBox:public Box
{
    int64_t Parse(IOBase* io) override;
};