#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ELEMENT 500
#define ALPHABET 26

//구조체
typedef struct {
	char ch;
	int freq;
}AlphaType;

typedef struct {
	AlphaType weight;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef struct {
	TreeNode* ptree;
	int freq;	//문자 빈도수
}Element;

typedef struct {
	Element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


//사용자 정의함수
HeapType* create();
void init(HeapType* h);
void init_alpha(AlphaType* p);
void insert_min_heap(HeapType* h, Element item);
Element delete_min_heap(HeapType* h);
TreeNode* make_tree(TreeNode* left, TreeNode* right);
void destroy_tree(TreeNode* root);
int is_leaf(TreeNode* t);
void print_tree(TreeNode* p, int i, int code[]);
void hyffman_tree(AlphaType* a, int n);


//우선순위큐 생성
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

//우선순위큐 초기화
void init(HeapType* h) {
	h->heap_size = 0;
}

//구조체 초기화
void init_alpha(AlphaType* p) {
	for (int i = 0; i < ALPHABET; i++) {
		p[i].ch = i + 97;
		p[i].freq = 0;
	}
}

//삽입함수
void insert_min_heap(HeapType* h, Element item) {
	int i;
	i = ++(h->heap_size);
	//트리 부모노드와 비교하여 삽입위치 확인
	while ((i != 1) && (item.freq < h->heap[i / 2].freq)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//삭제 값 반환함수
Element delete_min_heap(HeapType* h) {
	int parent, child;
	Element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		//두 자식노드 중 더 작은 노드 찾기
		if ((child < h->heap_size) && (h->heap[child].freq > h->heap[child + 1].freq))
			child++;
		if (temp.freq < h->heap[child].freq)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//트리 구성
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

	if (node == NULL) {
		printf("메모리 할당 오류\n");
		exit(-1);
	}
	node->left = left;
	node->right = right;
	return node;
}

//트리 제거
void destroy_tree(TreeNode* root) {
	if (root == NULL)
		return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

//잎 노드 판단 함수
int is_leaf(TreeNode* t) {
	return (!(t->left) && !(t->right));
}

void print_tree(TreeNode* t, int i, int code[]) {
	//왼쪽으로 가면 0 저장, 순환호출
	if (t->left) {
		code[i] = 0;
		print_tree(t->left, i, code[i + 1]);
	}
	//오른쪽으로 가면 1 저장, 순환호출
	if (t->right) {
		code[i] = 1;
		print_tree(t->right, i, code[i + 1]);
	}

	if (is_leaf) {
		printf("%3c\t%3d\t", t->weight.ch, t->weight.freq);
		int j = 0;
		while (code[j] == 0 || code[j] == 1) {
			printf("%d", code[j]);
			j++;
		}
		printf("\n");
	}
}

//허프만 트리
void hyffman_tree(AlphaType* a, int n) {
	TreeNode* node, * temp;
	Element e0, e1, e2;
	HeapType heap;
	init(&heap);
	int codes[100];

	//노드 생성 및 삽입
	for (int i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		node->weight.ch = a[i].ch;
		e0.freq = node->weight.freq = a[i].freq;
		e0.ptree = node;
		insert_min_heap(&heap, e0);
	}

	//마지막 노드 루트로 n-1까지 반복
	for (int i = 0; i < n - 1; i++) {
		//최소값 노드 2개 반환
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);

		//2개의 노드를 가지는 노드 생성
		temp = make_tree(e1.ptree, e2.ptree);
		e0.freq = temp->weight.freq = e1.freq + e2.freq;
		e0.ptree = temp;

		insert_min_heap(&heap, e0);
	}
	//최종 트리
	e0 = delete_min_heap(&heap);

	print_tree(e0.ptree, 0, codes);

	destroy_tree(e0.ptree);
}


int main() {
	AlphaType data[ALPHABET];
	AlphaType* copydata;

	init_alpha(data);
	int count = 0;

	char* str = (char*)malloc(sizeof(char));



	FILE* fp = fopen("124124.txt", "r");
	if (fp == NULL) {
		printf("파일을 불러오지 못했습니다");
		exit(1);
	}

	if (fp != NULL) {
		while (feof(fp) == 0) {
			fgets(str, 25, fp);
			count++;

		}
	}
	  
	for (int j = 0; j < count; j++) {
		printf("%s", str);
	}

	fclose(fp);
	return 0;
}