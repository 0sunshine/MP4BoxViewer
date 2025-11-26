#include <iostream>
#include <format>

#include "IOFStream.h"
#include "RootBox.h"
#include "boxs/TrunBox.h"
#include "boxs/StsdBox.h"
#include "boxs/TfdtBox.h"
#include "Util.h"
#include <boxs/StszBox.h>

void writeFile(IOFStream& fin, HEVCConfigurationBox* hvcCEntry, Box* mdatBox, int count)
{
    std::ofstream fout("track1.h265", std::ios::ate | std::ios::binary);

    if (!fout) {
        return;
    }

    uint32_t startCode = 1;
    ByteOrderReverse(startCode);

    for (auto& arr : hvcCEntry->_HEVCConifg._arrays){
        for (auto& nal : arr.nalus) {
            fout.write((char*)&startCode, 4);
            fout.write((char*)&nal._nalu[0], nal._naluLen);
        }
    }

    fin.SeekTo(mdatBox->_ioBodyPos);

    std::vector<uint8_t> frameData;

    while (count--)
    {
        uint32_t sampleSize = 0;
        if (!fin.Read((uint8_t*) &sampleSize, 4)) {
            std::cout << "error............" << std::endl;
            return;
        }
        ByteOrderReverse(sampleSize);

        frameData.resize(sampleSize);
        if (!fin.Read((uint8_t*)&frameData[0], frameData.size())) {
            std::cout << "error............" << std::endl;
            return;
        }

        fout.write((char*)&startCode, 4);
        fout.write((char*)&frameData[0], frameData.size());
    }

    fout.close();
}



void writeAudioToFile()
{
    std::ofstream fout("kcw.aac", std::ios::ate | std::ios::binary);
    std::ofstream fout2("old.txt", std::ios::ate);

    int sIdx = 0;

    for (int i = 1; i < 522; ++i)
    {
        RootBox rootBox;
        IOFStream fin;
        if (!fin.OpenFile(std::format(
              "D:/task/vr/pts/vodpts/Test_track2000.{}.mp4", i))) {
            std::cout << "open file error" << std::endl;
            return;
        }

        rootBox._size = fin.GetFileSize();
        if (rootBox.Parse(&fin) < 0) {
            std::cout << "rootBox parser error" << std::endl;
            return;
        }

        std::vector<Box*> trunBoxs;
        rootBox.GetBoxsByType(trunBoxs, "trun");

        std::vector<Box*> mdatBoxs;
        rootBox.GetBoxsByType(mdatBoxs, "mdat");

        TrunBox* trunBox = static_cast<TrunBox*>(trunBoxs[0]);
        Box* mdatBox = mdatBoxs[0];

        fin.SeekTo(mdatBox->_ioBodyPos);

        int idx = 0;


        for (auto entry : trunBox->_entrys) {
            ++idx;



            int p = fout.tellp();
            //if (p > 0x9CA8) {
            //    std::cout << "......" << std::endl;
            //}

            std::vector<uint8_t> frameData;
            frameData.resize(entry._sampleSize.value());

            if (!fin.Read(&frameData[0], frameData.size())) {
                std::cout << "error............" << std::endl;
                return;
            }

            ++sIdx;
            fout2 << std::dec << sIdx << " -- "
                  << entry._sampleSize.value() << " -- ";

            for (auto& x : frameData)
            {
                if (x < 0x10) {
                    fout2 << 0;
                }
                fout2 << std::hex << (uint16_t)x;
            }

            fout2 << std::endl;


            uint8_t adts[7] = { 0 };
            int profile = 1;
            int freqIdx = 3; // 48000
            int nb_channels = 2;
            int size = frameData.size();

            adts[0] = 0xFF;
            adts[1] = 0xF1;
            adts[2] = (profile << 6) + (freqIdx << 2) + (nb_channels >> 2);
            adts[3] = ((nb_channels & 3) << 6) + ((size + 7) >> 11);
            adts[4] = ((size + 7) & 0x7FF) >> 3;
            adts[5] = (((size + 7) & 7) << 5) + 0x1F;
            adts[6] = 0xFC;

            fout.write((char*)&adts, 7);
            fout.write((char*)&frameData[0], frameData.size());
        }
    }
    fout.close();
    fout2.close();
}



