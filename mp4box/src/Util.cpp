#include "Util.h"

void ByteOrderReverse(uint8_t* p, int len)
{
    std::vector<uint8_t> tmp;
    tmp.resize(len);
    memcpy(&tmp[0], p, len);

    for (int i = 0; i < len; ++i) {
        p[i] = tmp[len - i - 1];
    }
}