#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MAXSIZE 9     /* �洢�ռ��ʼ������ */
#define MAXEDGE 15    /* ������ */
#define MAXVEX 9      /* ��󶥵��� */

/* ״̬���Ͷ��� */
typedef int Status; 
typedef int Boolean; 

/* ����ͱߵ����Ͷ��� */
typedef char VertexType;   /* ������������ */
typedef int EdgeType;      /* �ߵ�Ȩ������ */

/* �ڽӱ�ṹ���� */
typedef struct EdgeNode 
{  
	int adjvex;            /* �ڽӵ���±� */
	int weight;            /* Ȩ�� (��ѡ) */
	struct EdgeNode *next; /* ָ����һ���ڽӵ��ָ�� */
} EdgeNode;

typedef struct VertexNode 
{  
	char data;            /* �������� */
	EdgeNode *firstedge;  /* �߱��ͷָ�� */
} VertexNode, AdjList[MAXVEX];

typedef struct 
{	
	AdjList adjList;      /* �����б� */
	int numVertexes;      /* ͼ�ж�������� */
	int numEdges;         /* ͼ�бߵ����� */
} GraphAdjList, *Graph;

/* ���нṹ���壨���ڹ�����ȱ����� */
typedef struct 
{
	int data[MAXSIZE];
	int front;    /* ͷָ�� */
	int rear;     /* βָ�� */
} Queue;

/* ���в������� */
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
	if ((Q->rear + 1) % MAXSIZE == Q->front)  /* �ж϶����Ƿ��� */
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

Status DeQueue(Queue *Q, int *e) 
{
	if (Q->front == Q->rear)  /* �ж϶����Ƿ�� */
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

/* ͼ�Ĵ�����ʹ���ڽӱ��ʾ */
void CreateGraph(Graph *G) 
{
	int i, j, k;
	EdgeNode *e;
	
	/* �����ڴ沢��ʼ��ͼ */
	*G = (Graph)malloc(sizeof(GraphAdjList));
	(*G)->numVertexes = 9;
	(*G)->numEdges = 15;
	
	/* ��ʼ���������� */
	char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	for (i = 0; i < (*G)->numVertexes; i++) 
	{
		(*G)->adjList[i].data = vertices[i];
		(*G)->adjList[i].firstedge = NULL;  /* ��ʼ���߱�Ϊ�� */
	}
	
	/* ͼ�ıߣ�����ͼ�������ڽӱ�15��2�еĶ�ά���飬ÿ�б�ʾһ���ߣ�ÿ���߰�������������±� */
	int edges[15][2] = 
	{
		{0, 1}, {0, 5}, {1, 2}, {1, 8}, {1, 6},
		{2, 3}, {2, 8}, {3, 4}, {3, 7}, {3, 6},
		{3, 8}, {4, 5}, {4, 7}, {5, 6}, {6, 7}
	};
	
	/* ���������飬����˫�����ӵı� */
	for (k = 0; k < (*G)->numEdges; k++) 
	{
		i = edges[k][0];
		j = edges[k][1];
		
		/* ��i��j�ı� */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = (*G)->adjList[i].firstedge;
		(*G)->adjList[i].firstedge = e;
		
		/* ��j��i�ıߣ���Ϊ������ͼ�� */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = (*G)->adjList[j].firstedge;
		(*G)->adjList[j].firstedge = e;
	}
}

/* ������ȱ��� */
Boolean visited[MAXVEX];  /* ���ʱ�־���� */

void DFS(Graph G, int i) 
{
	EdgeNode *p;
	visited[i] = TRUE;  /* ��ǵ�ǰ����Ϊ�ѷ��� */
	printf("%c ", G->adjList[i].data);  /* ��ӡ���� */
	
	/* ������ǰ����������ڽӵ� */
	p = G->adjList[i].firstedge;
	while (p) 
	{
		if (!visited[p->adjvex]) 
		{
			DFS(G, p->adjvex);  /* �ݹ����δ���ʵ��ڽӵ� */
		}
		p = p->next;  /* ������һ���ڽӵ� */
	}
}

void DFSTraverse(Graph G) {
	int i;
	for (i = 0; i < G->numVertexes; i++) 
	{
		visited[i] = FALSE;  /* ��ʼ�����ж���Ϊδ���� */
	}
	for (i = 0; i < G->numVertexes; i++) 
	{
		if (!visited[i]) 
		{  /* ��δ���ʵĶ������DFS */
			DFS(G, i);
		}
	}
}

/* ������ȱ��� */
void BFSTraverse(Graph G) 
{
	int i;
	EdgeNode *p;
	Queue Q;
	
	for (i = 0; i < G->numVertexes; i++) 
	{
		visited[i] = FALSE;  /* ��ʼ�����ж���Ϊδ���� */
	}
	
	InitQueue(&Q);  /* ��ʼ������ */
	for (i = 0; i < G->numVertexes; i++) 
	{
		if (!visited[i]) 
		{  /* ��δ���ʵĶ���ִ�й�����ȱ��� */
			visited[i] = TRUE;
			printf("%c ", G->adjList[i].data);  /* ��ӡ���� */
			EnQueue(&Q, i);  /* ��������� */
			while (!QueueEmpty(Q)) 
			{
				DeQueue(&Q, &i);  /* ������ */
				p = G->adjList[i].firstedge;
				while (p) 
				{
					if (!visited[p->adjvex]) 
					{  /* ����δ���ʵ��ڽӵ� */
						visited[p->adjvex] = TRUE;
						printf("%c ", G->adjList[p->adjvex].data);
						EnQueue(&Q, p->adjvex);  /* ���ڽӵ���� */
					}
					p = p->next;  /* ָ����һ���ڽӵ� */
				}
			}
		}
	}
}

int main(void) {    
	Graph G;    
	CreateGraph(&G);  /* ����ͼ */
	
	printf("\n������ȱ���: ");
	DFSTraverse(G);  /* ������ȱ��� */
	
	printf("\n������ȱ���: ");
	BFSTraverse(G);  /* ������ȱ��� */
	
	return 0;
}

