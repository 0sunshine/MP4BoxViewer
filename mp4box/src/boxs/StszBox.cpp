#include "boxs/StszBox.h"
#include "Util.h"

#include <iostream>

int64_t StszBox::Parse(IOBase* io)
{
    int64_t _ioCurrPos = io->GetCurrPos();

    if (FullBox::Parse(io) < 0) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_sampleSize), 4)) {
        return -1;
    }
    ByteOrderReverse(_sampleSize);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_sampleCount), 4)) {
        return -1;
    }
    ByteOrderReverse(_sampleCount);


    if (_sampleSize == 0)
    {
        for (int i = 1; i <= _sampleCount; ++i)
        {
            uint32_t entrySize = 0;
            if (!io->Read(reinterpret_cast<uint8_t*>(&entrySize),4)) {
                return -1;
            }
            ByteOrderReverse(entrySize);

            _entrySizes.push_back(entrySize);
        }
    }

    return io->GetCurrPos() - _ioCurrPos;
}
