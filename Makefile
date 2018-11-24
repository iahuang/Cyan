# Copyright mr. kadish is a big nerd 2018
build:
	echo "Building executable..."
	g++ -std=c++17 main2.cpp
debug:
	g++ -std=c++17 lib/framework.cpp -o main