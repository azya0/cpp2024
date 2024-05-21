cmake_minimum_required(VERSION 3.23)
project(lab2 LANGUAGES CXX)

add_executable(lab2 main.cpp student/student.cpp professor/professor.cpp)

if(WIN32)
    add_custom_command(
            TARGET lab2
            COMMENT "Copy data files"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:lab2>
            VERBATIM
    )
endif()