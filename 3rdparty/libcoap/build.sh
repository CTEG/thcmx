#!/bin/bash

source param.mk

CURDIR=`pwd`

if [ ! -d ${DIRNAME} ]; then
	git clone  https://github.com/authmillenon/libcoap.git
fi

mkdir out

# build lib
cd ${DIRNAME}
autoconf
./configure --prefix=${CURDIR}/out
make
make install
cd ..

cp -rf ${CURDIR}/out/include/* ${CURDIR}/../prebuild/include/
cp ${CURDIR}/out/lib/*.a ${CURDIR}/../prebuild/libs
