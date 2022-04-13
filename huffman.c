#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_ELEMENT 100
#define MAX_CODE 100
#define ALPHA_SIZE 58

enum ColorType {
    BLACK,
    darkBLUE,
    DarkGreen,
    darkSkyBlue,
    DarkRed,
    DarakPurple,
    DarkYellow,
    GRAY,
    DarkGray,
    BLUE,
    GREEN,
    SkyBlue,
    RED,
    PurPPLE,
    YELLOW,
    WHITE
}COLOR;

int bit = 0;
int beforebit = 0;      //��ȯ �� ��Ʈ ��(Ư������ ��Ʈ ������)
int afterbit = 0;       //��ȯ �� ��Ʈ ��(Ư������ ��Ʈ ������)

typedef struct TreeNode {
    int weight;                     //�󵵼�
    int alpha;                      //���ĺ�
    char code[MAX_CODE];            //��ȯ�� �ڵ带 ��� �迭
    int depth;                      //����� ����(��ȯ�� �ڵ��� ����)
    struct TreeNode* left_child;
    struct TreeNode* right_child;
} TreeNode;
typedef struct {
    TreeNode* ptree;                //����Ʈ��
    int key;                        //�󵵼�
} element;
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

init(HeapType* h);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType* h);
TreeNode* make_tree(TreeNode* left, TreeNode* right);
void destroy_tree(TreeNode* root);
void huffman_code(TreeNode* r, int n, char* code);
int is_leaf(TreeNode* r);
void sub_order(TreeNode* r, int i);
void level_order(TreeNode* r);
void huffman_tree(int freq[], int n, int total);
int existingBit(int total);
void textcolor(int colorNum);

//�켱���� ť �ʱ�ȭ
init(HeapType* h) {
    h->heap_size = 0;
}

//�����Լ�
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

//���� �� ��ȯ �Լ�
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child <= h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;

        if (temp.key < h->heap[child].key) break;

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
        fprintf(stderr, "�޸� ����\n");
        exit(1);
    }

    node->left_child = left;
    node->right_child = right;

    return node;
}

//Ʈ�� ����
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;

    destroy_tree(root->left_child);
    destroy_tree(root->right_child);

    free(root);
}

//������ �ڵ�� ��ȯ
void huffman_code(TreeNode* r, int n, char* code) {
    if (r) {
        n++;
        code[n] = '1';
        huffman_code(r->right_child, n, code);
        code[n] = '0';
        huffman_code(r->left_child, n, code);
        code[n] = '\0';
        if (r->left_child == NULL && r->right_child == NULL) {
            strcpy(r->code, code);
            r->depth = n;
        }
    }
}

//�ܸ�������� Ȯ��
int is_leaf(TreeNode* r) {
    return (!(r->left_child) && !(r->right_child));
}

//����Լ� ȣ���� ���� �ܸ���带 ã�� ������ ��
void sub_order(TreeNode* r, int i)
{
    if (r) {
        sub_order(r->right_child, i);
        sub_order(r->left_child, i);
        if (is_leaf(r) && r->depth == i)
        {
            printf("weight = %2d \tchar = %c \tcode = %s \n", r->weight, r->alpha, r->code);
            beforebit += r->weight * 7;                 //��ȯ �� ��Ʈ ��(Ư������ ��Ʈ ������)
            afterbit += (strlen(r->code) * r->weight);  //��ȯ �� ��Ʈ ��(Ư������ ��Ʈ ������)
        }
    }
}

//������ȸ
void level_order(TreeNode* r) {
    int i;
    for (i = 0; i < 10; i++) {
        sub_order(r, i);
    }
}

//������ Ʈ�� ����
void huffman_tree(int freq[], int n, int total) {
    int i;
    int j = 0;

    TreeNode* node, * x;
    HeapType heap;
    element e, e1, e2;
    char* code = (char*)malloc(sizeof(char));

    init(&heap);

    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.key = node->weight = freq[i];
        node->alpha = (i + 65);
        e.ptree = node;
        insert_min_heap(&heap, e);
        j++;
    }

    for (i = 1; i < j; i++) {
        e1 = delete_min_heap(&heap);
        e2 = delete_min_heap(&heap);
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        insert_min_heap(&heap, e);
    }

    e = delete_min_heap(&heap);
    huffman_code(e.ptree, -1, code);

    level_order(e.ptree);

    int exBit = existingBit(total);     //��ȯ �� Ư������ ���� ��Ʈ ��
    int extra = exBit - beforebit;      //Ư������ ��Ʈ ��
    int conBit = afterbit + extra;      //��ȯ �� Ư������ ���� ��Ʈ �� 

    textcolor(DarkYellow);
    printf("\n���� txt ��Ʈ�� : %d\n", exBit);
    printf("��ȯ txt ��Ʈ�� : %d\n", conBit);
    textcolor(RED);;
    printf("����� : %.2f\n", ((double)conBit / (double)exBit) * 100);
    textcolor(WHITE);

    destroy_tree(e.ptree);
}

//Ư�� ���� ���� ���� ��Ʈ�� ��ȯ
int existingBit(int total) {
    return 7 * total;
}

//�ܼ� �۾� �� ��ȯ
void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//����
void main() {
    int i = 0;
    int freq[ALPHA_SIZE] = { 0 };

    FILE* stream = fopen("english journal.txt", "r");
    if (stream == NULL) { puts("������ �����ϴ�."); }

    int count = 0;

    while (i != EOF) {
        i = fgetc(stream);
        count++;        //Ư�����ڿ� ���ĺ� ī��Ʈ

        if ((0 <= (i - 65) <= 25) || (32 <= (i - 65) <= 57)) {
            freq[i - 65] += 1;
        }

    }
    count--;            //while ������ null ��

    fclose(stream);
    huffman_tree(freq, ALPHA_SIZE, count);
}