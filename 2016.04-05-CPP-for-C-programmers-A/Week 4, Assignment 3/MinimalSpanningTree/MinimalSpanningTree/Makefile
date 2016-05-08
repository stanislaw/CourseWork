appname := minimal-spanning-tree

CXX := g++
CXXFLAGS := -std=c++11

srcfiles := $(wildcard *.cpp)
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

default: build run

run:
	./$(appname)

build: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

clean:
	rm -f $(objects)

