#ifndef INSTANCE_CONF_HPP
#define INSTANCE_CONF_HPP
#include <string>
namespace turna {
    struct InstanceConf{
        std::string dns;
        std::string proxy;
        unsigned int connection_count;
    };
}

#endif
