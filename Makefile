# Copyright mr. kadish is a big nerd 2018
build:
	clang++ -g -std=c++17 src/main.cpp src/memory.cpp src/types/base.cpp src/cyio.cpp
run:
	make build
	./a.out