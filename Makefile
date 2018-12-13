# Copyright mr. kadish is a big nerd 2018
build:
	g++ -std=c++17 ./src/main.cpp src/memory.cpp src/cyio.cpp src/types/base.cpp -ferror-limit=9999
run:
	make build
	./a.out