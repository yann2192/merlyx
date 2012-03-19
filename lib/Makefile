# Generic GNUMakefile

ifneq (,)
	This makefile requires GNU Make.
endif

C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))
OUT := $(patsubst %.c, %, $(C_FILES))
CC = gcc
:q
CFLAGS = -Wall -shared
LDFLAGS =

all: compile

compile: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f *.o
	rm $(OUT)

.PHONY: clean depend
