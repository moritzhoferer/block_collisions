CXX = g++
CXXFLAGS = -flto -march=native -mtune=native -O3 -Wall

all: block_collisions

clean:
	rm -f *.o block_collisions

block_collisions: main.o core.o 
	$(CXX) -o block_collisions main.o core.o $(CXXFLAGS)

main.o: main.cpp core.h timer.h
	$(CXX) $(CXXFLAGS) -c main.cpp 

core.o: core.cpp core.h
	$(CXX) $(CXXFLAGS) -c core.cpp
