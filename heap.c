#include <stdio.h>
#include <stdlib.h>
#include <time.h> //rand seed �ʱ�ȭ�� ���� time.h

#define MAX_ELEMENTS 200 //�ִ� ���������� heapSize�� ���� ���Ե� ũ�⸸ŭ�� ���

typedef struct { //���� ����ü
	int key;
}element;

typedef struct { //heap ����ü
	element heap[MAX_ELEMENTS];
	int heapSize;
}heapType;

heapType* makeHeap() { //�� ����
	return (heapType*)malloc(sizeof(heapType));
}

void init(heapType* h) { //�� �ʱ�ȭ
	h->heapSize = 0;
}

void insertMax(heapType* h, element e) {
	int i; //heapSize�� ������ ���� ������ ���� i ����
	i = ++(h->heapSize);

	while (e.key > h->heap[i / 2].key && i != 1) {//i�� 1�̸� root ���
		h->heap[i] = h->heap[i / 2];//element�� �θ� ��庸�� ũ�� ���� ��ü
		i /= 2; //i�� ������ ���̸鼭 �θ��� ���� Ž��
	}
	h->heap[i] = e;
}

element makeRandElement() {//���� int�� key�� ���� random element ���� �Լ�
	int randInt = rand() % 99 + 1;
	element e = { randInt };
	return e;
}

element deletemaxHeap(heapType* h) { //�ִ밪(root ���)�� �����ϰ�, ��ȯ�ϸ鼭 �� Ʈ���� �����ϴ� �Լ�
	element item = h->heap[1]; //�ִ밪 root ��� item. ��ȯ��
	element temp = h->heap[h->heapSize]; //temp�� heap�� ������ ���� root�� �� �� �ִٰ� ���� + temp�� �ӽ÷� ����
	(h->heapSize)--; //�ִ� ��� ���� �Ĵϱ� heapSize 1 ����
	int parent = 1; int child = 2; //�θ��� �ڽĳ�� �ε����� ��� ���� parent child. ���� ���۰� 1, 2�� �ʱ�ȭ
	while (child <= h->heapSize) {
		if (child < h->heapSize && h->heap[child].key < h->heap[child + 1].key) { //�ڽ� ��带 ���ؼ� ������ ��尪�� �� Ŭ�� + child �ε����� heapSize���� ���� ��(�迭 ���� �ʰ� ����)
			child++; //�ڽĳ�� �ε��� �� ���� -> �ڽ� �� �� �� ū ��� ã��
		}
		if (temp.key >= h->heap[child].key) {//������ �¾��� ���(�� ū �ڽĳ�庸�� ������ ��尡 Ŭ ��) -> ������ ��� temp�� root�� �� �� �ִ� �ִ밪�̹Ƿ� ���� ����
			break;
		}
		h->heap[parent].key = h->heap[child].key; //�ڽ� ��庸�� ������ ��尡 ������->�θ� ���� �ڽ� ��� ��ȯ
		parent = child;//�Ʒ� �ܰ�� �̵�
		child = child * 2; //�Ʒ� �ܰ��� �ڽĳ�� Ž���� ���� 2��(ex.�θ��尡 2�� �ڽĳ��� 4,5)
	}
	h->heap[parent] = temp; //while�� Ż���-> ������ ��尡 root��尡 �ǰų� Ʈ���� �������� ������ ��� temp ��ġ�� ����
	return item; //�ִ밪 ���(root)�� ��ȯ
}
void printHeap(heapType* h) {//�� ��� �Լ�
	for (int i = 1; i <= h->heapSize; i++) { //heapSize��ŭ �ݺ����� ���� ������ ���
		printf("heap[%d] = %d\n", i, h->heap[i].key);
	}
}

void heapSort(element elements[],int size) {//�� ���� �Լ�
	heapType* h; //�ӽ÷� ����� maxHeap
	h = makeHeap();
	init(h);

	for (int i = 0; i < size; i++) {
		insertMax(h, elements[i]); //���� �迭 elements�� ��Ҹ� ���� ���ʷ� ����
	}
	for (int i = size-1; i >=0; i--) {
		elements[i] = deletemaxHeap(h); //���� ū ���� �����ϸ鼭 elements �迭�� 0�� �ε������� ����
	}
	free(h);

}
void main() {
	srand(time(NULL));//���� �õ� �ʱ�ȭ
	element elements[MAX_ELEMENTS];
	int size = 10;
	for (int i = 0; i < 10; i++) {
		elements[i] = makeRandElement(); //���� ����ü�� �߻���Ű�� elements �迭�� ���ʷ� ����. ���ĵ����� ���� ����
	}
	heapSort(elements, size); //�� ����
	for (int i = size-1; i>=0; i--) {
		printf("heapSorted array[%d] : %d\n",i, elements[i].key);
	}

}