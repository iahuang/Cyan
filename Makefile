# Copyright mr. kadish is a big nerd 2018
build:
	g++-8 -std=c++17 ./src/main.cpp src/memory.cpp
run:
	g++-8 -std=c++17 ./src/main.cpp src/memory.cpp
	./a.out