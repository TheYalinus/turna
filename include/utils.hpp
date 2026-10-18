#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstddef>
#include <string>
namespace turna {
    size_t writeFunctionStream(char* ,size_t, size_t ,void *);
    size_t ignoreWriteStream(char* ,size_t, size_t ,void *);
    std::string getTempFileNameforPart(int i, std::string originalFileName);
    std::string genTaskCode();
}
#endif
