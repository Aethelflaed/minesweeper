
CXX=g++
CFLAGS=--std=c++17 -Wall

INCLUDE = -iquote ./include/

all: src/*.cpp include/*.hpp
	$(CXX) $(CFLAGS) $(INCLUDE) $?
