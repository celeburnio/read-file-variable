cmake_minimum_required(VERSION 3.9)

project(read-file-variable VERSION 0.0.0)

add_executable(${PROJECT_NAME} readVariableFile.cpp)

install (TARGETS ${PROJECT_NAME} 
        RUNTIME DESTINATION bin
        DESTINATION ${CMAKE_INSTALL_BINDIR})