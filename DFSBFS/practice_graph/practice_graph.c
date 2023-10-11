#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICS 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICS] = {FALSE};

#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct { // ť Ÿ��
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;


typedef struct GraphType {
	int n; //������ ��
	int adj_mat[MAX_VERTICS][MAX_VERTICS];
}GraphType;

// ���� �Լ�
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void queue_init(QueueType* q) {
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q) {
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


void init(GraphType* g) {//�׷��� �ʱ� ���� �Լ�
	g->n = 0;
	for (int rows = 0; rows < MAX_VERTICS; rows++) {
		for (int columns = 0; columns < MAX_VERTICS; columns++) {
			g->adj_mat[rows][columns] = 0;
		}
	}
}

void visitedArrayClear() { // visited �迭 �ʱ�ȭ �Լ�
	for (int i = 0; i < MAX_VERTICS; i++) {
		visited[i] = FALSE;
	}
}
void insert_vertex(GraphType* g, int vertex) {//���� ���� �߰� �Լ�
	if (((g->n) + 1) > MAX_VERTICS) {
		printf("Vertex overflow\n");
		return;
	}
	(g->n)++;
}

void insert_edge(GraphType* g, int start, int end) {//���� �߰��Լ�
	if (start >= g->n || end>= g->n) {
		printf("edge overflow\n");
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType* g) {//��� ��� �Լ�
	printf("�׷����� ������ķ� ǥ���մϴ�. \n");
	for (int i = 0; i < g->n; i++) {
		int degree = 0; // �� ����� ������ ���� degree�� ���� - 0���� �ʱ�ȭ
		for (int j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1) {//1�̶��(������ �ִٸ�)
				degree++; //���� 1�� ����
			}
		}

		printf("%d�� ����� ����: %d\n", i, degree);
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

void selectMenu(GraphType *g) { //�޴� ���� �ϴ� �Լ�
	int select, start;
	while (TRUE) {
		printf("1: DFS, 2: BFS, 3: Exit >>");
		scanf_s("%d", &select);
		switch (select) {
		case 1: 
			printf("���̿켱Ž�� ����Դϴ�.\n");
			printf("���� ��� �Է� >>");
			scanf_s("%d", &start);
			dfs_mat(g, start);
			printf("\n");
			//�迭�� �������� ���������Ƿ� Ž�� ��Ŀ� ���� ��� �� �ʱ�ȭ
			visitedArrayClear(); 
			break;
		case 2:
			printf("�ʺ�켱��� Ž���Դϴ�.\n");
			printf("���� ��� �Է� >>");
			scanf_s("%d", &start);
			bfs_mat(g, start);
			printf("\n");
			//�迭�� �������� ���������Ƿ� Ž�� ��Ŀ� ���� ��� �� �ʱ�ȭ
			visitedArrayClear();
			break;
		case 3:
			printf("���α׷��� �����մϴ�.");
			return;
		default:
			printf("���� �Է� ���� 1,2,3 �� ����\n");
			break;
		}
	}
}

int main(void) {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));

	//�ʱ�ȭ
	init(g);
	//���� �߰�
	for (int i = 0; i < 4; i++) {
		insert_vertex(g, i);
	}
	//���� �߰�
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	print_adj_mat(g); //������� ���
	selectMenu(g);

	return 0;
}