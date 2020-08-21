all: main.c utils.c getline.c
	cc -Wall -o gameoflife main.c utils.c getline.c