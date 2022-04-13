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
int beforebit = 0;      //변환 전 비트 수(특수문자 비트 미포함)
int afterbit = 0;       //변환 후 비트 수(특수문자 비트 미포함)

typedef struct TreeNode {
    int weight;                     //빈도수
    int alpha;                      //알파벳
    char code[MAX_CODE];            //변환된 코드를 담는 배열
    int depth;                      //노드의 깊이(변환된 코드이 길이)
    struct TreeNode* left_child;
    struct TreeNode* right_child;
} TreeNode;
typedef struct {
    TreeNode* ptree;                //가상트리
    int key;                        //빈도수
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

//우선순위 큐 초기화
init(HeapType* h) {
    h->heap_size = 0;
}

//삽입함수
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

//삭제 값 반환 함수
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

//트리 생성
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    if (node == NULL) {
        fprintf(stderr, "메모리 에러\n");
        exit(1);
    }

    node->left_child = left;
    node->right_child = right;

    return node;
}

//트리 삭제
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;

    destroy_tree(root->left_child);
    destroy_tree(root->right_child);

    free(root);
}

//허프만 코드로 변환
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

//단말노드인지 확인
int is_leaf(TreeNode* r) {
    return (!(r->left_child) && !(r->right_child));
}

//재귀함수 호출을 통해 단말노드를 찾고 레벨과 비교
void sub_order(TreeNode* r, int i)
{
    if (r) {
        sub_order(r->right_child, i);
        sub_order(r->left_child, i);
        if (is_leaf(r) && r->depth == i)
        {
            printf("weight = %2d \tchar = %c \tcode = %s \n", r->weight, r->alpha, r->code);
            beforebit += r->weight * 7;                 //변환 전 비트 수(특수문자 비트 미포함)
            afterbit += (strlen(r->code) * r->weight);  //변환 후 비트 수(특수문자 비트 미포함)
        }
    }
}

//레벨순회
void level_order(TreeNode* r) {
    int i;
    for (i = 0; i < 10; i++) {
        sub_order(r, i);
    }
}

//허프만 트리 생성
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

    int exBit = existingBit(total);     //변환 전 특수문자 포함 비트 수
    int extra = exBit - beforebit;      //특수문자 비트 수
    int conBit = afterbit + extra;      //변환 후 특수문자 포함 비트 수 

    textcolor(DarkYellow);
    printf("\n기존 txt 비트수 : %d\n", exBit);
    printf("변환 txt 비트수 : %d\n", conBit);
    textcolor(RED);;
    printf("압축률 : %.2f\n", ((double)conBit / (double)exBit) * 100);
    textcolor(WHITE);

    destroy_tree(e.ptree);
}

//특수 문자 포함 기존 비트수 반환
int existingBit(int total) {
    return 7 * total;
}

//콘솔 글씨 색 변환
void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//메인
void main() {
    int i = 0;
    int freq[ALPHA_SIZE] = { 0 };

    FILE* stream = fopen("english journal.txt", "r");
    if (stream == NULL) { puts("파일이 없습니다."); }

    int count = 0;

    while (i != EOF) {
        i = fgetc(stream);
        count++;        //특수문자와 알파벳 카운트

        if ((0 <= (i - 65) <= 25) || (32 <= (i - 65) <= 57)) {
            freq[i - 65] += 1;
        }

    }
    count--;            //while 마지막 null 값

    fclose(stream);
    huffman_tree(freq, ALPHA_SIZE, count);
}