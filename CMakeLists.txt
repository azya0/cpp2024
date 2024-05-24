cmake_minimum_required(VERSION 3.23)
project(arcane LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(arcane main.cpp source/structures/structures.cpp source/game/game.cpp source/objects/objects.cpp)
target_link_libraries(arcane PRIVATE sfml-graphics)
target_compile_features(arcane PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET arcane
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:arcane>
        VERBATIM)
endif()

install(TARGETS arcane)
