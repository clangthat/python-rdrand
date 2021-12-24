#!/bin/bash

PYEXEC="/usr/bin/python3.9"

function prereq() {
    if ! [[ -e $PYEXEC ]]; then
        echo "$PYEXEC not found. Please specify the Python 3.9 binary in line 3 of this script."
        exit 1
    fi 
    
    SETUP_TOOLS=$(python3.9 -c "
import sys
try:
    import setuptools
except ImportError:
    sys.exit(1)
else:
    sys.exit(0)

")

    if [[ $SETUP_TOOLS -eq 1 ]]; then
        echo -e "Please install setuptools before proceed.\nExample: pip3 install setuptools"
        exit 1
    fi
}

function clean() {
    echo -n "Cleaning... "
    rm -rf "rdrand.cpython-39-x86_64-linux-gnu.so"
    rm -rf build
    echo "OK"
}

function build() {
    
    # Check pre-requisites before trying to build
    prereq
    
    # Ensure to clean first
    clean   

    # Compile with rdrand switch.
    CFLAGS="-mrdrnd" "$PYEXEC" setup.py build
    
    echo -n "Copying shared object to current directory... "
    cp -f "build/lib.linux-x86_64-3.9/rdrand.cpython-39-x86_64-linux-gnu.so" . && echo "OK"
}

if [ "$1" == "clean" ]; then
    clean
else
    build
fi