file(GLOB_RECURSE PROTOCOL_SRCS src/*.cpp)

add_library(protocol ${PROTOCOL_SRCS})

set_target_properties(protocol PROPERTIES CXX_STANDARD 23)


target_include_directories(protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
