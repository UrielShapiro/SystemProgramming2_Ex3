CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

EXEC = Demo

SRCS = $(wildcard *.cpp)					# Get all the .cpp files in the current directory
SRCS := $(filter-out $(EXEC).cpp, $(SRCS))	# Remove the main file from the list of sources

OBJECTS = $(SRCS:.cpp=.o)

demo = Demo

all: $(demo)

$(demo): $(OBJECTS) $(EXEC).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(demo)
	valgrind $(VALGRIND_FLAGS) ./$(demo)

catan: $(demo)
	./$(demo)

clean:
	rm -f *.o $(demo)

.PHONY: all clean valgrind catan
