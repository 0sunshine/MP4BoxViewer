#include "Box.h"
#include "BoxFactory.h"
#include "Util.h"

#include <iostream>

int64_t Box::Parse(IOBase* io)
{
    if( !io->SeekTo(_ioStartPos) )
    {
        return -1;
    }


    if( !io->SeekTo(_size, IOBase::SeeKDirection::Curr) )
    {
        return -1;
    }

    return _size;
}

void Box::GetBoxsByType(std::vector<Box*>& boxs, const std::string& type)
{
    if(type == _type)
    {
        boxs.push_back(this);
    }

    for(auto& sub : _subBoxs)
    {
        sub->GetBoxsByType(boxs, type);
    }
}

Box* Box::GetOneBox(IOBase* io, Box* specifiedBox)
{
    int64_t ioStartPos = io->GetCurrPos();

    uint32_t size = 0;
    if( !io->Read(reinterpret_cast<uint8_t*>(&size), 4) )
    {
        return nullptr;
    }
    ByteOrderReverse(size);

    char type[5] = {};
    io->Read(reinterpret_cast<uint8_t*>(type), 4);

    Box* box = specifiedBox;
    if (!box)
    {
        box = BoxFactory::GetBoxByType(type);
    }
        
    box->_ioStartPos = ioStartPos;
    box->_size = size;
    memcpy(box->_type, type, 4);

    if (box->_size == 1) {
        uint64_t largeSize = 0;
        io->Read(reinterpret_cast<uint8_t*>(&largeSize), 8);
        ByteOrderReverse(largeSize);
        box->_size = largeSize;
    }

    if (box->_type[0] == 'u' && box->_type[1] == 'u' && box->_type[2] == 'i' &&
        box->_type[3] == 'd') {

        io->Read(reinterpret_cast<uint8_t*>(box->_userType), 16);
    }

    box->_ioBodyPos = io->GetCurrPos();
    return box;
}
