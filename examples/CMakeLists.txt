#First example curl_wrapper
add_executable(curl_wrapper curl_wrapper.cpp)
target_link_libraries(curl_wrapper PRIVATE turna)
