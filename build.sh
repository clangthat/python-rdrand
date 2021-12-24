#!/bin/bash
echo "Cleaning and building..."
rm -rf build
CFLAGS="-mrdrnd" python3 setup.py build

echo "Copying shared object to current directory..."
rm -f "rdrand.cpython-39-x86_64-linux-gnu.so"
cp -f "build/lib.linux-x86_64-3.9/rdrand.cpython-39-x86_64-linux-gnu.so" .
