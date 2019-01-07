cmake_minimum_required(VERSION 3.12)
project(fuse_sample C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED fuse)

set(CMAKE_C_STANDARD 99)

add_executable(fuse_sample main.c)

target_link_libraries(fuse_sample ${FUSE_LIBRARIES})
target_include_directories(fuse_sample PUBLIC ${FUSE_INCLUDE_DIRS})
target_compile_options(fuse_sample PUBLIC ${FUSE_CFLAGS_OTHER})
