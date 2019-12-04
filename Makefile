CXX = g++
CXXFLAGS = -flto -march=native -mtune=native -O3 -Wall

all: block_collisions

clean:
	rm *.o block_collisions

block_collisions: main.o
	$(CXX) -o block_collisions $(CXXFLAGS) main.o 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp 
