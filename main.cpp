#include <iostream>

#include "IOFStream.h"
#include "RootBox.h"

int main(int, char**)
{
    RootBox rootBox;
    IOFStream fin;

    if( !fin.OpenFile("D:/task/vr/Test_track11.1.mp4") )
    {
        std::cout << "open file error" << std::endl;
    }

    rootBox._size = fin.GetFileSize();

    rootBox.Parse(&fin);

    std::cout << "box num: " << rootBox._subBoxs.size() << std::endl;
}
