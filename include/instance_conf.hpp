#ifndef INSTANCE_CONF_HPP
#define INSTANCE_CONF_HPP
#include <filesystem>
#include <string>
namespace turna {
    struct InstanceConf{
        std::string dns = "";
        std::string proxy= "";
        std::string user_agent= "";
        std::filesystem::path task_location = std::filesystem::current_path() / "newtask";
        unsigned int connection_count =1 ;
        std::filesystem::path final_location=  std::filesystem::current_path();
    };
}

#endif
