#pragma once

#include "IOBase.h"

#include <fstream>
#include <string>

class IOFStream: public IOBase
{
public:
    bool OpenFile(const std::string& path);
    void Close();

    int64_t GetFileSize();

    bool SeekTo(int64_t pos, SeeKDirection dir = SeeKDirection::Begin) override;
    int64_t GetCurrPos() override;

    bool Read(uint8_t* buffer, int64_t wantSize) override;

    bool Eof() override;

private:
    std::ifstream _in;
};