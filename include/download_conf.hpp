#ifndef DOWNLOAD_CONF_HPP
#define DOWNLOAD_CONF_HPP
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
namespace turna {
    class DownloadConf{
        public:
            DownloadConf(std::string_view url,std::string_view sha256 ="");
            std::string getSHA256();
        protected:
            std::string url , sha256;
    };
    class DownloadConfComplex:public DownloadConf{
        public:
            DownloadConfComplex(nlohmann::json json);
            DownloadConfComplex(unsigned int partCount, std::string_view url,  std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize, std::string_view sha256="");

        private:
            std::string contentType , originalFileName , originalFileExtension;
            unsigned long originalFileSize , partSize , partSizeRemainder;
            unsigned int partCount;

    };

}
#endif
