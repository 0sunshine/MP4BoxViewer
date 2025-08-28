#pragma once

#include "Box.h"

#include <optional>

struct RinfBox : public Box
{
    int64_t Parse(IOBase* io) override;
};