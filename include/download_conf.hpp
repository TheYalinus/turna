#ifndef DOWNLOAD_CONF_HPP
#define DOWNLOAD_CONF_HPP
#include "part_data.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <vector>
namespace turna {

    class DownloadConf{
        public:
            static DownloadConf LoadComplexConf(nlohmann::json json);
            static DownloadConf NewComplexConf(unsigned int partCount, std::string_view url,  std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize, bool header,  std::string_view sha256="");
            static DownloadConf NewSimpleConf(std::string_view url);
            bool checkifStillValid(DownloadConf & conf);
            std::string getUrl();
            unsigned int getPartCount();
            std::string getOriginalFileName();
            std::string getOriginalFileExtension();
            unsigned long getOriginalFileSize();
            unsigned long getPartSizeRemainder();
            unsigned long getPartSize();
            bool is_complex();
            bool is_acceptingHeaders();
            std::string getSHASig();
            std::string getContentType();
            void saveTo(std::filesystem::path);
        protected:
            DownloadConf(nlohmann::json json);
            DownloadConf(unsigned int partCount, std::string_view url,  std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize,bool complex, bool header, std::string_view sha256="");
        private:
            std::string contentType , originalFileName , originalFileExtension , url, sha256;
            unsigned long originalFileSize , partSize , partSizeRemainder;
            unsigned int partCount;
            bool complex , header;
            std::vector<turna::partData> parts;

    };

}
#endif
