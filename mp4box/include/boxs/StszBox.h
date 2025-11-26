#pragma once

#include "FullBox.h"

#include <optional>

struct StszBox : public FullBox
{
    uint32_t _sampleSize = 0;
    uint32_t _sampleCount = 0;
    std::vector<uint32_t> _entrySizes;

    int64_t Parse(IOBase* io) override;
};