#!/bin/bash
# Instalación de dependencias y herramientas
echo "Instalación de dependencias..."
apt-get update 
apt-get install -y \
autotools-dev \
build-essential \
cmake \
libbz2-dev \
libcrypto++-dev \
zlib1g-dev \
libsnappy-dev \
libcurl4-gnutls-dev \
doxygen \
lcov

if [ "$1" == "-oldboost" ]
then
 add-apt-repository ppa:afrank/boost -y
 apt-get update -q
 apt-get install libboost1.57-all libboost1.57-all-dev
else
	apt-get install -y libboost-all-dev
fi

mkdir -p build
cd build

cmake CMAKE_BUILD_TYPE=Debug ../project && make

