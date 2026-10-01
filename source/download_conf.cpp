#include "download_conf.hpp"
#include <string>
#include <string_view>
turna::DownloadConf::DownloadConf(std::string_view url , std::string_view sha256):url(url) , sha256(sha256){

}
turna::DownloadConfComplex::DownloadConfComplex(nlohmann::json json): DownloadConf(std::string(json.at("url"))), contentType(json.at("contentType")), originalFileName(json.at("originalFileName"))
,originalFileExtension(json.at("originalFileExtension")), originalFileSize(json.at("originalFileSize")), partSize(json.at("def_partSize")), partSizeRemainder(json.at("def_remainder"))
,partCount(json.at("partCount"))
{

}
turna::DownloadConfComplex::DownloadConfComplex( unsigned int partCount, std::string_view url, std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize, std::string_view sha256):
DownloadConf(url ,sha256), partCount(partCount), contentType(contentType) ,originalFileSize(originalFileSize), originalFileExtension(originalFileExtension), originalFileName(originalFileName), partSize(originalFileSize / partCount), partSizeRemainder(originalFileSize %partSize){

}
std::string turna::DownloadConf::DownloadConf::getSHA256(){
    return this->sha256;
}
