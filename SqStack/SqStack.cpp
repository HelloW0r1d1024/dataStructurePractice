#include<stdio.h>
#include<stdlib.h>


#define True 1
#define False 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define SElemType int

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;

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

Status isEmpty(SqStack S) {
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

void conversion(int num, int base) {
    SqStack S;
    initStack(S);

    while (num) {
        push(S, num%base);
        num /= base;
    }

    while (!isEmpty(S)) {
        int e;
        pop(S, e);
        printf("%d", e);
    }
}


int main() {
    
    conversion(1348, 8);
    return 0;
}