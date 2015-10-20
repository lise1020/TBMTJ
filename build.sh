#!/bin/bash

cd build/build-core
cmake ../../src
make
cd ../../

#cd build/build-gui
#qmake ../../src/QMakeLists.txt
#make
#cd ../../



