#ifndef INSTANCE_CONF_HPP
#define INSTANCE_CONF_HPP
#include <filesystem>
#include <string>
namespace turna {
    struct InstanceConf{
        std::string dns;
        std::string proxy;
        std::string user_agent;
        unsigned int connection_count;
        std::filesystem::path final_location;
    };
}

#endif
