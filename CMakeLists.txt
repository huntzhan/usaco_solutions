cmake_minimum_required(VERSION 2.8)
project(weibo_models CXX)


###########################
# Settings related to g++ #
###########################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")


#################
# Build runtime #
#################
function(build_session tasks)
  foreach(name ${tasks})
    add_executable(${name} ${name}.cc)
  endforeach(name)
endfunction(build_session)

include_directories(src)
include_directories(test)

add_subdirectory(src/session1)


####################
# Setup googletest #
####################
add_subdirectory(lib/gtest-1.7.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) 
enable_testing()

# function that create test cases.
function(add_gtest item)
  target_link_libraries(${item} gtest_main)
  add_test(${item} ${item})
endfunction(add_gtest)
