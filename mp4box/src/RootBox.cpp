#include "RootBox.h"
#include "Util.h"

#include <iostream>

int64_t RootBox::Parse(IOBase* io)
{
    int64_t _ioCurrPos = io->GetCurrPos();

    while(_ioCurrPos < _ioStartPos + _size)
    {
        Box* subBox = GetOneBox(io);
        if (subBox->Parse(io) < 0) {
            delete subBox;
            std::cout << "subBox->Parse < 0" << std::endl;
            break;
        } else {
            _subBoxs.push_back(subBox);
        }

        _ioCurrPos = io->GetCurrPos();
    }

    return _ioCurrPos;
}
