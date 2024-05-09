cmake_minimum_required(VERSION 3.25)
project(cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(include)

set(THIRDPARTY_LIBS glog gflags jsoncpp gurobi95 gurobi_g++5.2 ${Jsoncpp_LIBRARY} ${Z3_FILE})

add_subdirectory(basic)
add_subdirectory(autolifter)
add_subdirectory(exp)
add_subdirectory(baseline)
add_subdirectory(polygen)

add_executable(main main.cpp)
target_link_libraries(main exp_lib autolifter_lib baseline_lib polygen_lib basic_lib ${THIRDPARTY_LIBS})