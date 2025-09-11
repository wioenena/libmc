find_package(boost_asio CONFIG REQUIRED)

add_executable(server src/main.cpp)

target_link_libraries(server PRIVATE network Boost::asio)