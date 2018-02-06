CC=gcc
SOURCES = ../main.c ../convertToRPN.c ../evaluateRPN.c
LIBS= -lm
CFLAGS= -Wall -O3

all: $(SOURCES) ../defs.h
	$(CC) -o  terminalMath $(SOURCES) $(LIBS)  $(CFLAGS)

.PHONY: clean

clean:
	$(RM) terminalMath
