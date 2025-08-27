#include "boxs/TrunBox.h"
#include "Util.h"

#include <iostream>

int64_t TrunBox::Parse(IOBase* io)
{
    if( FullBox::Parse(io) < 0 )
    {
        return -1;
    }

    int64_t _ioCurrPos = io->GetCurrPos();

    if (!io->Read(reinterpret_cast<uint8_t*>(&_sampleCount), 4)) {
        return -1;
    }
    ByteOrderReverse(_sampleCount);

    if (_flags & 0x000001)
    {
        int32_t dataOffset = 0;
        if (!io->Read(reinterpret_cast<uint8_t*>(&dataOffset), 4)) {
            return -1;
        }
        ByteOrderReverse(dataOffset);

        _dataOffset = dataOffset;
    }

    if (_flags & 0x000004) {
        uint32_t firstSampleFlags = 0;
        if (!io->Read(reinterpret_cast<uint8_t*>(&firstSampleFlags), 4)) {
            return -1;
        }
        ByteOrderReverse(firstSampleFlags);

        _firstSampleFlags = firstSampleFlags;
    }

    for (uint32_t i = 0; i < _sampleCount; ++i)
    {
        Entry entry;

        if (_flags & 0x000100) {
            uint32_t sampleDuration = 0;
            if (!io->Read(reinterpret_cast<uint8_t*>(&sampleDuration), 4)) {
                return -1;
            }
            ByteOrderReverse(sampleDuration);

            entry._sampleDuration = sampleDuration;
        }

        if (_flags & 0x000200) {
            uint32_t sampleSize = 0;
            if (!io->Read(reinterpret_cast<uint8_t*>(&sampleSize), 4)) {
                return -1;
            }
            ByteOrderReverse(sampleSize);

            entry._sampleSize = sampleSize;
        }

        if (_flags & 0x000400) {
            uint32_t sampleFlags = 0;
            if (!io->Read(reinterpret_cast<uint8_t*>(&sampleFlags), 4)) {
                return -1;
            }
            ByteOrderReverse(sampleFlags);

            entry._sampleFlags = sampleFlags;
        }

        if (_flags & 0x000800) {
            uint32_t timeOffset = 0;
            if (!io->Read(reinterpret_cast<uint8_t*>(&timeOffset), 4)) {
                return -1;
            }
            ByteOrderReverse(timeOffset);

            if(_version == 0){
                entry._sampleCompositionTimeOffset = (int32_t)timeOffset;
            }else{
                entry._sampleCompositionTimeOffset = (uint32_t)timeOffset;
            }
        }

        _entrys.push_back(entry);
    }

    int64_t _ioCurrPos2 = io->GetCurrPos();
    return _ioCurrPos2 - _ioCurrPos;
}
