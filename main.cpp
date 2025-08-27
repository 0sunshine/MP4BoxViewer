#include <iostream>

#include "IOFStream.h"
#include "RootBox.h"
#include "boxs/TrunBox.h"

int main(int, char**)
{
    RootBox rootBox;
    IOFStream fin;

    if( !fin.OpenFile("D:/task/vr/Test_track11.2.mp4") )
    {
        std::cout << "open file error" << std::endl;
    }

    rootBox._size = fin.GetFileSize();

    rootBox.Parse(&fin);

    std::cout << "box num: " << rootBox._subBoxs.size() << std::endl;

    std::vector<Box*> trunBoxs;
    rootBox.GetBoxsByType(trunBoxs,"trun");

    std::vector<Box*> mdatBoxs;
    rootBox.GetBoxsByType(mdatBoxs, "mdat");

    if (trunBoxs.size() != 1 || mdatBoxs.size() != 1)
    {
        std::cout << "trunBoxs.size() != 1 || mdatBoxs != 1, quit" << std::endl;
        return -1;
    }

    TrunBox* trunBox = static_cast<TrunBox*>(trunBoxs[0]);
    Box* mdatBox = mdatBoxs[0];

    fin.SeekTo(mdatBox->_ioBodyPos);

    std::vector<uint8_t> firstFrameData;
    firstFrameData.resize(trunBox->_entrys[0]._sampleSize.value());

    fin.Read(&firstFrameData[0], firstFrameData.size());


    uint8_t type = (firstFrameData[0] >> 1) & 0x3F;
    std::cout << "nalu type: " << (int)type << std::endl;

    std::cout << "end............" << std::endl;
}
