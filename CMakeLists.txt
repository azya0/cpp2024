cmake_minimum_required(VERSION 3.23)
project(gems LANGUAGES CXX)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/.env
  ${CMAKE_CURRENT_BINARY_DIR}/.env
  COPYONLY
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(gems main.cpp source/board/board.cpp source/base_structions/base_structions.cpp)
target_link_libraries(gems PRIVATE sfml-graphics)
target_compile_features(gems PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET gems
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:gems>
        VERBATIM)
    add_custom_command(
        TARGET gems
        COMMENT "Copy .env"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/.env $<TARGET_FILE_DIR:gems>
        VERBATIM)
endif()

install(TARGETS gems)
