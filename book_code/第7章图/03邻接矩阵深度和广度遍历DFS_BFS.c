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

typedef int Status; /* Status �Ǻ�������ֵ�����ͣ����� OK, ERROR �� */
typedef int Boolean; /* Boolean �ǲ������ͣ���ֵΪ TRUE �� FALSE */

typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* �ߵ�Ȩ������Ӧ���û����� */

#define MAXSIZE 9 /* ���д洢�ĳ�ʼ�����С */
#define MAXEDGE 15 /* ͼ�������� */
#define MAXVEX 9 /* ͼ����󶥵��� */

typedef struct
{
	VertexType vertices[MAXVEX]; /* �����б� */
	EdgeType edges[MAXVEX][MAXVEX]; /* �ڽӾ��󣬿��Կ����߱� */
	int vertexCount, edgeCount; /* ͼ�е�ǰ�Ķ������ͱ��� */
} MGraph;

/* ѭ�����нṹ */
typedef struct
{
	int data[MAXSIZE];
	int front; /* ͷָ�� */
	int rear; /* βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� */
} Queue;

/* ��ʼ��һ���ն��� */
Status initQueue(Queue *queue)
{
	queue->front = 0;
	queue->rear = 0;
	return OK;
}

/* ������Ϊ�գ��򷵻� TRUE�����򷵻� FALSE */
Boolean isQueueEmpty(Queue queue)
{
	return queue.front == queue.rear;
}

/* ������δ���������Ԫ�� e ��Ϊ���е���βԪ�� */
Status enqueue(Queue *queue, int element)
{
	if ((queue->rear + 1) % MAXSIZE == queue->front) /* ��������� */
	{
		return ERROR;
	}
	queue->data[queue->rear] = element; /* ��Ԫ�� e ��ֵ����β */
	queue->rear = (queue->rear + 1) % MAXSIZE; /* rear ָ������ƶ����������ĩβ����� */
	return OK;
}

/* �����в�Ϊ�գ���ɾ����ͷԪ�ز�ͨ�� e ������ֵ */
Status dequeue(Queue *queue, int *element)
{
	if (queue->front == queue->rear) /* ���пռ�� */
	{
		return ERROR;
	}
	*element = queue->data[queue->front]; /* ����ͷԪ�ظ�ֵ�� e */
	queue->front = (queue->front + 1) % MAXSIZE; /* front ָ������ƶ����������ĩβ����� */
	return OK;
}

/* ����һ������ͼ */
void createGraph(MGraph *graph)
{
	graph->vertexCount = 9;
	graph->edgeCount = 15;
	
	/* ��ȡ������Ϣ�Խ��������б� */
	graph->vertices[0] = 'A';
	graph->vertices[1] = 'B';
	graph->vertices[2] = 'C';
	graph->vertices[3] = 'D';
	graph->vertices[4] = 'E';
	graph->vertices[5] = 'F';
	graph->vertices[6] = 'G';
	graph->vertices[7] = 'H';
	graph->vertices[8] = 'I';
	
	for (int i = 0; i < graph->vertexCount; i++) /* ��ʼ��ͼ */
	{
		for (int j = 0; j < graph->vertexCount; j++)
		{
			graph->edges[i][j] = 0; /* ����Ԫ�ؾ���Ϊ 0 */
		}
	}
	
	/* ���ñߣ����� */
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
			graph->edges[j][i] = graph->edges[i][j]; /* ����������ͼ��ȷ���Գ��� */
		}
	}
}

Boolean visited[MAXVEX]; /* ���ʱ�־���� */

/* ʹ���ڽӾ����ʾ������������� (DFS) */
void depthFirstSearch(MGraph graph, int index)
{
	visited[index] = TRUE;
	printf("%c ", graph.vertices[index]); /* ��ӡ���㣬Ҳ����ִ���������� */
	
	for (int j = 0; j < graph.vertexCount; j++) /* ����ڽӾ����� index �е�ÿ��Ԫ�� */
	{
		if (graph.edges[index][j] == 1 && !visited[j])
		{
			depthFirstSearch(graph, j); /* ��δ���ʵ��ڽӶ���ݹ���� DFS */
		}
	}
}

/* �ڽӾ����������ȱ��� */
void depthFirstTraversal(MGraph graph)
{
	for (int i = 0; i < graph.vertexCount; i++)
	{
		visited[i] = FALSE; /* ��ʼ�����ж���Ϊδ����״̬ */
	}
	printf("������ȱ���: ");
	for (int i = 0; i < graph.vertexCount; i++)
	{
		if (!visited[i]) /* ��δ���ʵĶ������ DFS�����ͼ����ͨ�ģ��� if ֻ��ִ��һ�� */
		{
			depthFirstSearch(graph, i);
		}
	}
	printf("\n");
}

/* ʹ���ڽӾ���Ĺ�����ȱ��� (BFS) */
void breadthFirstTraversal(MGraph graph)
{
	Queue queue;
	initQueue(&queue); /* ��ʼ��һ���������� */
	
	for (int i = 0; i < graph.vertexCount; i++)
	{
		visited[i] = FALSE; /* ��ʼ�����ж���Ϊδ����״̬ */
	}
	
	printf("������ȱ���: ");
	for (int i = 0; i < graph.vertexCount; i++) /* ����ÿ������ */
	{
		if (!visited[i]) /* �������δ������ */
		{
			visited[i] = TRUE; /* ��ǵ�ǰ����Ϊ�ѷ��� */
			printf("%c ", graph.vertices[i]); /* ��ӡ���㣬Ҳ����ִ���������� */
			enqueue(&queue, i); /* ���˶������ */
			
			while (!isQueueEmpty(queue)) /* �����в�Ϊ�� */
			{
				int currentIndex;
				dequeue(&queue, &currentIndex); /* ����һ��Ԫ�ز����� currentIndex */
				for (int j = 0; j < graph.vertexCount; j++)
				{
					/* ������ڱ��Ҷ���δ������ */
					if (graph.edges[currentIndex][j] == 1 && !visited[j])
					{
						visited[j] = TRUE; /* ����ҵ��Ķ���Ϊ�ѷ��� */
						printf("%c ", graph.vertices[j]); /* ��ӡ���� */
						enqueue(&queue, j); /* ���ҵ��Ķ������ */
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

