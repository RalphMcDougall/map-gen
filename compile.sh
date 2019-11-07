
echo "Creating main object"
g++ -c main.cpp -std=c++11 -O2
echo "Linking objects together"
g++ main.o -o map-gen -w -lSDL2 -std=c++11 -O2