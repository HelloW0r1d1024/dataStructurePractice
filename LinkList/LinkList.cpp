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

// 创建元素个数为n的链表
void createList(LinkList &L, int n, int reversed) {
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;

    if (reversed) {
        for (int i = 0; i < n; i++) {
            LinkList p = (LinkList)malloc(sizeof(LNode));
            scanf("%d", &p->data);
        
            p->next = L->next;
            L->next = p;
        }
    } else {
        LinkList p = L;
        for (int i = 0; i < n; i++) {
            LinkList q = (LinkList)malloc(sizeof(LNode));
            scanf("%d", &q->data);
            
            q->next = p->next;
            p->next = q;
            p = q;
        }
    }
}

void destroyList(LinkList &L) {
    
    while (L) {
        LinkList p = L->next;
    }
}

Status insertElem(LinkList &L, int i, ElemType e) {
    LinkList p = L;
    int j = 0;
    
    while (p && j<i-1) {
        p = p->next;
        j++;
    }

    if (!p || j>i-1)
        return ERROR;

    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

/* 删除元素时要确保第i个元素是存在的
 * 然后令一个指针变量指向其前驱
 * 不能单纯的去指向第i - 1个元素
 * 
 */
Status deleteElem(LinkList &L, int i, ElemType &e) {
    LinkList p = L;
    int j = 0;

    /* p->next一旦为假说明已到表尾 */
    /* 若被删除元素在正常范围[1, len]中, j == i */
    while (p->next && j<i-1) {
        p = p->next;
        j++;
    }

    if (!(p->next) || j>i-1)
        return ERROR;
    LinkList q = p->next;
    e = q->data;
    p->next = q->next;

    free(q);
    return OK;
}


int length(LinkList L) {
    int cnt = 0;
    LinkList p = L->next;

    while (p) {
        cnt++;
        p = p->next;
    }
    return cnt;
}


Status getElem(LinkList L, int i, ElemType &e) {
    LinkList p = L->next;
    int j = 1;
    
    while (p && j<i) {
        p = p->next;
        j++;
    }

    if (!p || j>i)
        return ERROR;

    e = p->data;
    return OK;
}

void printList(LinkList L) {
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main() {
    LinkList L;
    createList(L, 5, 0);
    int e;
    deleteElem(L, 6, e);
    printList(L);
    
}