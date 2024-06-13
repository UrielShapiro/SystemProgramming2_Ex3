CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g

EXEC = Demo

SRCS = $(wildcard *.cpp)
SRCS := $(filter-out $(EXEC).cpp, $(SRCS))	# Remove the main file from the list of sources

OBJECTS = $(SRCS:.cpp=.o)

# SRCS = Board.cpp Buildable.cpp Catan.cpp Edge.cpp Player.cpp Tile.cpp Vertex.cpp GameConsts.cpp
# HEADRS = Board.hpp Buildable.hpp Edge.hpp Player.hpp Tile.hpp Vertex.hpp GameConsts.hpp Catan.hpp

demo = Demo

all: $(demo)

# $(EXEC): $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

$(demo): $(OBJECTS) $(EXEC).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(demo)

.PHONY: all clean
