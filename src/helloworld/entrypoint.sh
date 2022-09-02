#!/bin/bash

emcc src/helloworld/helloworld.cpp -o output/helloworld.html
node output/helloworld.js
