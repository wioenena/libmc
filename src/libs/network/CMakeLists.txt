file(GLOB_RECURSE NETWORK_SRCS src/*.cpp)

add_library(network ${NETWORK_SRCS})

target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
