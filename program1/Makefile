CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=address -pthread
LDFLAGS =  -fsanitize=address

SRC = main.cpp inputprocessor.cpp outputprocessor.cpp connectionclient.cpp
OBJ = $(SRC:.cc=.o)
EXEC = program1.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)