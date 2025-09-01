#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#undef INFINITY
#define INFINITY 99999

typedef int Status; /* Status 是函数返回值的类型，例如 OK, ERROR 等 */
typedef int Boolean; /* Boolean 是布尔类型，其值为 TRUE 或 FALSE */

typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边的权重类型应由用户定义 */

#define MAXSIZE 9 /* 队列存储的初始分配大小 */
#define MAXEDGE 15 /* 图的最大边数 */
#define MAXVEX 9 /* 图的最大顶点数 */

typedef struct
{
	VertexType vertices[MAXVEX]; /* 顶点列表 */
	EdgeType edges[MAXVEX][MAXVEX]; /* 邻接矩阵，可以看作边表 */
	int vertexCount, edgeCount; /* 图中当前的顶点数和边数 */
} MGraph;

/* 循环队列结构 */
typedef struct
{
	int data[MAXSIZE];
	int front; /* 头指针 */
	int rear; /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
} Queue;

/* 初始化一个空队列 */
Status initQueue(Queue *queue)
{
	queue->front = 0;
	queue->rear = 0;
	return OK;
}

/* 若队列为空，则返回 TRUE，否则返回 FALSE */
Boolean isQueueEmpty(Queue queue)
{
	return queue.front == queue.rear;
}

/* 若队列未满，则插入元素 e 作为队列的新尾元素 */
Status enqueue(Queue *queue, int element)
{
	if ((queue->rear + 1) % MAXSIZE == queue->front) /* 队列满检查 */
	{
		return ERROR;
	}
	queue->data[queue->rear] = element; /* 将元素 e 赋值给队尾 */
	queue->rear = (queue->rear + 1) % MAXSIZE; /* rear 指针向后移动，如果到达末尾则回绕 */
	return OK;
}

/* 若队列不为空，则删除队头元素并通过 e 返回其值 */
Status dequeue(Queue *queue, int *element)
{
	if (queue->front == queue->rear) /* 队列空检查 */
	{
		return ERROR;
	}
	*element = queue->data[queue->front]; /* 将队头元素赋值给 e */
	queue->front = (queue->front + 1) % MAXSIZE; /* front 指针向后移动，如果到达末尾则回绕 */
	return OK;
}

/* 创建一个无向图 */
void createGraph(MGraph *graph)
{
	graph->vertexCount = 9;
	graph->edgeCount = 15;
	
	/* 读取顶点信息以建立顶点列表 */
	graph->vertices[0] = 'A';
	graph->vertices[1] = 'B';
	graph->vertices[2] = 'C';
	graph->vertices[3] = 'D';
	graph->vertices[4] = 'E';
	graph->vertices[5] = 'F';
	graph->vertices[6] = 'G';
	graph->vertices[7] = 'H';
	graph->vertices[8] = 'I';
	
	for (int i = 0; i < graph->vertexCount; i++) /* 初始化图 */
	{
		for (int j = 0; j < graph->vertexCount; j++)
		{
			graph->edges[i][j] = 0; /* 所有元素均设为 0 */
		}
	}
	
	/* 设置边（无向） */
	graph->edges[0][1] = 1;
	graph->edges[0][5] = 1;
	graph->edges[1][2] = 1;
	graph->edges[1][6] = 1;
	graph->edges[1][8] = 1;
	graph->edges[2][3] = 1;
	graph->edges[2][8] = 1;
	graph->edges[3][4] = 1;
	graph->edges[3][7] = 1;
	graph->edges[3][6] = 1;
	graph->edges[3][8] = 1;
	graph->edges[4][5] = 1;
	graph->edges[4][7] = 1;
	graph->edges[5][6] = 1;
	graph->edges[6][7] = 1;
	
	for (int i = 0; i < graph->vertexCount; i++)
	{
		for (int j = i; j < graph->vertexCount; j++)
		{
			graph->edges[j][i] = graph->edges[i][j]; /* 由于是无向图，确保对称性 */
		}
	}
}

Boolean visited[MAXVEX]; /* 访问标志数组 */

/* 使用邻接矩阵表示的深度优先搜索 (DFS) */
void depthFirstSearch(MGraph graph, int index)
{
	visited[index] = TRUE;
	printf("%c ", graph.vertices[index]); /* 打印顶点，也可以执行其他操作 */
	
	for (int j = 0; j < graph.vertexCount; j++) /* 检查邻接矩阵中 index 行的每个元素 */
	{
		if (graph.edges[index][j] == 1 && !visited[j])
		{
			depthFirstSearch(graph, j); /* 对未访问的邻接顶点递归调用 DFS */
		}
	}
}

/* 邻接矩阵的深度优先遍历 */
void depthFirstTraversal(MGraph graph)
{
	for (int i = 0; i < graph.vertexCount; i++)
	{
		visited[i] = FALSE; /* 初始化所有顶点为未访问状态 */
	}
	printf("深度优先遍历: ");
	for (int i = 0; i < graph.vertexCount; i++)
	{
		if (!visited[i]) /* 对未访问的顶点调用 DFS，如果图是连通的，此 if 只会执行一次 */
		{
			depthFirstSearch(graph, i);
		}
	}
	printf("\n");
}

/* 使用邻接矩阵的广度优先遍历 (BFS) */
void breadthFirstTraversal(MGraph graph)
{
	Queue queue;
	initQueue(&queue); /* 初始化一个辅助队列 */
	
	for (int i = 0; i < graph.vertexCount; i++)
	{
		visited[i] = FALSE; /* 初始化所有顶点为未访问状态 */
	}
	
	printf("广度优先遍历: ");
	for (int i = 0; i < graph.vertexCount; i++) /* 遍历每个顶点 */
	{
		if (!visited[i]) /* 如果顶点未被访问 */
		{
			visited[i] = TRUE; /* 标记当前顶点为已访问 */
			printf("%c ", graph.vertices[i]); /* 打印顶点，也可以执行其他操作 */
			enqueue(&queue, i); /* 将此顶点入队 */
			
			while (!isQueueEmpty(queue)) /* 当队列不为空 */
			{
				int currentIndex;
				dequeue(&queue, &currentIndex); /* 出队一个元素并赋给 currentIndex */
				for (int j = 0; j < graph.vertexCount; j++)
				{
					/* 如果存在边且顶点未被访问 */
					if (graph.edges[currentIndex][j] == 1 && !visited[j])
					{
						visited[j] = TRUE; /* 标记找到的顶点为已访问 */
						printf("%c ", graph.vertices[j]); /* 打印顶点 */
						enqueue(&queue, j); /* 将找到的顶点入队 */
					}
				}
			}
		}
	}
	printf("\n");
}

int main(void)
{
	MGraph graph;
	createGraph(&graph);
	depthFirstTraversal(graph);
	breadthFirstTraversal(graph);
	return 0;
}

