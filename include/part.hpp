#ifndef PART_HPP
#define PART_HPP
#include "range_type.hpp"
#include <filesystem>
#include <fstream>
#include "curl_wrapper.hpp"
#include <streambuf>
#include <string>
namespace turna {
    class Part{
        public:
            Part(RangeType range,std::filesystem::path path,bool isCompleted);
            ~Part();
            std::ofstream* getWriteStream();
            std::ifstream* getReadStream();
            void deleteFile();
            std::filesystem::path getPath();
            std::string getPathString();
            unsigned long getFileSize();
            void downloadPart(turna::CurlWrapper * cw);
            bool exists();

        private:
            RangeType range;
            std::filesystem::path path;
            std::ofstream writeStream;
            std::ifstream readStream;
            bool isCompleted;

    };
}
#endif
