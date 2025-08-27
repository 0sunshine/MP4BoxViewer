#pragma once

#include "FullBox.h"

#include <optional>

struct TfhdBox: public FullBox
{
    struct Entry
    {
        std::optional<uint64_t> _baseDataOffset;
        std::optional<uint32_t> _sampleDescIndex;
        std::optional<uint32_t> _defaultSampleDuration;
        std::optional<uint32_t> _defaultSampleSize;
        std::optional<uint32_t> _defaultSampleFlags;
    };

    uint32_t _trackID;

    int64_t Parse(IOBase* io) override;
};