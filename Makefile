CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror -g

SRC = ./src/main.cc 

.PHONY: all parse compile

all: $(SRC) 
	$(CXX) $(CXXFLAGS) $(SRC)

