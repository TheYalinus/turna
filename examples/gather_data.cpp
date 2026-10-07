#include "gather_info.hpp"
#include "turna.hpp"
#include <iostream>
int main(){
    std::string user_agent ="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36";
    //create a curl object , or pull one from a connection pool
    //take a look : examples/connection_pool.cpp
    turna::CurlWrapper wrapper;
    //all the properties, except the url, should be set before gatherData function
    wrapper.setCurlVerbose().setKeepConnection(true).setUsrAgent(user_agent).setFollowRedirects();
    auto cfg = turna::gatherData(wrapper, "https://thumb.wikimedia.org/wikipedia/commons/thumb/0/0d/Onur_An%C4%B1t%C4%B1.JPG/250px-Onur_An%C4%B1t%C4%B1.JPG?utm_source=tr.wikipedia.org&utm_campaign=parser&utm_content=thumbnail", 1);
    //now you can see info about the file
    std::cout<<cfg.getOriginalFileName()<<"-"<<cfg.getContentType()<<"-"<<cfg.getOriginalFileSize();
}
