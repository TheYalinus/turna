#ifndef INSTANCE_CONF_HPP
#define INSTANCE_CONF_HPP
#include <string>
namespace turna {
    struct InstanceConf{
        std::string dns;
        std::string proxy;
        std::string user_agent;
        unsigned int connection_count;
    };
}

#endif
