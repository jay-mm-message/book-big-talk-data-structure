#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MAXSIZE 9     /* 存储空间初始分配量 */
#define MAXEDGE 15    /* 最大边数 */
#define MAXVEX 9      /* 最大顶点数 */

/* 状态类型定义 */
typedef int Status; 
typedef int Boolean; 

/* 顶点和边的类型定义 */
typedef char VertexType;   /* 顶点数据类型 */
typedef int EdgeType;      /* 边的权重类型 */

/* 邻接表结构定义 */
typedef struct EdgeNode 
{  
	int adjvex;            /* 邻接点的下标 */
	int weight;            /* 权重 (可选) */
	struct EdgeNode *next; /* 指向下一个邻接点的指针 */
} EdgeNode;

typedef struct VertexNode 
{  
	char data;            /* 顶点数据 */
	EdgeNode *firstedge;  /* 边表的头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct 
{	
	AdjList adjList;      /* 顶点列表 */
	int numVertexes;      /* 图中顶点的数量 */
	int numEdges;         /* 图中边的数量 */
} GraphAdjList, *Graph;

/* 队列结构定义（用于广度优先遍历） */
typedef struct 
{
	int data[MAXSIZE];
	int front;    /* 头指针 */
	int rear;     /* 尾指针 */
} Queue;

/* 队列操作函数 */
Status InitQueue(Queue *Q) 
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

Status QueueEmpty(Queue Q) 
{ 
	return Q.front == Q.rear ? TRUE : FALSE;
}

Status EnQueue(Queue *Q, int e) 
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)  /* 判断队列是否满 */
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

Status DeQueue(Queue *Q, int *e) 
{
	if (Q->front == Q->rear)  /* 判断队列是否空 */
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

/* 图的创建：使用邻接表表示 */
void CreateGraph(Graph *G) 
{
	int i, j, k;
	EdgeNode *e;
	
	/* 分配内存并初始化图 */
	*G = (Graph)malloc(sizeof(GraphAdjList));
	(*G)->numVertexes = 9;
	(*G)->numEdges = 15;
	
	/* 初始化顶点数据 */
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	for (i = 0; i < (*G)->numVertexes; i++) 
	{
		(*G)->adjList[i].data = vertices[i];
		(*G)->adjList[i].firstedge = NULL;  /* 初始化边表为空 */
	}
	
	/* 图的边：无向图，建立邻接表。15行2列的二维数组，每行表示一个边，每个边包含两个顶点的下标 */
	int edges[15][2] = 
	{
		{0, 1}, {0, 5}, {1, 2}, {1, 8}, {1, 6},
		{2, 3}, {2, 8}, {3, 4}, {3, 7}, {3, 6},
		{3, 8}, {4, 5}, {4, 7}, {5, 6}, {6, 7}
	};
	
	/* 遍历边数组，建立双向连接的边 */
	for (k = 0; k < (*G)->numEdges; k++) 
	{
		i = edges[k][0];
		j = edges[k][1];
		
		/* 从i到j的边 */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = (*G)->adjList[i].firstedge;
		(*G)->adjList[i].firstedge = e;
		
		/* 从j到i的边（因为是无向图） */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = (*G)->adjList[j].firstedge;
		(*G)->adjList[j].firstedge = e;
	}
}

/* 深度优先遍历 */
Boolean visited[MAXVEX];  /* 访问标志数组 */

void DFS(Graph G, int i) 
{
	EdgeNode *p;
	visited[i] = TRUE;  /* 标记当前顶点为已访问 */
	printf("%c ", G->adjList[i].data);  /* 打印顶点 */
	
	/* 遍历当前顶点的所有邻接点 */
	p = G->adjList[i].firstedge;
	while (p) 
	{
		if (!visited[p->adjvex]) 
		{
			DFS(G, p->adjvex);  /* 递归访问未访问的邻接点 */
		}
		p = p->next;  /* 遍历下一个邻接点 */
	}
}

void DFSTraverse(Graph G) {
	int i;
	for (i = 0; i < G->numVertexes; i++) 
	{
		visited[i] = FALSE;  /* 初始化所有顶点为未访问 */
	}
	for (i = 0; i < G->numVertexes; i++) 
	{
		if (!visited[i]) 
		{  /* 对未访问的顶点调用DFS */
			DFS(G, i);
		}
	}
}

/* 广度优先遍历 */
void BFSTraverse(Graph G) 
{
	int i;
	EdgeNode *p;
	Queue Q;
	
	for (i = 0; i < G->numVertexes; i++) 
	{
		visited[i] = FALSE;  /* 初始化所有顶点为未访问 */
	}
	
	InitQueue(&Q);  /* 初始化队列 */
	for (i = 0; i < G->numVertexes; i++) 
	{
		if (!visited[i]) 
		{  /* 对未访问的顶点执行广度优先遍历 */
			visited[i] = TRUE;
			printf("%c ", G->adjList[i].data);  /* 打印顶点 */
			EnQueue(&Q, i);  /* 将顶点入队 */
			while (!QueueEmpty(Q)) 
			{
				DeQueue(&Q, &i);  /* 出队列 */
				p = G->adjList[i].firstedge;
				while (p) 
				{
					if (!visited[p->adjvex]) 
					{  /* 访问未访问的邻接点 */
						visited[p->adjvex] = TRUE;
						printf("%c ", G->adjList[p->adjvex].data);
						EnQueue(&Q, p->adjvex);  /* 将邻接点入队 */
					}
					p = p->next;  /* 指向下一个邻接点 */
				}
			}
		}
	}
}

int main(void) {    
	Graph G;    
	CreateGraph(&G);  /* 创建图 */
	
	printf("\n深度优先遍历: ");
	DFSTraverse(G);  /* 深度优先遍历 */
	
	printf("\n广度优先遍历: ");
	BFSTraverse(G);  /* 广度优先遍历 */
	
	return 0;
}