int main(int, char**)
{
    writeAudioToFile();

    //return 0;

    RootBox rootMetaBox;
    IOFStream fin;

    //if (!fin.OpenFile("D:/task/vr/Test_track11.init.mp4")) {
    //    std::cout << "open file error" << std::endl;
    //}

    //rootMetaBox._size = fin.GetFileSize();
    //if (rootMetaBox.Parse(&fin) < 0) {
    //    std::cout << "rootBox parser error" << std::endl;
    //    return -1;
    //}

    //std::cout << "box num: " << rootMetaBox._subBoxs.size() << std::endl;

    //std::vector<Box*> hvcCBoxs;
    //rootMetaBox.GetBoxsByType(hvcCBoxs, "hvcC");
    //HEVCConfigurationBox* hvcCEntry =
    //  static_cast<HEVCConfigurationBox*>(hvcCBoxs[0]);

    fin.Close();
    RootBox rootBox;
    if( !fin.OpenFile("D:/task/vr/pts/tt.mp4") ){
        std::cout << "open file error" << std::endl;
        return -1;
    }

    rootBox._size = fin.GetFileSize();
    if (rootBox.Parse(&fin) < 0)
    {
        std::cout << "rootBox parser error" << std::endl;
        return -1;
    }

    std::cout << "box num: " << rootBox._subBoxs.size() << std::endl;

    //std::vector<Box*> tfdtCBoxs;
    //rootBox.GetBoxsByType(tfdtCBoxs, "tfdt");
    //TfdtBox* tfdtBox = static_cast<TfdtBox*>(tfdtCBoxs[0]);

    std::vector<Box*> trunBoxs;
    rootBox.GetBoxsByType(trunBoxs,"trun");

    std::vector<Box*> mdatBoxs;
    rootBox.GetBoxsByType(mdatBoxs, "mdat");

    //if (trunBoxs.size() != 1 || mdatBoxs.size() != 1)
    //{
    //    std::cout << "trunBoxs.size() != 1 || mdatBoxs != 1, quit" << std::endl;
    //    return -1;
    //}

    //TrunBox* trunBox = static_cast<TrunBox*>(trunBoxs[0]);
    Box* mdatBox = mdatBoxs[0];

    fin.SeekTo(mdatBox->_ioBodyPos);


    {
        std::ofstream fout("ori.txt", std::ios::ate);

        std::vector<Box*> stszBoxs;
        rootBox.GetBoxsByType(stszBoxs, "stsz");
        StszBox* stszBox = static_cast<StszBox*>(stszBoxs[0]);

        for (int i = 0; i < stszBox->_entrySizes.size(); ++i) {

            std::vector<uint8_t> frameData;
            frameData.resize(stszBox->_entrySizes[i]);

            if (!fin.Read(&frameData[0], frameData.size())) {
                std::cout << "error............" << std::endl;
                return -1;
            }

            fout << std::dec << i + 1 << " -- " << stszBox->_entrySizes[i]
                 << " -- ";

            for (auto& x : frameData) {
                if (x < 0x10)
                {
                    fout << 0;
                }
                fout << std::hex << (uint16_t)x;
            }

            fout << std::endl;
        }



        fout.close();
    }

    //{
    //    std::ofstream fout("1.aac", std::ios::ate | std::ios::binary);

    //    if (!fout) {
    //        return -1;
    //    }

    //    int idx = 0;

    //    for (auto entry : trunBox->_entrys) {


    //        ++idx;

    //        std::vector<uint8_t> frameData;
    //        frameData.resize(entry._sampleSize.value());

    //        if (!fin.Read(&frameData[0], frameData.size())) {
    //            std::cout << "error............" << std::endl;
    //            return -1;
    //        }

    //        uint8_t adts[7] = { 0 };
    //        int profile = 1;
    //        int freqIdx = 3; //48000
    //        int nb_channels = 2;
    //        int size = frameData.size();

    //        adts[0] = 0xFF;
    //        adts[1] = 0xF1;
    //        adts[2] = (profile << 6) + (freqIdx << 2) + (nb_channels >> 2);
    //        adts[3] = ((nb_channels & 3) << 6) + ((size + 7) >> 11);
    //        adts[4] = ((size + 7) & 0x7FF) >> 3;
    //        adts[5] = (((size + 7) & 7) << 5) + 0x1F;
    //        adts[6] = 0xFC;

    //        fout.write((char*)&adts, 7);
    //        fout.write((char*)&frameData[0], frameData.size());
    //    }

    //    fout.close();
    //}

    //for (auto entry : trunBox->_entrys)
    //{
    //    ++idx;

    //    std::vector<uint8_t> frameData;
    //    frameData.resize(entry._sampleSize.value());

    //    
    //    if (!fin.Read(&frameData[0], frameData.size()))
    //    {
    //        std::cout << "error............" << std::endl;
    //        return -1;
    //    }

    //    // first 4 bytes is sample length
    //    uint8_t type = (frameData[4] >> 1) & 0x3F;

    //    
    //    std::cout << std::format("No.{} sample, len: {}, nalu type: {}",
    //                             idx,
    //                             frameData.size(), type)
    //              << std::endl;
    //}

    //writeFile(fin, hvcCEntry, mdatBox, trunBox->_entrys.size());
    
    std::cout << "end............" << std::endl;
}
