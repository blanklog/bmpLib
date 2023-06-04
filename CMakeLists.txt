cmake_minimum_required(VERSION 3.5)

project(bmpLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(bmpLib SHARED BmpSupporter.cpp BmpSupporter.h bmpLibGlobal.h)
set_target_properties(bmpLib PROPERTIES PUBLIC_HEADER bmpLibGlobal.h)
get_target_property(myvar bmpLib PUBLIC_HEADER)


add_executable(bmpExample  BmpSupporter.cpp BmpSupporter.h bmpLibGlobal.h main.cpp)


set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install/ CACHE PATH "..." FORCE)
install(TARGETS bmpLib
    #RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    #PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
