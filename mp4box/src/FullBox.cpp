#include "FullBox.h"
#include "Util.h"

int64_t FullBox::Parse(IOBase* io) 
{
    int64_t _ioCurrPos = io->GetCurrPos();

    if (!io->Read(reinterpret_cast<uint8_t*>(&_version), 1)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_flags), 3)) {
        return -1;
    }
    ByteOrderReverse(reinterpret_cast<uint8_t*>(&_flags), 3);

    _ioBodyPos = io->GetCurrPos();

    return _ioBodyPos - _ioCurrPos;
}