#include "boxs/StsdBox.h"
#include "Util.h"

#include <iostream>
#include "boxs/StsdBox.h"

int64_t StsdBox::Parse(IOBase* io)
{
    if (FullBox::Parse(io) < 0) {
        return -1;
    }

    int64_t ioStsdBodyStartPos = io->GetCurrPos();

    if (!io->Read(reinterpret_cast<uint8_t*>(&_entryCount), 4)) {
        return -1;
    }
    ByteOrderReverse(_entryCount);

    for (int i = 0; i < _entryCount; ++i) {
        Box* entry = GetOneBox(io);
        if (entry->Parse(io) < 0) {
            delete entry;
            std::cout << "entry Parse < 0" << std::endl;
            return -1;
        } else {
            _sampleEntrys.push_back(entry);
        }
    }

    int64_t readSize = io->GetCurrPos() - _ioStartPos;

    return readSize;
}

void StsdBox::GetBoxsByType(std::vector<Box*>& boxs, const std::string& type)
{
    Box::GetBoxsByType(boxs, type);

    for (auto& entry : _sampleEntrys) {
        entry->GetBoxsByType(boxs, type);
    }
}

int64_t SampleEntry::Parse(IOBase* io)
{
    int64_t _ioCurrPos = io->GetCurrPos();

    if (!io->Read(reinterpret_cast<uint8_t*>(&_reserved), 6)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_dataReferenceIndex), 2)) {
        return -1;
    }
    ByteOrderReverse(reinterpret_cast<uint8_t*>(&_dataReferenceIndex), 2);

    int64_t _ioCurrPos2 = io->GetCurrPos();

    return _ioCurrPos2 - _ioCurrPos;
}

int64_t VisualSampleEntry::Parse(IOBase* io)
{
    if (SampleEntry::Parse(io) < 0) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_preDefined1), 2)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_reserved1), 2)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_preDefined2), 12)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_width), 2)) {
        return -1;
    }
    ByteOrderReverse(_width);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_height), 2)) {
        return -1;
    }
    ByteOrderReverse(_height);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_horizresolution), 4)) {
        return -1;
    }
    ByteOrderReverse(_horizresolution);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_vertresolution), 4)) {
        return -1;
    }
    ByteOrderReverse(_vertresolution);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_reserved2), 4)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_frameCount), 2)) {
        return -1;
    }
    ByteOrderReverse(_frameCount);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_compressorname), 32)) {
        return -1;
    }

    if (!io->Read(reinterpret_cast<uint8_t*>(&_depth), 2)) {
        return -1;
    }
    ByteOrderReverse(_depth);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_preDefined3), 2)) {
        return -1;
    }

    int64_t ioCurrPos = io->GetCurrPos();

    return ioCurrPos - _ioBodyPos;
}

int64_t HevcSampleEntry::Parse(IOBase* io)
{
    if (VisualSampleEntry::Parse(io) < 0) {
        return -1;
    }

    int64_t _ioCurrPos = io->GetCurrPos();

    while (_ioCurrPos < _ioStartPos + _size) {
        Box* subBox = GetOneBox(io);
        if (subBox->Parse(io) < 0) {
            delete subBox;
            std::cout << "subBox->Parse < 0" << std::endl;
            return -1;
        } else {
            _subBoxs.push_back(subBox);
        }

        _ioCurrPos = io->GetCurrPos();
    }

    return _ioCurrPos - _ioStartPos;
}

int64_t HEVCConfigurationBox::Parse(IOBase* io)
{
    if (!io->Read(
          reinterpret_cast<uint8_t*>(&_HEVCConifg._configurationVersion), 1)) {
        return -1;
    }

    uint8_t b = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
        return -1;
    }
    _HEVCConifg._generalProFileSpace = b & 0xC0;
    _HEVCConifg._generalTierFlag = b & 0x20;
    _HEVCConifg._generalProFileSpace = b & 0x1F;

    if (!io->Read(
          reinterpret_cast<uint8_t*>(&_HEVCConifg._generalProFileCompatFlags),
          4)) {
        return -1;
    }
    ByteOrderReverse(_HEVCConifg._generalProFileCompatFlags);

    if (!io->Read(
          reinterpret_cast<uint8_t*>(&_HEVCConifg._generalConstIndicatorFlags),
          6)) {
        return -1;
    }
    ByteOrderReverse((uint8_t*)&_HEVCConifg._generalConstIndicatorFlags, 6);

    if (!io->Read(reinterpret_cast<uint8_t*>(&_HEVCConifg._generalLevelIdc),
                  1)) {
        return -1;
    }
    ByteOrderReverse(_HEVCConifg._generalLevelIdc);

    uint16_t b2 = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b2), 2)) {
        return -1;
    }
    _HEVCConifg._reserved1 = b2 & 0xF000;
    _HEVCConifg._minSpatialSegIdc = b2 & 0x0FFF;
    ByteOrderReverse(_HEVCConifg._minSpatialSegIdc);

    b = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
        return -1;
    }
    _HEVCConifg._reserved2 = b & 0xFC;
    _HEVCConifg._parallelismType = b & 0x3;

    b = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
        return -1;
    }
    _HEVCConifg._reserved3 = b & 0xFC;
    _HEVCConifg._chroma_format_idc = b & 0x3;

    b = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
        return -1;
    }
    _HEVCConifg._reserved4 = b & 0xF8;
    _HEVCConifg._bitDepthLumaMinus8 = b & 0x7;

    b = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
        return -1;
    }
    _HEVCConifg._reserved5 = b & 0xF8;
    _HEVCConifg._bitDepthChromaMinus8 = b & 0x7;

    if (!io->Read(reinterpret_cast<uint8_t*>(&_HEVCConifg._avgFrameRate), 2)) {
        return -1;
    }
    ByteOrderReverse(_HEVCConifg._avgFrameRate);

    b = 0;
    if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
        return -1;
    }
    _HEVCConifg._constFrameRate = b & 0xC0;
    _HEVCConifg._numTempLayers = b & 0x38;
    _HEVCConifg._tempIdNested = b & 0x4;
    _HEVCConifg._lengthSizeMinusOne = b & 0x3;

    if (!io->Read(reinterpret_cast<uint8_t*>(&_HEVCConifg._numOfArrays), 1)) {
        return -1;
    }

    for (int i = 0; i < _HEVCConifg._numOfArrays; ++i){
        b = 0;
        if (!io->Read(reinterpret_cast<uint8_t*>(&b), 1)) {
            return -1;
        }

        Record::Arrays arr;

        arr._arrayCompleteness = 0x80 & b;
        arr._reserved = 0x40 & b;
        arr._naluType = 0x3F & b;

        if (!io->Read(reinterpret_cast<uint8_t*>(&arr._numNalues), 2)) {
            return -1;
        }
        ByteOrderReverse(arr._numNalues);

        for (int j = 0; j < arr._numNalues; ++j){
            Record::Nalu nalu;

            if (!io->Read(reinterpret_cast<uint8_t*>(&nalu._naluLen), 2)) {
                return -1;
            }
            ByteOrderReverse(nalu._naluLen);

            nalu._nalu.resize(nalu._naluLen);
            if (!io->Read(reinterpret_cast<uint8_t*>(&nalu._nalu[0]),
                          nalu._naluLen)) {
                return -1;
            }

            arr.nalus.emplace_back(std::move(nalu));
        }

        _HEVCConifg._arrays.emplace_back(std::move(arr));
    }

    int64_t ioCurrPos = io->GetCurrPos();
    return ioCurrPos - _ioBodyPos;
}
