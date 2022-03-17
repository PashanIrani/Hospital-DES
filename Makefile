

SRC_DIR=./src
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC)/%.cpp,./%.o,$(SRC_FILES))

CC=cc
CXX=g++
CCFLAGS= -g -std=c++11 -Wall -Werror
LDLIBS= -lm

all: project1

project1: $(OBJ_FILES)
	$(CXX) $(CCFLAGS) $(LDLIBS) -o $@ $^ 

./%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CCFLAGS) -c -o $@ $< 


clean:
	rm ./project1