CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++11 -g -fsanitize=address -pthread
LDFLAGS =  -fsanitize=address

SRC = main.cpp inputprocessor.cpp outputprocessor.cpp
OBJ = $(SRC:.cc=.o)
EXEC = program1

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)