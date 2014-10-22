CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

VPATH = ../source:../source/drawing

all: ../main

../main: QuadTreeApp.o QuadTree.o drawing.o main.o Point.o Rect.o QuadNode.o
	$(CC) $(LFLAGS) $^ -o $@

QuadTreeApp.o: QuadTreeApp.cpp drawing_c.h
	$(CC) $(CFLAGS) $< -o $@

QuadTree.o: QuadTree.cpp Point.hpp Rect.hpp QuadNode.hpp
	$(CC) $(CFLAGS) $< -o $@

main.o: main.cpp QuadTreeApp.hpp
	$(CC) $(CFLAGS) $< -o $@

drawing.o: drawing.c drawing_c.h
	gcc $(CFLAGS) $< -o $@

QuadNode.o: QuadNode.cpp Rect.hpp
	$(CC) $(CFLAGS) $< -o $@

Point.o: Point.cpp
	$(CC) $(CFLAGS) $< -o $@

Rect.o: Rect.cpp Point.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *o main