#include <stdio.h>
#include <stdlib.h>
#include <time.h> //rand seed 초기화를 위한 time.h

#define MAX_ELEMENTS 200 //최대 사이즈지만 heapSize를 통해 삽입된 크기만큼만 사용

typedef struct { //정수 구조체
	int key;
}element;

typedef struct { //heap 구조체
	element heap[MAX_ELEMENTS];
	int heapSize;
}heapType;

heapType* makeHeap() { //힙 생성
	return (heapType*)malloc(sizeof(heapType));
}

void init(heapType* h) { //힙 초기화
	h->heapSize = 0;
}

void insertMax(heapType* h, element e) {
	int i; //heapSize를 저장해 식을 조작할 변수 i 설정
	i = ++(h->heapSize);

	while (e.key > h->heap[i / 2].key && i != 1) {//i가 1이면 root 노드
		h->heap[i] = h->heap[i / 2];//element가 부모 노드보다 크면 둘이 교체
		i /= 2; //i를 반으로 줄이면서 부모노드 전부 탐색
	}
	h->heap[i] = e;
}

element makeRandElement() {//랜덤 int를 key로 갖는 random element 생성 함수
	int randInt = rand() % 99 + 1;
	element e = { randInt };
	return e;
}

element deletemaxHeap(heapType* h) { //최대값(root 노드)를 삭제하고, 반환하면서 힙 트리를 정렬하는 함수
	element item = h->heap[1]; //최대값 root 노드 item. 반환용
	element temp = h->heap[h->heapSize]; //temp는 heap의 마지막 노드로 root가 될 수 있다고 가정 + temp에 임시로 저장
	(h->heapSize)--; //최대 노드 삭제 후니까 heapSize 1 감소
	int parent = 1; int child = 2; //부모노드 자식노드 인덱스를 담는 변수 parent child. 각각 시작값 1, 2로 초기화
	while (child <= h->heapSize) {
		if (child < h->heapSize && h->heap[child].key < h->heap[child + 1].key) { //자식 노드를 비교해서 오른쪽 노드값이 더 클때 + child 인덱스가 heapSize보다 작을 때(배열 범위 초과 방지)
			child++; //자식노드 인덱스 값 증가 -> 자식 둘 중 더 큰 노드 찾기
		}
		if (temp.key >= h->heap[child].key) {//가정이 맞았을 경우(더 큰 자식노드보다 마지막 노드가 클 때) -> 마지막 노드 temp가 root로 될 수 있는 최대값이므로 루프 종료
			break;
		}
		h->heap[parent].key = h->heap[child].key; //자식 노드보다 마지막 노드가 작으면->부모 노드와 자식 노드 교환
		parent = child;//아랫 단계로 이동
		child = child * 2; //아랫 단계의 자식노드 탐색을 위해 2배(ex.부모노드가 2면 자식노드는 4,5)
	}
	h->heap[parent] = temp; //while문 탈출시-> 마지막 노드가 root노드가 되거나 트리의 마지막에 도착할 경우 temp 위치를 고정
	return item; //최대값 노드(root)값 반환
}
void printHeap(heapType* h) {//힙 출력 함수
	for (int i = 1; i <= h->heapSize; i++) { //heapSize만큼 반복문을 돌며 내용을 출력
		printf("heap[%d] = %d\n", i, h->heap[i].key);
	}
}

void heapSort(element elements[],int size) {//힙 정렬 함수
	heapType* h; //임시로 사용할 maxHeap
	h = makeHeap();
	init(h);

	for (int i = 0; i < size; i++) {
		insertMax(h, elements[i]); //난수 배열 elements의 요소를 힙에 차례로 삽입
	}
	for (int i = size-1; i >=0; i--) {
		elements[i] = deletemaxHeap(h); //가장 큰 값을 삭제하면서 elements 배열의 0번 인덱스부터 삽입
	}
	free(h);

}
void main() {
	srand(time(NULL));//난수 시드 초기화
	element elements[MAX_ELEMENTS];
	int size = 10;
	for (int i = 0; i < 10; i++) {
		elements[i] = makeRandElement(); //난수 구조체를 발생시키고 elements 배열에 차례로 삽입. 정렬돼있지 않은 상태
	}
	heapSort(elements, size); //힙 정렬
	for (int i = size-1; i>=0; i--) {
		printf("heapSorted array[%d] : %d\n",i, elements[i].key);
	}

}