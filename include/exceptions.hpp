#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <exception>
#include <stdexcept>
#include <string>
namespace turna {
    class CurlPerformException : public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
    };
    class CurlInvalidUrlError : public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
    };
    class CurlGetInfoError : public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
    };
    class CurlShareError : public std::runtime_error{
        public:
            using std::runtime_error::runtime_error;
    };
}

#endif
