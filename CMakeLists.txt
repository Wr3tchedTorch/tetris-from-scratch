cmake_minimum_required(VERSION 3.28)
project(TetrisFromScratch LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(TetrisFromScratch 
    src/main.cpp
    src/GridManager.cpp
    src/Tetromino.cpp
    src/Game.cpp
)
target_link_libraries(TetrisFromScratch PRIVATE sfml-graphics)
target_compile_features(TetrisFromScratch PRIVATE cxx_std_17)

# Define the assets directory
set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)

# Copy assets folder to the build output directory
add_custom_command(
    TARGET TetrisFromScratch
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_FOLDER} $<TARGET_FILE_DIR:TetrisFromScratch>/assets
    COMMENT "Copying assets folder to output directory"
)

if(WIN32)
    add_custom_command(
        TARGET TetrisFromScratch
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:TetrisFromScratch>
        VERBATIM)
endif()
