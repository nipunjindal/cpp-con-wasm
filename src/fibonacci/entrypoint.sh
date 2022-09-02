#!/bin/bash

cd src/fibonacci/
emcc --no-entry -0s -s WASM=1 -s SIDE_MODULE=1 fibonacci.cpp -o fibonacci.wasm
http-server -p 8000
