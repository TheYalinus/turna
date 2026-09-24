#include "part.hpp"
#include "range_type.hpp"
#include <filesystem>
#include <fstream>
#include <ios>
turna::Part::Part(RangeType range,std::filesystem::path path)
:range(range)
,path(path)
,stream(path , std::ios::app  | std::ios::binary){

}
void turna::Part::deleteFile(){
    std::filesystem::remove(this->path);
}
std::string turna::Part::getPathString(){
    return this->path.string();
}
std::filesystem::path turna::Part::getPath(){
    return this->path;
}
unsigned long turna::Part::getFileSize(){
    return std::filesystem::file_size(this->path);
}
std::fstream* turna::Part::getStream(){
    return &this->stream;
}
