#pragma once

#include "FullBox.h"

#include <optional>

struct SampleEntry : public Box
{
    uint8_t _reserved[6] = {};
    uint16_t _dataReferenceIndex = 0;

    int64_t Parse(IOBase* io) override;
};

struct VisualSampleEntry : public SampleEntry
{
    uint16_t _preDefined1 = 0;
    uint16_t _reserved1 = 0;
    uint32_t _preDefined2[3] = {};

    uint16_t _width = 0;
    uint16_t _height = 0;

    uint32_t _horizresolution = 0;
    uint32_t _vertresolution = 0;

    uint32_t _reserved2 = 0;

    uint16_t _frameCount = 0;

    uint8_t _compressorname[32] = {};

    uint16_t _depth = 0;

    uint16_t _preDefined3 = 0;

    int64_t Parse(IOBase* io) override;
};

struct HEVCConfigurationBox : public Box
{
    struct Record
    {
        struct Nalu
        {
            uint16_t _naluLen = 0;
            std::vector<uint8_t*> _nalu;
        };

        struct Arrays
        {
            uint8_t _arrayCompleteness = 0; // 1bit
            uint8_t _reserved = 0;          // 1bit
            uint8_t _naluType = 0;          // 6bit

            uint16_t _numNalues = 0;

            std::vector<Nalu> nalus;
        };

        uint8_t _configurationVersion = 0;

        uint8_t _generalProFileSpace = 0; // 2 bit
        uint8_t _generalTierFlag = 0;     // 1 bit
        uint8_t _generalProFileIdc = 0;   // 5 bit

        uint32_t _generalProFileCompatFlags = 0;
        uint64_t _generalConstIndicatorFlags = 0; // 48bit
        uint8_t _generalLevelIdc = 0;

        uint8_t _reserved1 = 0;         // 4bit
        uint16_t _minSpatialSegIdc = 0; // 12 bit

        uint8_t _reserved2 = 0;       // 6bit
        uint8_t _parallelismType = 0; // 2 bit

        uint8_t _reserved3 = 0;       // 6bit
        uint8_t _chroma_format_idc = 0; // 2 bit

        uint8_t _reserved4 = 0;          // 5bit
        uint8_t _bitDepthLumaMinus8 = 0; // 3bit

        uint8_t _reserved5 = 0;            // 5bit
        uint8_t _bitDepthChromaMinus8 = 0; // 3bit

        uint16_t _avgFrameRate = 0;

        uint8_t _constFrameRate = 0;     // 2bit
        uint8_t _numTempLayers = 0;      // 3bit
        uint8_t _tempIdNested = 0;       // 1bit
        uint8_t _lengthSizeMinusOne = 0; // 2bit

        uint8_t _numOfArrays = 0;

        std::vector<Arrays> _arrays;

    } _HEVCConifg;

    int64_t Parse(IOBase* io) override;
};

struct HevcSampleEntry : public VisualSampleEntry
{
    //HEVCConfigurationBox _config;
    //Box* _MPEG4ExtDescBox = nullptr;  add to subBoxs

    int64_t Parse(IOBase* io) override;
};

struct StsdBox: public FullBox
{
    uint32_t _entryCount = 0;

    std::vector<Box*> _sampleEntrys;

    int64_t Parse(IOBase* io) override;
};