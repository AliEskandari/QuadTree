CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

EXE = main

all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(OBJS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJS) $(EXE)