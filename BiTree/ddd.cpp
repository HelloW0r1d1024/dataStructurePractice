#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define KeyType int
typedef struct BSTNode {
    KeyType data;
    struct BSTNode * lchild;
    struct BSTNode * rchild;
} * BST;

Status searchBST(BST T, KeyType e, BST f, BST &p) {
    if (!T) {
        p = f;
        return ERROR;
    }
    else if (e == T->data) {
        p = T;
        return OK;
    }
    else if (e > T->data){
        return searchBST(T->rchild, e, T, p);
    }
    else {
        return searchBST(T->lchild, e, T, p);
    }
}

Status insertBST(BST &T, KeyType e) {
    BST p;
    if (!searchBST(T, e, NULL, p)) {
        BST s = (BST)malloc(sizeof(BSTNode));
        s->data = e;
        s->lchild = NULL;
        s->rchild = NULL;

        if (!p)
            T = s;
        else if (e > p->data)
            p->rchild = s;
        else
            p->lchild = s;
        return OK;
    }
    else
        return ERROR;
}

int main() {
    BST T = NULL, p;
    for (int i = 0; i < 10; i++) {
        int x;
        scanf("%d", &x);
        insertBST(T, x);
    }

    for (int i = 0; i < 2; i++) {
        int x;
        scanf("%d", &x);
        if (searchBST(T, x, NULL, p))
            printf("查找成功,该结点位于%p,值为:%d\n", p, p->data);
        else
            printf("查找失败\n");
    } 
} // 测试用例