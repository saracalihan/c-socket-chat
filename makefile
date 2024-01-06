CC=cc
FLAGS= -Wall -Wextra -Wno-format -Wno-unused-parameter -ggdb

all: compile link run
compile: src/server.c
	$(CC) $(FLAGS) -I./includes -c ./src/commands.c -o ./obj/commands.o
	$(CC) $(FLAGS) -I./includes -c ./src/commons.c -o ./obj/commons.o
	$(CC) $(FLAGS) -I./includes -c ./src/server.c -o ./obj/server.o
link:
	$(CC) ./obj/* -o ./bin/program
run: bin/program
	./bin/program
rm:
	rm bin/* obj/*
