# compiler to use
CC = gcc

# flags to pass compiler
CFLAGS = -g -Wall -O0 -std=c11 -ggdb -Wextra -Wshadow

# name for executable
EXE = speller

# space-separated list of header files
HDRS = dictionary.h linked_list.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
# LIBS =

# space-separated list of source files
SRCS = speller.c dictionary.c linked_list.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	del core $(EXE) *.o

# to run it?
run: $(EXE)
	$(EXE).exe
