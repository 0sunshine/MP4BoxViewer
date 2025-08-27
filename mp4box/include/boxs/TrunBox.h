#pragma once

#include "FullBox.h"

#include <optional>

struct TrunBox:public FullBox
{
    struct Entry
    {
        std::optional<uint32_t> _sampleDuration;
        std::optional<uint32_t> _sampleSize;
        std::optional<uint32_t> _sampleFlags;
        std::optional<int64_t> _sampleCompositionTimeOffset;
    };

    uint32_t _sampleCount = 0;
    std::optional<int32_t> _dataOffset;
    std::optional<uint32_t> _firstSampleFlags;

    std::vector<Entry> _entrys;

    int64_t Parse(IOBase* io) override;
};