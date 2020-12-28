#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 100

typedef char VertexType;

typedef int arcType;
typedef int Boolean;
Boolean visited[MAXVEX];

typedef struct arcNode {
    int adjvex;
    struct arcNode * next;
} arcNode;

typedef struct vertexNode {
    VertexType data;
    arcNode * firstedge;
}vertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
}GraphAdjList;

void CreateALGraph(GraphAdjList *G) {
    int i, j, k;
    arcNode * e;
    printf("输入顶点数和边数:\n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges);
    for (i = 0; i < G->numVertexes; i++) {
        G->adjList[i].firstedge=NULL;
    }

    for (k = 0; k < G->numEdges; k++) {
        printf("输入边(vi, vj)上的顶点序号:\n");
        scanf("%d, %d", &i, &j);
        e = (arcNode *)malloc(sizeof(arcNode));
        e->adjvex = j;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;

        e = (arcNode *)malloc(sizeof(arcNode));

        e->adjvex = i;
        e->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e;
    }
}

void DFS(GraphAdjList GL, int i) {
    arcNode * p;
    visited[i] = true;
    
    p = GL.adjList[i].firstedge;

    while (p) {
        if (!visited[p->adjvex])
            DFS(GL, p->adjvex);
        p = p->next;
    }
}

int DFSTraverse(GraphAdjList GL) {
    int cnt = 0;
    int i;
    for (i = 0; i < GL.numVertexes; i++)
        visited[i] = false;
    for (i = 0; i < GL.numVertexes; i++)
        if (!visited[i]) {
            DFS(GL, i);
            cnt++;
        }

    return cnt;
}

int main() {
    GraphAdjList GL;
    CreateALGraph(&GL);
    printf("连通分量有%d个", DFSTraverse(GL));
} // 测试用例