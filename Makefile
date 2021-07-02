CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

INC = -I include/
SRC = $(wildcard src/*/*.c)

all:
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) example/cli.c -o bin/cli.exe -lm

run:
	bin/cli.exe

clean:
	rm bin/*
