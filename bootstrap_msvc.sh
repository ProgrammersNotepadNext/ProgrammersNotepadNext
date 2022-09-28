#!/bin/sh

QT_PATH=C:/Qt/6.3.1/msvc2019_64

rm -rf vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=${QT_PATH}
cd ..
