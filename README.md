# map-gen
![Example map](images/img1.png?raw=true "Example map")

An experiment in terrain generation with Perlin noise.

## Getting started

### Prerequisites
This project requires SDL2 to be installed on your system. If you are using a Linux distribution, this can be done with:
```
sudo apt-get install libsdl2-dev
```
Instructions for other operation systems can be found on the tutorial on [LazyFoo](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).

### Installing
Clone the repository to your local device. Take not of where it has been installed.

### Compilation
If you are using a Linux distribution, open a terminal in the folder where the project was installed, then run:
```
./compile.sh
```
### Running
If you are using a Linux distribution, run the following in the terminal:
```
./map-gen
```

If you have any errors in running [compile.sh](compile.sh) or map-gen, make sure that the files have executable permissions. In Ubuntu, this can be changed by right-clicking on the file, clicking "Properties", then "Permissions" and then tick the appropriate box.

## Details
The program creates several layers of noise and then superimposes them with decreasing weights. The overall noise levels get seen as heights on a topological map. From there, each height gets converted to a biome type that has a unique colour. The colour for each pixel is then the colour associated with the biome it is in.

![Noise map](images/img2.png?raw=true "Noise map")
![Noise after biomes are applied](images/img1.png?raw=true "Noise after biomes are applied")

## Interaction
The program generates a random map every time it is run, but this can be changed by changing the WORLD_SEED variable in [main.cpp](main.cpp). You can change between the noise map and the biome map by pressing "2" and "1" on the keyboard respectively.

## Author
**Ralph McDougall** - [GitHub](https://github.com/RalphMcDougall)
