echo "Creating main object"
g++ -c main.cpp -std=c++11 -O2
echo "Creating perlin object"
g++ -c perlin.cpp -std=c++11 -O2
echo "Linking objects together"
g++ main.o perlin.o -o map-gen -w -lSDL2 -std=c++11 -O2