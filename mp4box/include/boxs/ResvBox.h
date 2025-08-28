#pragma once

#include "boxs/StsdBox.h"

#include <optional>

struct ResvBox: public VisualSampleEntry
{
    int64_t Parse(IOBase* io) override;
};