#!/bin/bash

cd box2d/Box2D/Build
cmake \
    -DBOX2D_INSTALL=ON \
    -DBOX2D_INSTALL_DOC=ON \
    -DBOX2D_BUILD_SHARED=ON \
    -DBOX2D_BUILD_STATIC=OFF \
    -DBOX2D_BUILD_EXAMPLES=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DCMAKE_INSTALL_PREFIX=/opt/Box2d \
    ..
make clean
make





