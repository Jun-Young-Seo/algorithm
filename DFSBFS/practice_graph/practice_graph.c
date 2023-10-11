#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICS 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICS] = {FALSE};

#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct { // 큐 타입
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;


typedef struct GraphType {
	int n; //정점의 수
	int adj_mat[MAX_VERTICS][MAX_VERTICS];
}GraphType;

// 오류 함수
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void queue_init(QueueType* q) {
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


void init(GraphType* g) {//그래프 초기 설정 함수
	g->n = 0;
	for (int rows = 0; rows < MAX_VERTICS; rows++) {
		for (int columns = 0; columns < MAX_VERTICS; columns++) {
			g->adj_mat[rows][columns] = 0;
		}
	}
}

void visitedArrayClear() { // visited 배열 초기화 함수
	for (int i = 0; i < MAX_VERTICS; i++) {
		visited[i] = FALSE;
	}
}
void insert_vertex(GraphType* g, int vertex) {//정점 갯수 추가 함수
	if (((g->n) + 1) > MAX_VERTICS) {
		printf("Vertex overflow\n");
		return;
	}
	(g->n)++;
}

void insert_edge(GraphType* g, int start, int end) {//간선 추가함수
	if (start >= g->n || end>= g->n) {
		printf("edge overflow\n");
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType* g) {//행렬 출력 함수
	printf("그래프를 인접행렬로 표현합니다. \n");
	for (int i = 0; i < g->n; i++) {
		int degree = 0; // 각 노드의 차수를 변수 degree에 저장 - 0으로 초기화
		for (int j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1) {//1이라면(간선이 있다면)
				degree++; //차수 1씩 증가
			}
		}

		printf("%d번 노드의 차수: %d\n", i, degree);
	}
	for (int i = 0; i < g->n; i++) {
		for (int n = 0; n < g->n; n++) {
			printf("[%d]", g->adj_mat[i][n]);
			if (g->adj_mat[i][n] == 1) {
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void dfs_mat(GraphType* g, int start) {//depth first search
	visited[start] = TRUE;
	printf("%d -> ", start);
	for (int i = 0; i < g->n; i++) {
		if (g->adj_mat[start][i] == 1 && visited[i]==FALSE) {
			dfs_mat(g, i);
		}
	}
}

void bfs_mat(GraphType* g, int v) {//breadth first search
	int w;
	QueueType q;
	queue_init(&q);
	
	visited[v] = TRUE;
	printf("%d -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = 0; w < g->n; w++)
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d -> ", w);
				enqueue(&q, w);
			}
	}
}

void selectMenu(GraphType *g) { //메뉴 고르게 하는 함수
	int select, start;
	while (TRUE) {
		printf("1: DFS, 2: BFS, 3: Exit >>");
		scanf_s("%d", &select);
		switch (select) {
		case 1: 
			printf("깊이우선탐색 방식입니다.\n");
			printf("시작 노드 입력 >>");
			scanf_s("%d", &start);
			dfs_mat(g, start);
			printf("\n");
			//배열을 전역으로 선언했으므로 탐색 방식에 따라 출력 후 초기화
			visitedArrayClear(); 
			break;
		case 2:
			printf("너비우선방식 탐색입니다.\n");
			printf("시작 노드 입력 >>");
			scanf_s("%d", &start);
			bfs_mat(g, start);
			printf("\n");
			//배열을 전역으로 선언했으므로 탐색 방식에 따라 출력 후 초기화
			visitedArrayClear();
			break;
		case 3:
			printf("프로그램을 종료합니다.");
			return;
		default:
			printf("숫자 입력 오류 1,2,3 중 선택\n");
			break;
		}
	}
}

int main(void) {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));

	//초기화
	init(g);
	//정점 추가
	for (int i = 0; i < 4; i++) {
		insert_vertex(g, i);
	}
	//간선 추가
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	print_adj_mat(g); //인접행렬 출력
	selectMenu(g);

	return 0;
}