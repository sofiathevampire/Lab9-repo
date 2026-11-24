cmake_minimum_required(VERSION 3.20)
project(lab9 C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# des/d3des.c is a vendored, public-domain C (not C++) DES/Triple-DES
# implementation - see des/DesCipher.hpp for why it's here and how to use it.
add_executable(lab9
        main.cpp
        Request.hpp
        CommandLineParser.cpp
        CommandLineParser.hpp
        Crypto.cpp
        Crypto.hpp
        des/DesCipher.cpp
        des/DesCipher.hpp
        des/d3des.c
        des/d3des.h)

target_include_directories(lab9 PRIVATE des)

# des/d3des.c uses 1992-vintage K&R-style function definitions; that's the
# vendored file as published, not something to "fix" here.
set_source_files_properties(des/d3des.c PROPERTIES COMPILE_OPTIONS "-Wno-old-style-definition")
