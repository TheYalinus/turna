#include "utils.hpp"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <string_view>
size_t turna::writeFunctionStream(char* data,size_t size, size_t nmemb,void *clientp){
    auto stream = static_cast<std::ofstream *>( clientp);
    stream->write(data, size*nmemb);
    stream->flush();
    return nmemb;
}
size_t turna::ignoreWriteStream(char* data,size_t size, size_t nmemb,void *clientp){
    return nmemb;
}
std::string turna::getTempFileNameforPart(int i, std::string originalFileName){
    return originalFileName + "_" + "[" + std::to_string(i) + "]";
}
std::string turna::genTaskCode(){
    auto now = time(nullptr);
    auto date = localtime(&now);
    return "task_"+std::to_string(date->tm_year+1900)+"_"+std::to_string(date->tm_mon+1)+"_"+std::to_string(date->tm_mday)+"_"+std::to_string(date->tm_hour)+std::to_string(date->tm_min)+std::to_string(date->tm_sec)+std::to_string(std::rand()%101);
}
