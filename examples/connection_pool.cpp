

#include "turna.hpp"
#include <chrono>
#include <thread>

int main(){
    //Create a connetion pool object, that initalizes curl connections instantly
    //All the connections in the pool uses the same DNS cache, so the url is once time resolved
    // For establishing connections for the first time, ctor sends a range 0-1 request to server and the connections left intact
    turna::InstanceConf conf {}; //A config that keeps instance-specific things like dns and user-agents
    conf.connection_count=3; //This a must have
    conf.user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36"; //you'll need this somehow
    turna::ConnectionPool pool("www.google.com", conf);
    //Get a CurlWrapper object from pool
    auto wrapper1= pool.acquireCurlWrapper();
    auto wrapper2= pool.acquireCurlWrapper();
    auto wrapper3= pool.acquireCurlWrapper();
    std::thread thr ([&wrapper1](){
        std::this_thread::sleep_for(std::chrono::seconds(15)); //simulate here some work
        wrapper1.reset(); //reset the pointer and call the dtor , this notifies waiting wrapper
    });
    auto wrapper4 = pool.acquireCurlWrapper();//this will be wait until a wrapper resets
    //after the 15 seconds work ends, wrapper doesnt contains anything
    // and wrapper4 becomes usable(contains the CurlWrapper object of old wrapper1)
    // also it uses old connection that left intact
    wrapper4->executeCurl();
    thr.join();
}
