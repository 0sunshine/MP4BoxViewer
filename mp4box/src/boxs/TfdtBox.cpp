#include "boxs/TfdtBox.h"
#include "Util.h"

#include <iostream>

int64_t TfdtBox::Parse(IOBase* io)
{
    int64_t _ioCurrPos = io->GetCurrPos();

    if (FullBox::Parse(io) < 0) {
        return -1;
    }

    if(_version == 1)
    {
        if (!io->Read(reinterpret_cast<uint8_t*>(&_baseMediaDecodeTime), 8)) {
            return -1;
        }
        ByteOrderReverse(_baseMediaDecodeTime);
    }
    else
    {
        uint32_t baseMediaDecodeTime32 = 0;
        if (!io->Read(reinterpret_cast<uint8_t*>(&baseMediaDecodeTime32), 4)) {
            return -1;
        }
        ByteOrderReverse(baseMediaDecodeTime32);

        _baseMediaDecodeTime = baseMediaDecodeTime32;
    }

    return io->GetCurrPos() - _ioCurrPos;
}
