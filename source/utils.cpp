#include "utils.hpp"
#include <fstream>
size_t writeFunctionStream(char* data,size_t size, size_t nmemb,void *clientp){
    auto stream = static_cast<std::fstream *>( clientp);
    stream->write(data, size*nmemb);
    stream->flush();
    return nmemb;
}
