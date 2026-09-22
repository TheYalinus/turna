#ifndef RANGE_TYPE_HPP
#define RANGE_TYPE_HPP
#include <string>
#include <string_view>
#include <utility>
namespace turna {
    class RangeType : protected std::pair<std::string, std::string>{
        public:
            RangeType();
            RangeType(std::string_view a, std::string_view b);
            RangeType(unsigned long a , unsigned long b);
            RangeType(std::string range_string);
            std::string getCurlRange();
    };
}
#endif
