CC     = g++
CFLAGS = -std=c++17 -O2
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

ALG_CPP = $(wildcard ./alg/*.cpp)
ALG_OBJ = $(patsubst %.cpp, %.o, $(ALG_CPP))

OBJ = main.o program.o chart.o $(ALG_OBJ)
BIN = sorting-visualizer.out

.PHONY: all clean

all: $(BIN)

alg/sort.o: alg/sort.cpp alg/sort.hpp
	$(CC) $(CFLAGS) -c $< -o $@

alg/%.o: alg/%.cpp alg/%.hpp alg/sort.o
	$(CC) $(CFLAGS) -c $< -o $@

chart.o: chart.cpp chart.cpp $(ALG_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

program.o: program.cpp program.hpp chart.o
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.cpp program.o
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $@

clean:
	-rm *.o
	-rm alg/*.o
	-rm $(BIN)
