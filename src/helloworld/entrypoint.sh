#!/bin/bash

emcc -Os src/helloworld/helloworld.cpp -o output/helloworld.js
node output/helloworld.js
