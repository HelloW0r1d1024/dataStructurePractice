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
    struct BiTNode * lchild;
    struct BiTNode * rchild;
} * BiTree;

#define SElemType BiTree
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct {
    SElemType * base;
    SElemType * top;
    int stackSize;
} SqStack;

Status initStack(SqStack &S) {
    S.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stackSize = STACK_INIT_SIZE;
    return OK;
}

Status stackEmpty(SqStack S) {
    return S.top == S.base;
}

Status push(SqStack &S, SElemType e) {
    if (S.top-S.base >= S.stackSize) {
        SElemType * newBase = (SElemType *)realloc(S.base, sizeof(SElemType) * (S.stackSize + STACKINCREMENT));
        if (!newBase) exit(OVERFLOW);
        S.base = newBase;
        S.top = S.base + S.stackSize;
        S.stackSize += STACKINCREMENT;
    }
    *(S.top++) = e;
    return OK;
}

Status pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

Status getTop(SqStack S, SElemType &p) {
    p = *(S.top-1);
    return OK;
}

Status createBiTree(BiTree &T) {
    char ch;
    ch = getchar();

    if (' ' == ch) {
        T = NULL;
    }
    else {
        if (!(T=(BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);

        T->data = ch;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }

    return OK;
}

int leafCnt(BiTree T) {
    if (!T)
        return 0;
    else if (!(T->lchild || T->rchild))
        return 1;
    else
        return leafCnt(T->lchild) + leafCnt(T->rchild);
} // 题目一

int cnt = 0;
void kthNode(BiTree T, int k, BiTree &p) {

    if (!T) return;
    cnt++;
    if (cnt == k) {
        p = T;
        return;
    }
    kthNode(T->lchild, k, p);
    kthNode(T->rchild, k, p);
} // 题目二

Status preOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    SqStack S;
    initStack(S);
    BiTree p;
    push(S, T);

    while (!stackEmpty(S)) {
        while (getTop(S, p) && p) {
            (* visit)(p->data);
            push(S, p->lchild);
        }

        pop(S, p);
        if (!stackEmpty(S)) {
            pop(S, p);
            push(S, p->rchild);
        }
    }
    return OK;
} // 题目三

Status inOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    SqStack S;
    initStack(S);
    BiTree p;
    push(S, T);

    while (!stackEmpty(S)) {
        while (getTop(S, p) && p) push(S, p->lchild);
        pop(S, p);

        if (!stackEmpty(S)) {
            pop(S, p);
            (* visit)(p->data);
            push(S, p->rchild);
        }
    }
    return OK;
} // 题目三

Status postOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    SqStack S;
    initStack(S);
    BiTree p;
    push(S, T);
    BiTree pre = NULL;

    while (!stackEmpty(S)) {
        while (getTop(S, p) && p) push(S, p->lchild);
        pop(S, p);

        if (!stackEmpty(S)){
            getTop(S, p);
            if (p->rchild && p->rchild!=pre) {
                p = p->rchild;
                push(S, p);
            }
            else {
                pop(S, p);
                (*visit)(p->data);
                pre = p;
                push(S, NULL);
            }
        }
    }

    return OK;
} // 题目三

Status printElem(TElemType e) {
    printf("%c", e);
    return OK;
}

int main() {
    BiTree T = NULL;
    BiTree p = NULL;
    createBiTree(T);
    kthNode(T, 3, p);

    printf("\n叶子数:%d", leafCnt(T));
    printf("\n先序遍历序列中第三个元素为:%c", p->data);
    printf("\n先序遍历序列:");
    preOrderTraverse(T, printElem);
    printf("\n中序遍历序列:");
    inOrderTraverse(T, printElem);
    printf("\n后序遍历序列:");
    postOrderTraverse(T, printElem);
    
    return 0;
}