#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define ElemType int

typedef int Status;

typedef struct LNode {
    ElemType data;
    struct LNode * next;
} * LinkList;

// 创建元素个数为n的链表, reversed = False
void createList(LinkList &L, int n) {
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList p = L;

    for (int i = 0; i < n; i++) {
        LinkList q = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &q->data);
            
        q->next = p->next;
        p->next = q;
        p = q;
    }
    
}

void selectionSort(LinkList &L) {
    LinkList r = L->next; // r指向无序序列的第一个结点
    LinkList min = r->next; // 临时存放最小项

    while (r->next) {
        LinkList p = r->next;
        while (p) {
            if (p->data < min->data)
             min = p;
            p = p->next;
        }
        L->data = min->data;
        min->data = r->data;
        r->data = L->data;
        r = r->next;
    }
}

void printList(LinkList L) {
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main() {
    LinkList L = NULL;
    createList(L, 5);
    printf("排序前:");
    printList(L);
    printf("\n排序后:");
    selectionSort(L);
    printList(L);
} // 测试用例