#!/bin/bash

emcc -std=c++17 -Os -s TOTAL_MEMORY=1073741824 -s USE_PTHREADS=1 -s PROXY_TO_PTHREAD=1 -s EXIT_RUNTIME=1 src/mergesort/mergesort.cpp -o output/mergesort.js
node output/mergesort.js
