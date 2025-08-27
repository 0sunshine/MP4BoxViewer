#pragma once

#include "IOBase.h"

#include <stdint.h>
#include <vector>
#include <optional>

struct Box
{
    uint64_t _size = 0;
    char _type[5] = {};
    char _userType[17] = {};
    std::vector<Box*> _subBoxs;

    int64_t _ioStartPos = 0;

    virtual int64_t Parse(IOBase* io);
    
protected:
    Box* GetOneBox(IOBase* io);
};