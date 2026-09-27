#include "curl_wrapper.hpp"
#include <turna.hpp>
int main(int argc , char * argv[]){
    if(argc< 2)
        return -1;
    turna::CurlWrapper wrapper;
    std::string user_agent ="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36";
    wrapper.setUrl(argv[1]);
    wrapper.setFollowRedirects();
    wrapper.setUsrAgent(user_agent);
    wrapper.executeCurl();
    //It has method chaining support
    turna::CurlWrapper wrapper2;
    wrapper2.setUrl(argv[1]).setCurlVerbose(true).setUsrAgent(user_agent).executeCurl();
    return 0;
}
