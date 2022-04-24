#!/bin/bash

PYEXEC="/usr/bin/python3.10"

function prereq() {
    if ! [[ -e $PYEXEC ]]; then
        echo "$PYEXEC not found. Please specify the Python binary in line 3 of this script."
        exit 1
    fi

    SETUP_TOOLS=$("$PYEXEC" -c "
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
    rm -rf *.so
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

    if [ "$1" == "install" ]; then
        CFLAGS="-mrdrnd" "$PYEXEC" setup.py install
    else
        echo -n "Copying shared object to current directory..."
        cp -f build/lib.linux-x86_64-3.10/*.so . && echo "OK"
    fi
}
if [ "$1" == "clean" ]; then
    clean
else
    build $1
fi
