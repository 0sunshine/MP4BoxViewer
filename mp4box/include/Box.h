#pragma once

#include "IOBase.h"

#include <stdint.h>
#include <vector>
#include <optional>
#include <string>

struct Box
{
    uint64_t _size = 0;
    char _type[5] = {};
    char _userType[17] = {};
    std::vector<Box*> _subBoxs;

    int64_t _ioStartPos = 0;
    int64_t _ioBodyPos = 0;

    virtual int64_t Parse(IOBase* io);

    void GetBoxsByType(std::vector<Box*>& boxs, const std::string& type);

protected:
    Box* GetOneBox(IOBase* io);
};