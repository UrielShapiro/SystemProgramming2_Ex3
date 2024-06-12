CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g

SRCS = Board.cpp Buildable.cpp Catan.cpp Demo.cpp Edge.cpp Player.cpp Tile.cpp Vertex.cpp
HEADRS = Board.hpp Buildable.hpp Edge.hpp Player.hpp Tile.hpp Vertex.hpp

OBJS = $(SRCS:.cpp=.o)

demo = Demo

all: $(demo)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp $(HEADRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(demo)

.PHONY: all clean
