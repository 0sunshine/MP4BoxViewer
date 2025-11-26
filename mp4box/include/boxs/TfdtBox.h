#pragma once

#include "FullBox.h"

#include <optional>

struct TfdtBox : public FullBox
{
    uint64_t _baseMediaDecodeTime = 0;

    int64_t Parse(IOBase* io) override;
};