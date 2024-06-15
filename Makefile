CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

Test = Test
demo = Demo

SRCS = $(wildcard *.cpp)					# Get all the .cpp files in the current directory
SRCS := $(filter-out $(demo).cpp, $(SRCS))	# Remove the main file from the list of sources
SRCS := $(filter-out $(Test).cpp, $(SRCS))	# Remove the main file from the list of sources

OBJECTS = $(SRCS:.cpp=.o)


all: $(demo)

$(demo): $(OBJECTS) $(demo).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(demo)
	valgrind $(VALGRIND_FLAGS) ./$(demo)

catan: $(demo)
	./$(demo)

$(Test): $(OBJECTS) $(Test).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$(Test)

clean:
	rm -f *.o $(demo) $(Test)

.PHONY: all clean valgrind catan
