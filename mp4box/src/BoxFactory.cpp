#include "BoxFactory.h"
#include "Box.h"
#include "boxs/MoofBox.h"
#include "boxs/TrafBox.h"
#include "boxs/TrunBox.h"

#include <string>

Box* BoxFactory::GetBoxByType(const char* type)
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

    return new Box;
}
