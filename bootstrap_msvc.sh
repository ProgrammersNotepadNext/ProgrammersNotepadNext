#!/bin/sh

#rmdir /S /Q builds_win
#mkdir builds_win
#cd builds_win

#QT_PATH=C:/Qt2/5.11.2/msvc2017_64/lib/cmake/Qt5
#QT_PATH=C:/Qt2/5.11.2/msvc2017_64
QT_PATH=C:/Qt/Qt5.14.0/5.14.0/msvc2017_64

rm -rf vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH=${QT_PATH}
cd ..
