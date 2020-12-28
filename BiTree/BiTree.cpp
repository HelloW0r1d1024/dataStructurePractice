#include<stdio.h>
#include<stdlib.h>

#define True 1
#define False 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

// 二叉树及结点类型定义
#define TElemType char
typedef struct BiTNode {
    TElemType data;
    struct BiTNode * lchild;
    struct BiTNode * rchild;
} * BiTree;

//辅助结构 栈类型定义
#define SElemType BiTree
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct {
    SElemType * base;
    SElemType * top;
    int stackSize;
} SqStack;

// 辅助结构 队列类型定义
#define QElemType BiTree

typedef struct QNode{
    QElemType data;
    struct QNode * next;
} * QPtr;

typedef struct {
    QPtr front, rear;
} Quene;

Status initQuene(Quene &Q) {
    Q.front = Q.rear = (QPtr)malloc(sizeof(QNode));
    if (!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;

    return OK;
}

Status enQuene(Quene &Q, QElemType e) {
    QPtr p = (QPtr)malloc(sizeof(QNode));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status deQuene(Quene &Q, QElemType &e) {
    if (Q.rear == Q.front)
        return ERROR;
    QPtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);

    return OK;
}

/*
 * 初始化栈
 */
Status initStack(SqStack &S) {
    S.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    if (!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stackSize = STACK_INIT_SIZE;
    return OK;
}

/*
 * 判空操作
 */
Status stackEmpty(SqStack S) {
    return S.top == S.base;
}

/*
 * 压栈操作
 */
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

/*
 * 弹栈操作
 */
Status pop(SqStack &S, SElemType &e) {
    if (S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

/*
 * 获取栈顶元素
 */
Status getTop(SqStack S, SElemType &p) {
    p = *(S.top-1);
    return OK;
}

/*
 * 初始化二叉树
 */
Status initBiTree(BiTree &T) {
    T = NULL;
    return OK;
}

/*
 * 二叉树判空
 */
Status BiTEmpty(BiTree T) {
    return !T;
}

/*
 * 创建二叉树
 */
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

/*
 * 其实销毁二叉树的过程就是后序遍历二叉树的过程
 */
void destroyBiTree(BiTree &T) {
    if (T) {
        destroyBiTree(T->lchild);
        destroyBiTree(T->rchild);
        free(T);
    }
}


// 按层遍历
Status levelOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    Quene Q;
    initQuene(Q);
    enQuene(Q, T);
    BiTree p;

    while (Q.front != Q.rear) {
        deQuene(Q, p);
        (* visit)(p->data);
        if (p->lchild)
            enQuene(Q, p->lchild);
        if (p->rchild)
            enQuene(Q, p->rchild);  
    }

    return OK;
}

/*
 * 前序遍历(递归)
 */
Status preOrderTraverse(BiTree T, Status (* visit)(TElemType e)) {
    if (T) {
        (* visit)(T->data);
        preOrderTraverse(T->lchild, visit);
        preOrderTraverse(T->rchild, visit);
    } else return ERROR;

    return OK;
}

/*
 * 前序遍历(非递归)
 */
Status preOrderTraverse_RE(BiTree T, Status (* visit)(TElemType e)) {
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
}

/*
 * 中序遍历(非递归)
 */
Status inOrderTraverse_RE(BiTree T, Status (* visit)(TElemType e)) {
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
}

BiTree swapChild(BiTree &T) {
    BiTree T1, T2, S;

    if (T) {
        S = (BiTree)malloc(sizeof(BiTNode));
        S->data = T->data;
        T1 = swapChild(T->lchild);
        T2 = swapChild(T->rchild);

        S->lchild = T2;
        S->rchild = T1;
    }
    else
        S = NULL;

    return S;
}

/*
 * 一棵树所包含的结点数 = 左子树结点数 + 右子树结点数 + 1
 */
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

/*
 * 根结点的深度 = max(左子树深度, 右子树深度) + 1
 */
int depth(BiTree T) {
    if (T) {
        int l = depth(T->lchild);
        int r = depth(T->rchild);

        return l>r ? l+1 : r+1;
    }
    else
        return 0;   
}

Status kthNode(BiTree T, int k, int &cnt, BiTree &p) {
    
    if (T) {
        if (k == cnt) {
            p = T;
            return OK;
        }
        else {
            kthNode(T->lchild, k, cnt, p);
            kthNode(T->rchild, k, cnt, p);
        }
        
    }
    else 
        return ERROR;
}

Status printElem(char ch) {
    printf("%c", ch);

    return OK;
}


