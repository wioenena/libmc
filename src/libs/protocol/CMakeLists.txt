file(GLOB_RECURSE PROTOCOL_SRCS src/*.cpp)

add_library(protocol ${PROTOCOL_SRCS})

target_include_directories(protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
