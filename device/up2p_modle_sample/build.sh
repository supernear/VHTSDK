#!/bin/sh

module_type=$1
usage="Usage: `basename $0` (linux|t31|t41) to build module"

cp config/$module_type.mk ./config.mk
make clean
make
