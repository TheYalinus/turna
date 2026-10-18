#ifndef INSTANCE_CONF_HPP
#define INSTANCE_CONF_HPP
#include "utils.hpp"
#include <filesystem>
#include <string>
namespace turna {
    struct InstanceConf{
        std::string dns = "";
        std::string proxy= "";
        std::string user_agent= "";
        std::filesystem::path task_location = std::filesystem::current_path() / turna::genTaskCode();
        unsigned int connection_count =1 ;
        std::filesystem::path final_location=  std::filesystem::current_path();
    };
}

#endif
