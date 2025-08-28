#include <iostream>
#include <format>

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

    if (rootBox.Parse(&fin) < 0)
    {
        std::cout << "rootBox parser error" << std::endl;
        return -1;
    }

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

    int idx = 0;
    for (auto entry : trunBox->_entrys)
    {
        ++idx;

        std::vector<uint8_t> frameData;
        frameData.resize(entry._sampleSize.value());

        
        if (!fin.Read(&frameData[0], frameData.size()))
        {
            std::cout << "error............" << std::endl;
            return -1;
        }

        // first 4 bytes is sample length
        uint8_t type = (frameData[4] >> 1) & 0x3F;

        
        std::cout << std::format("No.{} sample, len: {}, nalu type: {}",
                                 idx,
                                 frameData.size(), type)
                  << std::endl;
    }
    
    std::cout << "end............" << std::endl;
}
