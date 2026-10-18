#include "part.hpp"
#include "curl_wrapper.hpp"
#include "range_type.hpp"
#include "utils.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ios>
turna::Part::Part(RangeType range,std::filesystem::path path, bool isCompleted)
:range(range)
,path(path)
,writeStream(path , std::ios::app  | std::ios::binary)
,readStream(path, std::ios::binary),
isCompleted(isCompleted){

}
turna::Part::~Part(){
    this->writeStream.close();
    this->readStream.close();
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
std::ofstream* turna::Part::getWriteStream(){
    return &this->writeStream;
}
void turna::Part::downloadPart(turna::CurlWrapper * cw){
    if(!this->isCompleted)
    {
        cw->setHeaderOnly(false);
        cw->setWriteFunction(writeFunctionStream);
        cw->setWritePointer(this->getWriteStream());
        cw->setRange(this->range);
        cw->executeCurl();
        cw->setWriteFunction(writeFunctionStream);
        cw->setWritePointer(NULL);
    }
}
bool turna::Part::exists(){
    return std::filesystem::exists(this->getPath());
}
std::ifstream* turna::Part::getReadStream(){
    return &this->readStream;
}
