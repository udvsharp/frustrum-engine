find_package(benchmark REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE benchmark::benchmark)
