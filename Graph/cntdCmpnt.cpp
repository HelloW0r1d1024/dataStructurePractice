#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM

typedef char vertexType;

typedef struct arcNode {
    int adjvex;
    struct arcNode * next;
} arcNode;

typedef struct vertexNode {
    vertexType data;
    arcNode * firstArc;
}vertexNode;

typedef struct {
    vertexNode a[MAX_VERTEX_NUM];
    int vertexNum, arcNum;
}graphAdjList;

void createALGraph(graphAdjList &G) {
    printf("输入顶点数和边数:\n");
    scanf("%d %d", G.vertexNum, G.arcNum);

    for (int i = 0; i < G.vertexNum; i++) {
        printf("请输入以v%d为弧尾的所有弧，并以-1结束输入", i);
        G.a->data = 'v1';
        int x;
        scanf("%d", &x);

        arcNode * L = G.a[0].firstArc;
            L = (arcNode *)malloc(sizeof(arcNode));
            L->next = NULL;
            arcNode * p = L;
        while (x != -1) {
            scanf("%d", &x);
            

            
        }
    }
}