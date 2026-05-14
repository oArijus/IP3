CXX = g++
CXXFLAGS = -std=c++11 -Wall

Vehicles.o: Vehicles.cpp Vehicles.h
	$(CXX) $(CXXFLAGS) -c Vehicles.cpp -o Vehicles.o

Dealership.o: Dealership.cpp Dealership.h Vehicles.h
	$(CXX) $(CXXFLAGS) -c Dealership.cpp -o Dealership.o

demo: Demo.cpp Vehicles.o Dealership.o
	$(CXX) $(CXXFLAGS) Demo.cpp Vehicles.o Dealership.o -o demo

run_demo: demo
	./demo

test: test.cpp Vehicles.o Dealership.o
	$(CXX) $(CXXFLAGS) test.cpp Vehicles.o Dealership.o -o test

run_test: test
	./test

clean:
	rm -f *.o demo test

rebuild: clean demo test