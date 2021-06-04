CXX = g++
CXXFLAGS = -c -Wall
OBJS = cube.o math.o matrix.o

cube: $(OBJS)
	$(CXX) -o cube $(OBJS)

cube.o: cube.cpp
	$(CXX) $(CXXFLAGS) cube.cpp
	
math.o: math.cpp
	$(CXX) $(CXXFLAGS) math.cpp
	
matrix.o: matrix.cpp
	$(CXX) $(CXXFLAGS) matrix.cpp

clean:
	del $(OBJS)
	del cube.exe