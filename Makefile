SOURCES=$(wildcard *.c) $(wildcard */*.c)
HEADERS=$(SOURCES:.c=.h)
FLAGS=-DDEBUG -g

N=8

all: main

main: $(SOURCES) $(HEADERS)
	mpicc $(SOURCES) $(FLAGS) -o main

clear: clean

clean:
	rm main

run: main
	mpirun -np $(N) --hostfile labos --oversubscribe ./main $(ARGS)
