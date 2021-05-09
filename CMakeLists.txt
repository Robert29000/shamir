cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)


project(shamir)

add_library(bigrandom STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Random.cpp )

add_library(modularmath STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ModularMath.cpp)

add_library(biginteger STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/BigInteger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/BigNumberException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/BigUnsigned.cpp)

target_include_directories(biginteger
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(bigrandom
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(modularmath
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(shamir main.cpp)

target_link_libraries(bigrandom biginteger)
target_link_libraries(modularmath biginteger)
target_link_libraries(shamir biginteger bigrandom modularmath)