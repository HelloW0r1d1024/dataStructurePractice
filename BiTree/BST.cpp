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
        printf("插入成功\n");
        return OK;
    }
    else
        return ERROR;
}

Status deleteNode(BST &p) {
    if (!p->rchild) {
        BST q = p;
        p = p->lchild;
        free(q);
    }
    else if (!p->lchild) {
        BST q = p;
        p = p->rchild;
    }
    else {
        BST q = p;
        BST s = p->lchild;
        while (s->rchild) {
            q = s;
            s = s->rchild;
        }

        p->data = s->data;
        deleteNode(s);
    }
    return OK;
}

Status deleteBST(BST &T, KeyType e) {
    if (!T) return ERROR;
    else {
        if (e == T->data)
            return deleteNode(T);
        else if (e > T->data)
            return deleteBST(T->rchild, e);
        else
            return deleteBST(T->lchild, e);
    }
}



Status preOrderTraverse(BST T) {
    if (T) {
        printf("%d ", T->data);
        preOrderTraverse(T->lchild);
        
        preOrderTraverse(T->rchild);
    } else return ERROR;

    return OK;
}

Status inOrderTraverse(BST T) {
    if (T) {
        inOrderTraverse(T->lchild);
        printf("%d ", T->data);
        inOrderTraverse(T->rchild);
    } else return ERROR;

    return OK;
}

int main() {
    // BiTree T;
    // createBiTree(T);
    // preOrderTraverse(T, printElem);
    // printf("\n");
    // levelOrderTraverse(T, printElem);
    // printf("\n结点数为:%d", nodeCnt(T));
    // printf("\n叶子数为:%d", leafCnt(T));
    // printf("\n深度为:%d\n", depth(T));
    //destroyBiTree(T);
    BST T = NULL, p;
    for (int i = 0; i < 10; i++) {
        int x;
        scanf("%d", &x);
        insertBST(T, x);
    }
    printf("\n");
    preOrderTraverse(T);
    printf("\n");
    inOrderTraverse(T);
    deleteBST(T, 24);
    printf("\n");
    inOrderTraverse(T);
}
//45 12 53 3 37 24 100 61 90 78