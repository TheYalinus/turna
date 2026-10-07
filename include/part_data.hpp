#ifndef PART_DATA_HPP
#define PART_DATA_HPP
#include "range_type.hpp"
namespace turna {
    struct partData{
        RangeType range;
        unsigned long partSize;
        int id;
        std::string fileName;
    };
}
#endif
