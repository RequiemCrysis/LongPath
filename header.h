#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

#define F 1000
#define NODE_NUM 14

void floyd(int n);
void init();
void rmVertex(int node1, int node2);
void printMap();
void setNode(int* node1, int* node2);
void game();
void player(char* name, int rmvert);

const int MAP[NODE_NUM][NODE_NUM];