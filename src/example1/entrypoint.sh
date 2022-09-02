#!/bin/bash

emcc src/example1/helloworld.cpp -o output/helloworld.js
node output/helloworld.js