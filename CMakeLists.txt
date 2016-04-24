###############################################################################
# CMakeLists.txt
#
# A simple build file for automating the make procedure for the program.
###############################################################################

# The minimum required version of CMake in for these instructions to work
# TODO: Try to make as backwards compatible as possible.
cmake_minimum_required(VERSION 2.6)

# Specify the project name
project(vom)
# Specify the files to build
add_executable(vom src/main.c)

# Include the curses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
# Link the curses library to the binary
target_link_libraries(vom ${CURSES_LIBRARIES})

# Compile to reduce the binary size and display warnings
set(CMAKE_C_FLAGS "-Os -Wall")
# Strip out the debug symbols from the binary
# NOTE: Setting the build type doesn't appear to do this effectively.
set(CMAKE_EXE_LINKER_FLAGS "-s")

# Run static code analysis
add_custom_command(
  OUTPUT results.txt
  COMMAND cppcheck src
  DEPENDS src
  COMMENT "Running Static Code Analysis"
)
# Build PDF documentation
add_custom_command(
  OUTPUT readme.pdf
  COMMAND pandoc readme.md -s -o readme.pdf
  DEPENDS readme.md
  COMMENT "Building PDF documentation"
)
# Build HTML documentation
add_custom_command(
  OUTPUT readme.html
  COMMAND pandoc readme.md -s -o readme.html
  DEPENDS readme.md
  COMMENT "Building HTML documentation"
)
add_custom_target(run-analysis ALL DEPENDS results.txt)
add_custom_target(run-doc-pdf ALL DEPENDS readme.pdf)
add_custom_target(run-doc-html ALL DEPENDS readme.html)
