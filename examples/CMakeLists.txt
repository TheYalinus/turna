#First example curl_wrapper
add_executable(curl_wrapper curl_wrapper.cpp)
#Second example connection_pool
add_executable(connection_pool connection_pool.cpp)
#third example gather_data
add_executable(gather_data gather_data.cpp)
#fourth example download_task
add_executable(download_task download_task.cpp)
target_link_libraries(curl_wrapper PRIVATE turna::turna)
target_link_libraries(connection_pool PRIVATE turna::turna)
target_link_libraries(gather_data PRIVATE turna::turna)
target_link_libraries(download_task PRIVATE turna::turna)
