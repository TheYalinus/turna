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
            RangeType(std::string_view range_string);
            void setFirst(std::string_view first);
            void setFirst(unsigned long first);
            void setSecond(std::string_view second);
            void setSecond(unsigned long second);
            std::string getCurlRange() const;
    };
}
#endif
