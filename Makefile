CXX = g++
CXXFLAGS = -flto -march=native -mtune=native -O3 -Wall

all: block_collisions

clean:
	rm -f *.o block_collisions

block_collisions: main.o
	$(CXX) -o block_collisions main.o $(CXXFLAGS)

main.o: main.cpp core.cpp timer.h
	$(CXX) $(CXXFLAGS) -c main.cpp 
