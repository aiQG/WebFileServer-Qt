#!/bin/bash

echo "compiling ServerSide"
g++ -std=c++11 -c *.cpp && g++ -o Server-Side *.o
echo "removing *.o"
rm *.o

echo "creating \"fileHash\" file"
echo "# This file safes files' hash" > fileHash
echo "" >> fileHash

echo "success"

echo "run Server-Side first"
