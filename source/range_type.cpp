#include "range_type.hpp"
#include <string>
#include <string_view>
#include <utility>
turna::RangeType::RangeType():std::pair<std::string, std::string>("","" ){}
turna::RangeType::RangeType(std::string_view a , std::string_view b): std::pair<std::string, std::string>(a,b){}
turna::RangeType::RangeType(unsigned long a , unsigned long b): std::pair<std::string, std::string> (std::to_string(a),std::to_string(b)){}
turna::RangeType::RangeType(std::string range_string )
:std::pair<std::string , std::string>(range_string.substr(0,range_string.find("-")),range_string.substr(range_string.find("-")+1,range_string.size()-range_string.find("-")+1)){}
std::string turna::RangeType::getCurlRange(){
        if(!this->first.empty() && !this->second.empty())
            return (this->first + "-" + this->second + '\0');
        else if(this->first.empty() && !this->second.empty())
            return ("-" + this->second + '\0');
        if(!this->first.empty()&& this->second.empty())
            return (this->first + "-" + '\0');
        if(this->first.empty() && this->second.empty())
            return "";
        return "";
}
