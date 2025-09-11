file(GLOB_RECURSE NETWORK_SRCS src/*.cpp)

find_package(boost_asio CONFIG REQUIRED)

add_library(network SHARED ${NETWORK_SRCS})

target_link_libraries(network PRIVATE Boost::asio protocol)
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
