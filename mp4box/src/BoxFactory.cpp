#include "BoxFactory.h"
#include "Box.h"
#include "boxs/MdiaBox.h"
#include "boxs/MinfBox.h"
#include "boxs/MoofBox.h"
#include "boxs/MoovBox.h"
#include "boxs/ResvBox.h"
#include "boxs/RinfBox.h"
#include "boxs/StblBox.h"
#include "boxs/StsdBox.h"
#include "boxs/TfdtBox.h"
#include "boxs/TrafBox.h"
#include "boxs/TrakBox.h"
#include "boxs/TrunBox.h"
#include "boxs/StszBox.h"

#include <string>

  Box*
  BoxFactory::GetBoxByType(const char* type)
{
    if (std::string("trun") == type) {
        return new TrunBox;
    }

    if (std::string("moof") == type) {
        return new MoofBox;
    }

    if (std::string("traf") == type) {
        return new TrafBox;
    }

    if (std::string("moov") == type) {
        return new MoovBox;
    }

    if (std::string("trak") == type) {
        return new TrakBox;
    }

    if (std::string("mdia") == type) {
        return new MdiaBox;
    }

    if (std::string("minf") == type) {
        return new MinfBox;
    }

    if (std::string("stbl") == type) {
        return new StblBox;
    }

    if (std::string("stsd") == type) {
        return new StsdBox;
    }

    if (std::string("stsz") == type) {
        return new StszBox;
    }

    //if (std::string("resv") == type) {
    //    return new ResvBox;
    //}

    //if (std::string("rinf") == type) {
    //    return new RinfBox;
    //}

    //if (std::string("hvcC") == type) {
    //    return new HEVCConfigurationBox;
    //}

    //if (std::string("hvc1") == type || std::string("hev1") == type) {
    //    return new HevcSampleEntry;
    //}

    if (std::string("tfdt") == type) {
        return new TfdtBox;
    }

     return new Box;
}
