build:
	g++ -Wall -std=c++17 -I"./libs" src/*.cpp src/Logger/*.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o buginfestationgame
