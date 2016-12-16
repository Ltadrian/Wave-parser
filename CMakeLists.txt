cmake_minimum_required(VERSION 3.6)
project(wav)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    bass.wav
    text.txt
    wave.cpp
    wave.h
    wave.h.gch)

add_executable(wav ${SOURCE_FILES})