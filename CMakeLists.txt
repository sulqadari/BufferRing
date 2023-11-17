cmake_minimum_required(VERSION 3.25)

project(BufferRing VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2  \
	-Wall -Wextra -Wno-unused-parameter -Wmissing-declarations \
	-Wno-missing-field-initializers -Wredundant-decls -Wformat \
	-Wcast-align -Wformat-security"
)

# MinGW doesn't support TSAN on Windows. Although LLVM provides
# a limited support, for the sake of cross-platform portability
# this option is applied only on Unix systems.
if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

find_package(Threads REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Threads::Threads)