#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ELEMENT 500
#define ALPHABET 26

//����ü
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
	int freq;	//���� �󵵼�
}Element;

typedef struct {
	Element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


//����� �����Լ�
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


//�켱����ť ����
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

//�켱����ť �ʱ�ȭ
void init(HeapType* h) {
	h->heap_size = 0;
}

//����ü �ʱ�ȭ
void init_alpha(AlphaType* p) {
	for (int i = 0; i < ALPHABET; i++) {
		p[i].ch = i + 97;
		p[i].freq = 0;
	}
}

//�����Լ�
void insert_min_heap(HeapType* h, Element item) {
	int i;
	i = ++(h->heap_size);
	//Ʈ�� �θ���� ���Ͽ� ������ġ Ȯ��
	while ((i != 1) && (item.freq < h->heap[i / 2].freq)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

//���� �� ��ȯ�Լ�
Element delete_min_heap(HeapType* h) {
	int parent, child;
	Element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		//�� �ڽĳ�� �� �� ���� ��� ã��
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

//Ʈ�� ����
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

	if (node == NULL) {
		printf("�޸� �Ҵ� ����\n");
		exit(-1);
	}
	node->left = left;
	node->right = right;
	return node;
}

//Ʈ�� ����
void destroy_tree(TreeNode* root) {
	if (root == NULL)
		return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

//�� ��� �Ǵ� �Լ�
int is_leaf(TreeNode* t) {
	return (!(t->left) && !(t->right));
}

void print_tree(TreeNode* t, int i, int code[]) {
	//�������� ���� 0 ����, ��ȯȣ��
	if (t->left) {
		code[i] = 0;
		print_tree(t->left, i, code[i + 1]);
	}
	//���������� ���� 1 ����, ��ȯȣ��
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

//������ Ʈ��
void hyffman_tree(AlphaType* a, int n) {
	TreeNode* node, * temp;
	Element e0, e1, e2;
	HeapType heap;
	init(&heap);
	int codes[100];

	//��� ���� �� ����
	for (int i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		node->weight.ch = a[i].ch;
		e0.freq = node->weight.freq = a[i].freq;
		e0.ptree = node;
		insert_min_heap(&heap, e0);
	}

	//������ ��� ��Ʈ�� n-1���� �ݺ�
	for (int i = 0; i < n - 1; i++) {
		//�ּҰ� ��� 2�� ��ȯ
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);

		//2���� ��带 ������ ��� ����
		temp = make_tree(e1.ptree, e2.ptree);
		e0.freq = temp->weight.freq = e1.freq + e2.freq;
		e0.ptree = temp;

		insert_min_heap(&heap, e0);
	}
	//���� Ʈ��
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
		printf("������ �ҷ����� ���߽��ϴ�");
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