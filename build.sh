#!/bin/bash
echo "Cleaning and building..."
rm -rf build
CFLAGS="-mrdrnd" python3 setup.py build
