all: main.c utils.c
	cc -Wall -o gameoflife main.c utils.c