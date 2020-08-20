all: main.c utils.c
	cc -Wall -o main main.c utils.c