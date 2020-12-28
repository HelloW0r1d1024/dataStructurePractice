#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int KeyType;

typedef struct {
    KeyType key;
} SElemType;

typedef struct {
    SElemType * elem;
    int listsize;
    int length;
} SSTable;

int initSSTable(SSTable &ST, SElemType value[], int n) {
    ST.elem = (SElemType *)malloc(sizeof(SElemType) * LIST_INIT_SIZE);
    if (!ST.elem) exit(-2);
    ST.listsize = LIST_INIT_SIZE;
    ST.length = n;
    SElemType * p = ST.elem + 1;
    for (int i = 0; i < n; i++)
        *p++ = value[i];
    
    return 1;
}

int binSearch(SSTable ST, KeyType key, int low, int high) {

    if (low > high)
        return -1;
    int mid = (low+high) / 2;
    
    if (key == (ST.elem+mid)->key)
        return mid;
    else if (key < (ST.elem+mid)->key)
        return binSearch(ST, key, low, mid-1);
    else 
        return binSearch(ST, key, mid+1, high);

}

int main() {
    SElemType values[10] = {12,23,28,35,37,39,50,60,78,90};
    SSTable ST;
    initSSTable(ST, values, 10);

    for (int i = 0; i < 10; i++) 
        printf("%d ", (ST.elem+i)->key);
    printf("\n");

    for (int i = 0; i < 2; i++) {
        int x;
        scanf("%d", &x);
        int tmp = binSearch(ST, x, 1, ST.length);
        if (-1 == tmp)
            printf("该记录不存在\n");
        else
            printf("该记录在表中位置%d\n", tmp);
    }
} // 测试用例