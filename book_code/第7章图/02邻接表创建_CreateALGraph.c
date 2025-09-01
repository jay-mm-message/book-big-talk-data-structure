#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  

#define MAXVEX 100 /* 最大顶点数，应由用户定义 */

typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct EdgeNode /* 边表结点 */
{
	int adjvex;    /* 邻接点域, 存储该顶点对应的下标 */
	EdgeType info; /* 用于存储权值 */
	struct EdgeNode *next; /* 链域, 指向下一个邻接点 */
} EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	VertexType data; /* 顶点域, 存储顶点信息 */
	EdgeNode *firstedge; /* 边表头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numNodes, numEdges; /* 图中当前顶点数和边数 */
} GraphAdjList;

/* 建立无向图的邻接表结构 */
void CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d %d", &G->numNodes, &G->numEdges);
	
	printf("输入顶点信息:\n");
	for (i = 0; i < G->numNodes; i++) 
	{
		printf("顶点 %d: ", i + 1);
		scanf(" %c", &G->adjList[i].data); /* 读取顶点信息，注意前面的空格是为了忽略换行符或空白符。 */
		G->adjList[i].firstedge = NULL; /* 初始化边表 */
	}
	
	for (k = 0; k < G->numEdges; k++) 
	{
		printf("输入边(vi, vj)的顶点序号:\n");
		scanf("%d %d", &i, &j);
		
		/* 插入边 (i, j) */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (e == NULL) 
		{
			printf("内存分配失败！\n");
			exit(1);
		}
		e->adjvex = j;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;
		
		/* 插入边 (j, i)，因为是无向图 */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (e == NULL) 
		{
			printf("内存分配失败！\n");
			exit(1);
		}
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

/* 打印无向图的邻接表 */
void PrintGraph(GraphAdjList *G)
{
	EdgeNode *e;
	printf("\n邻接表:\n");
	for (int i = 0; i < G->numNodes; i++) 
	{
		printf("%c ->", G->adjList[i].data);
		e = G->adjList[i].firstedge;
		while (e) 
		{
			printf(" %d ->", e->adjvex);
			e = e->next;
		}
		printf(" NULL\n");
	}
}

int main(void)
{    
	GraphAdjList G;    
	CreateALGraph(&G);
	PrintGraph(&G);
	return 0;
}

