CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SRC= $(wildcard *.cc)
OBJ= $(SRC:.cc=.o)
OBJ_TEST = $(filter-out logic.o, $(OBJ)) $(TST:.cc=.o)
EXEC= snake


all: $(EXEC)

testcase : $(OBJ_TEST)
	g++ -std=c++11 -Wall -g  -o $@ $^

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depend:

	g++ -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC)
