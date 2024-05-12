CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(lazy_load)

MESSAGE(STATUS "Test lazy load library")


## Load lib through link
set(SRCS test_load_library.cc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
INCLUDE_DIRECTORIES(BEFORE ${PROJECT_SOURCE_DIR}/libs/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/lib)
ADD_EXECUTABLE(test_load_library ${SRCS})
TARGET_LINK_LIBRARIES(test_load_library liblazy_lib.so)


## Load lib through dlopen

#https://github.com/iree-org/iree/issues/4915
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAG} -lpthread")
set(CMAKE_C_FLAG "${CMAKE_CXX_FLAG} -lpthread")
MESSAGE(STATUS "CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")

ADD_EXECUTABLE(test_lazy_load_library test_lazy_load_library.cc)
# https://stackoverflow.com/questions/51584960/stdcall-once-throws-stdsystem-error-unknown-error-1
TARGET_LINK_LIBRARIES(test_lazy_load_library pthread)
