#include <stdio.h>
#include <iostream>


typedef struct Vertex {
	int vtx1;
	int vtx2;
	int value;
	struct Vertex *next;
}Vertex;

Vertex* createVertex(int vertex, int value);
void createMap(const char* file);


