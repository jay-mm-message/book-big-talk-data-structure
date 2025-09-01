#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 14

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/* 邻接矩阵结构 */
typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/* 邻接表结构****************** */
typedef struct EdgeNode /* 边表结点  */
{
	int adjvex;    /* 邻接点域，存储该顶点对应的下标 */
	int weight;		/* 用于存储权值，对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域，指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	int in;	/* 顶点入度 */
	int data; /* 顶点域，存储顶点信息 */
	EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numVertexes,numEdges; /* 图中当前顶点数和边数 */
}graphAdjList,*GraphAdjList;
/* **************************** */


void CreateMGraph(MGraph *G)/* 构件图 */
{
	int i, j;
	
	G->numEdges = MAXEDGE;
	G->numVertexes = MAXVEX;
	
	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		G->vexs[i] = i;
	}
	
	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j] = 0;
		}
	}
	
	/* 填充邻接矩阵 */
	G->arc[0][4] = 1;
	G->arc[0][5] = 1; 
	G->arc[0][11] = 1; 
	G->arc[1][2] = 1; 
	G->arc[1][4] = 1; 
	G->arc[1][8] = 1; 
	G->arc[2][5] = 1; 
	G->arc[2][6] = 1;
	G->arc[2][9] = 1;
	G->arc[3][2] = 1; 
	G->arc[3][13] = 1;
	G->arc[4][7] = 1;
	G->arc[5][8] = 1;
	G->arc[5][12] = 1; 
	G->arc[6][5] = 1; 
	G->arc[8][7] = 1;
	G->arc[9][10] = 1;
	G->arc[9][11] = 1;
	G->arc[10][13] = 1;
	G->arc[12][9] = 1;
}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph G, GraphAdjList *GL)
{
	int i, j;
	EdgeNode *e;
	
	// 分配邻接表内存
	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));
	
	// 检查内存分配是否成功
	if (*GL == NULL) 
	{
		printf("Memory allocation failed for GraphAdjList!\n");
		return;
	}
	
	(*GL)->numVertexes = G.numVertexes;
	(*GL)->numEdges = G.numEdges;
	
	// 初始化顶点
	for (i = 0; i < G.numVertexes; i++) 
	{
		(*GL)->adjList[i].in = 0;
		(*GL)->adjList[i].data = G.vexs[i];
		(*GL)->adjList[i].firstedge = NULL; 	/* 将边表置为空 */
	}
	
	// 建立边表
	for (i = 0; i < G.numVertexes; i++) 
	{
		for (j = 0; j < G.numVertexes; j++) 
		{
			if (G.arc[i][j] == 1) 
			{
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				
				// 检查内存分配是否成功
				if (e == NULL) 
				{
					printf("Memory allocation failed for EdgeNode!\n");
					return;
				}
				
				e->adjvex = j;
				e->next = (*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge = e;
				(*GL)->adjList[j].in++;  // 增加目标顶点的入度
			}
		}
	}
}

/* 拓扑排序，若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0。 */
Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, currentVertex;
	int top = -1;  /* 栈的栈指针下标 */
	int vertexCount = 0;  /* 用于统计输出顶点的个数 */
	int *stack;  /* 用于存放入度为0的顶点 */
	
	// 分配栈内存
	stack = (int *)malloc(GL->numVertexes * sizeof(int));
	
	// 检查栈内存是否分配成功
	if (stack == NULL) 
	{
		printf("Memory allocation failed for stack!\n");
		return ERROR;
	}
	
	// 将入度为0的顶点入栈
	for (i = 0; i < GL->numVertexes; i++) 
	{
		if (GL->adjList[i].in == 0) 
		{
			stack[++top] = i;
		}
	}
	
	// 进行拓扑排序
	while (top != -1) 
	{
		currentVertex = stack[top--];
		printf("%d", GL->adjList[currentVertex].data);
		vertexCount++;
		
		// 输出拓扑序列
		if (vertexCount < GL->numVertexes) 
		{
			printf(" -> ");
		}
		
		// 遍历当前顶点的邻接边
		for (e = GL->adjList[currentVertex].firstedge; e; e = e->next) 
		{
			k = e->adjvex;
			if (--GL->adjList[k].in == 0) 
			{
				stack[++top] = k;  // 如果入度减为0，则入栈
			}
		}
	}
	
	// 释放栈内存
	free(stack);
	
	// 判断是否有回路
	if (vertexCount < GL->numVertexes) 
	{
		return ERROR;  // 存在回路
	} else 
	{
		return OK;  // 无回路
	}
}

int main(void)
{
	MGraph G;
	GraphAdjList GL;
	int result;
	
	CreateMGraph(&G);
	CreateALGraph(G, &GL);
	result = TopologicalSort(GL);
	printf("\nresult: %d\n", result);
	
	return 0;
}

