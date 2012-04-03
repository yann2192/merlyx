# Generic GNUMakefile

ifneq (,)
	This makefile requires GNU Make.
endif

PROGRAM = merlyx
C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))
CC = gcc
:q
CFLAGS = -Wall -pipe -I./cuda
LDFLAGS = -ldl

all: $(PROGRAM)

gpunvidia.o: gpunvidia.c gpunvidia.h
	gcc -c gpunvidia.c -I./cuda -o gpunvidia.o

$(PROGRAM): .depend $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

depend: .depend

.depend: cmd = gcc -MM -MF depend $(var); cat depend >> .depend;
.depend: 
	@echo "Generating dependencies..."
	@$(foreach var, $(C_FILES), $(cmd))
	@rm -f depend

-include .depend

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f .depend *.o
	rm $(PROGRAM)

.PHONY: clean depend
