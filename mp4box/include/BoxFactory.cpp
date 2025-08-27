#include "BoxFactory.h"
#include "Box.h"

Box* BoxFactory::GetBoxByType(const char* type)
{
    return new Box;
}
