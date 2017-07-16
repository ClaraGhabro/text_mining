cmake_minimum_required(VERSION 3.0.2)
project(text_mining CXX)
set(TEXT_MINING_VERSION 0.1)

# direcory variables
set(SRC_DIR src/)
set(DOC_DIR doc/)
set(OUT_DIR out/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/${OUT_DIR})

# source directories
add_subdirectory(${SRC_DIR})
add_subdirectory(${DOC_DIR})
