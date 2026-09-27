#ifndef DOWNLOAD_CONF_HPP
#define DOWNLOAD_CONF_HPP

#include <nlohmann/json.hpp>
namespace turna {
    class DownloadConf{
        public:
            DownloadConf(nlohmann::json json);
            DownloadConf(const std::string& url, unsigned int partCount);
            DownloadConf(const std::string& url);
        private:
            bool complex;
            std::string url, contentType , originalFileName , originalFileExtension;
            unsigned long originalFileSize , partSize , partSizeRemainder;
            unsigned int partCount;
    };

}
#endif
