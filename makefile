CC = g++
CFLAGS = -std=c++17 -g
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

ALG_CPP = $(wildcard ./alg/*.cpp)
ALG_OBJ = $(patsubst %.cpp, %.o, $(ALG_CPP))

OBJ = main.o program.o chart.o $(ALG_OBJ)

BIN = test.out

.PHONY: all
all: $(BIN)

./alg/%.o: %.cpp %.hpp sort.o
	$(CC) $(CFLAGS) -c $<

chart.o: chart.cpp chart.cpp $(ALG_OBJ)
	$(CC) $(CFLAGS) -c $<

program.o: program.cpp program.hpp chart.o
	$(CC) $(CFLAGS) -c $<

main.o: main.cpp program.o
	$(CC) $(CFLAGS) -c $<

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $@

.PHONY: syntax
syntax: 
	$(CC) $(CFLAGS) -fsyntax-only $(ALG_CPP) $(wildcard ./alg/*.hpp) $(wildcard *.cpp) $(wildcard *.hpp)

.PHONY: check
check: $(BIN)
	./$(BIN)

.PHONY: clean
clean:
	-rm *.o
	-rm alg/*.o
	-rm $(BIN)
	-rm *.gch
