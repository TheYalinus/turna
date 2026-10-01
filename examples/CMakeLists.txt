#First example curl_wrapper
add_executable(curl_wrapper curl_wrapper.cpp)
#Second example connection_pool
add_executable(connection_pool connection_pool.cpp)
target_link_libraries(curl_wrapper PRIVATE turna::turna)
target_link_libraries(connection_pool PRIVATE turna::turna)
