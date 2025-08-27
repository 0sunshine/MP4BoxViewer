#include "IOFStream.h"

bool IOFStream::OpenFile(const std::string& path)
{
    _in.open(path, std::ios::binary);

    if(!_in)
    {
        return false;
    }

    return true;
}

int64_t IOFStream::GetFileSize()
{
    int64_t record = _in.tellg();

    _in.seekg(0, std::ios::end);
    int64_t end = _in.tellg();

    _in.seekg(record);

    return end;
}

bool IOFStream::SeekTo(int64_t pos, SeeKDirection dir)
{
    switch (dir) {
        case SeeKDirection::Begin:
            _in.seekg(pos);
            break;
        case SeeKDirection::Curr:
            _in.seekg(pos, std::ios::cur);
            break;
        default:
            return false;
    }

    return !_in.bad();
}

int64_t IOFStream::GetCurrPos()
{
    return _in.tellg();
}

bool IOFStream::Read(uint8_t* buffer, int64_t wantSize)
{
    _in.read(reinterpret_cast<char*>(buffer), wantSize);

    return _in.gcount() == wantSize;
}
