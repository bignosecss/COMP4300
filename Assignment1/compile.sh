#!/bin/bash

# 编译 C++ 文件
g++ src/*.cpp -Isrc -std=c++17 -o bin/sfmlgame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio