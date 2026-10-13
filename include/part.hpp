#ifndef PART_HPP
#define PART_HPP
#include "range_type.hpp"
#include <filesystem>
#include <fstream>
#include "curl_wrapper.hpp"
#include <string>
namespace turna {
    class Part{
        public:
            Part(RangeType range,std::filesystem::path path);
            ~Part();
            std::fstream* getStream();
            void deleteFile();
            std::filesystem::path getPath();
            std::string getPathString();
            unsigned long getFileSize();
            void downloadPart(turna::CurlWrapper * cw);
        private:
            RangeType range;
            std::filesystem::path path;
            std::fstream stream;

    };
}
#endif
