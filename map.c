#include "header.h"

/*
─│┌┐┘└
A ──D ───I ─N 
│    │    ┌┘  │
│    │    J ┐  │
B ┐  │    ││  │
│└─E ┐  ││  │
│      F ─┘K   │
C       │    └L ┘
│      └┐    │  
│    ┌─H ┐  │  
└G ─┘    └─M   
*/

const int MAP[NODE_NUM][NODE_NUM] = {
	{0, 2, F, 2, F, F, F, F, F, F, F, F, F, F},
	{2, 0, 2, F, 3, F, F, F, F, F, F, F, F, F},
	{F, 2, 0, F, F, F, 3, F, F, F, F, F, F, F},
	{2, F, F, 0, 3, F, F, F, 3, F, F, F, F, F},
	{F, 3, F, 3, 0, 1, F, F, F, F, F, F, F, F},
	{F, F, F, F, 1, 0, F, 3, F, 4, F, F, F, F},
	{F, F, 3, F, F, F, 0, 4, F, F, F, F, F, F},
	{F, F, F, F, F, 3, 4, 0, F, F, F, F, 3, F},
	{F, F, F, 3, F, F, F, F, 0, 2, F, F, F, 1},
	{F, F, F, F, F, 4, F, F, 2, 0, 3, F, F, F},
	{F, F, F, F, F, F, F, F, F, 3, 0, 1, F, F},
	{F, F, F, F, F, F, F, F, F, F, 1, 0, 2, 6},
	{F, F, F, F, F, F, F, 3, F, F, F, 2, 0, F},
	{F, F, F, F, F, F, F, F, 1, F, F, 6, F, 0},
};

int _map[NODE_NUM][NODE_NUM];

//for floyd
int distance[NODE_NUM][NODE_NUM];
int path_stack[];

void floyd(int n){
	int i, j, k;

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			distance[i][j] = _map[i][j];

	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(distance[i][k] + distance[k][j] < distance[i][j])
					distance[i][j] = distance[i][k] + distance[k][j];
}

void init(){
	int i, j;
	for(i = 0; i < NODE_NUM; i++)
		for(j = 0; j < NODE_NUM; j++)
			_map[i][j] = MAP[i][j];
}

//get parsed node eg A->0, D->3
void rmVertex(int node1, int node2){
	_map[node1][node2] = F;
	_map[node2][node1] = F;
}

void printMap(){
	puts("A ──D ───I ─N ");
	puts("│    │    ┌┘  │");
	puts("│    │    J ┐  │");
	puts("B ┐  │    ││  │");
	puts("│└─E ┐  ││  │");
	puts("│      F ─┘K   │");
	puts("C       │    └L ┘");
	puts("│      └┐    │  ");
	puts("│    ┌─H ┐  │  ");
	puts("└G ─┘    └─M   ");
}

void game(){
	int node1, node2;
	int rmvert;
	char p1[11], p2[11];
	char winner[11];
	int score1, score2;


	srand(time(NULL));
	setNode(&node1, &node2);
	rmvert = rand() % 3 + 2;

	printf("플레이어1의 이름을 입력해주세요(최대 10바이트) : ");
	scanf("%s", p1);
	printf("플레이어2의 이름을 입력해주세요(최대 10바이트) : ");
	scanf("%s", p2);

	printMap();
	printf("%c에서 %c까지 가는 가장 긴 경로를 만듭니다.\n", node1 + 'A', node2 + 'A');

	player(p1, rmvert);
	score1 = distance[node1][node2];

	player(p2, rmvert);
	score2 = distance[node1][node2];

	if(score1 > score2){
		if(score1 != 1000) strcpy(winner, p1);
	}else{
		if(score2 != 1000) strcpy(winner, p2);
	}

	if(score1 == score2) puts("둘다 패배하셨습니다...");
	else printf("%s : %d, %s : %d, %s 승리!\n", p1, score1, p2, score2, winner);
}

void player(char* name, int rmvert){
	char tnode1, tnode2;
	int t1, t2;

	init();
	printf("%s의 차례 - %d개의 선을 제거해주세요\n:", name, rmvert);

	while(rmvert > 0){
		fflush(stdin);
		scanf("%c %c", &tnode1, &tnode2);
		t1 = tnode1 - 'A';
		t2 = tnode2 - 'A';
		if(_map[t1][t2] == F){
			puts("존재하지 않는 선입니다.");
			continue;
		}
		rmVertex(t1, t2);
		rmvert--;
		printf("%d회 남았습니다.\n", rmvert);
	}

	floyd(NODE_NUM);
}

//set start and end node;
void setNode(int* node1, int* node2){
	int key;
	/*
	AL
	BN
	GI
	EM
	DH
	*/
	srand(time(NULL));
	key = rand() % 5 + 1;

	switch(key){
	case 1: *node1 = 0; *node2 = 11; break;
	case 2: *node1 = 1; *node2 = 13; break;
	case 3: *node1 = 6; *node2 = 8; break;
	case 4: *node1 = 4; *node2 = 12; break;
	case 5: *node1 = 3; *node2 = 7; break;
	}
}