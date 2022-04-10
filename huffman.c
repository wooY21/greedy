#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 100
#define MAX_CODE 100
#define ALPHA_SIZE 58

int bit = 0;
//int beforebit = 0;
//int afterbit = 0;

typedef struct TreeNode {
    int weight;
    int alpha;
    char code[MAX_CODE];
    int depth;
    struct TreeNode* left_child;
    struct TreeNode* right_child;
} TreeNode;
typedef struct {
    TreeNode* ptree;
    int key;
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
int convertedBit(TreeNode* r, int i);

init(HeapType* h)
{
    h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item)
{
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if ((child <= h->heap_size) &&
            (h->heap[child].key) > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 에러\n");
        exit(1);
    }
    node->left_child = left;
    node->right_child = right;
    return node;
}

void destroy_tree(TreeNode* root)
{
    if (root == NULL) return;
    destroy_tree(root->left_child);
    destroy_tree(root->right_child);
    free(root);
}

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

int is_leaf(TreeNode* r) {
    return (!(r->left_child) && !(r->right_child));
}

void sub_order(TreeNode* r, int i)
{
    if (r)
    {

        sub_order(r->right_child, i);
        sub_order(r->left_child, i);
        if (is_leaf(r) && r->depth == i)
        {
            printf("weight = %2d depth = %2d char = %c code = %s \n", r->weight, r->depth, r->alpha, r->code);
            //afterbit += (strlen(r->code) * r->weight);
        }
    }
}
void level_order(TreeNode* r)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        sub_order(r, i);
    }
}

void huffman_tree(int freq[], int n, int total)
{
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

    int exBit = 0;
    int conBit = 0;


    level_order(e.ptree);
    for (int k = 0; k < 10; k++) {
        convertedBit(e.ptree, k, bit);
    }
    printf("\n");


    exBit = existingBit(total);
    //int extra = total - afterbit;
    //printf("\nextra : %d\n", extra);
    conBit = bit;
    printf("기존txt 비트수 : %d\n", exBit);
    printf("변환txt 비트수 : %d\n", conBit);
    printf("압축률 : %.2f\n", ((double)conBit / (double)exBit) * 100);
    destroy_tree(e.ptree);
}

int existingBit(int total) {
    return 7 * total;
}

int convertedBit(TreeNode* r, int i) {

    if (r)
    {

        convertedBit(r->right_child, i);
        convertedBit(r->left_child, i);
        if (is_leaf(r) && r->depth == i)
        {

            int a = r->depth;
            int b = r->weight;
            bit += a * b;

        }
    }

    return bit;
}

void main()
{
    int i = 0;
    int freq[ALPHA_SIZE] = { 0 };


    FILE* stream = fopen("124124.txt", "r");
    if (stream == NULL) { puts("파일이 없습니다."); }

    int count = 0;


    while (i != EOF)
    {
        i = fgetc(stream);

        if ((0 <= (i - 65) <= 25) || (32 <= (i - 65) <= 57))
        {
            freq[i - 65] += 1;
            count++;

        }

    }
    count--; //while 마지막 null 값
    fclose(stream);


    huffman_tree(freq, ALPHA_SIZE, count);
}