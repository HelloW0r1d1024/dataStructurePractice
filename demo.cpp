#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define TElemType char
typedef struct BiTNode {
    TElemType data;
    struct BiTNode * lchild, * rchild;
} * BiTree;

Status printElem(TElemType e) {
    printf("%c", e);
    return OK;
}

Status initBiTree(BiTree &T) {
    T = NULL;
    return OK;
}

Status createBiTree(BiTree &T) {
    char ch;
    ch = getchar();

    if (' ' == ch)
        T = NULL;
    else {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = ch;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }

    return OK;
}

Status preOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    if (T) {
        if ((* visit)(T->data))
            if (preOrderTraverse(T->lchild, visit))
                if (preOrderTraverse(T->rchild, visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

int nodeCnt(BiTree T) {
    if (!T)
        return 0;
    else 
        return nodeCnt(T->lchild) + nodeCnt(T->rchild) + 1;
}

int leafCnt(BiTree T) {
    if (!T)
        return 0;
    else if (!(T->lchild || T->rchild))
        return 1;
    else 
        return leafCnt(T->lchild) + leafCnt(T->rchild);
}

int depth(BiTree T) {
    if (!T)
        return 0;
    else {
        int l = depth(T->lchild);
        int r = depth(T->rchild);

        return l > r ? l+1 : r+1;
    }
}

int main() {
    BiTree T;
    initBiTree(T);
    createBiTree(T);
    preOrderTraverse(T, printElem);
    printf("\n结点数:%d, 叶子数:%d, 深度为:%d", nodeCnt(T), leafCnt(T), depth(T));
}