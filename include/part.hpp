#ifndef PART_HPP
#define PART_HPP
#include "range_type.hpp"
#include <filesystem>
#include <fstream>
#include <string>
namespace turna {
    class Part{
        public:
            Part(RangeType range,std::filesystem::path path);
            std::fstream* getStream();
            void deleteFile();
            std::filesystem::path getPath();
            std::string getPathString();
            unsigned long getFileSize();
        private:
            RangeType range;
            std::filesystem::path path;
            std::fstream stream;

    };
}
#endif
