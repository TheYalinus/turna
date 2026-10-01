#include "utils.hpp"
#include <fstream>
size_t turna::writeFunctionStream(char* data,size_t size, size_t nmemb,void *clientp){
    auto stream = static_cast<std::fstream *>( clientp);
    stream->write(data, size*nmemb);
    stream->flush();
    return nmemb;
}
size_t turna::ignoreWriteStream(char* data,size_t size, size_t nmemb,void *clientp){
    return nmemb;
}
