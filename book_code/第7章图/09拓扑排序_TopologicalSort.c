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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

/* �ڽӾ���ṹ */
typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/* �ڽӱ�ṹ****************** */
typedef struct EdgeNode /* �߱���  */
{
	int adjvex;    /* �ڽӵ��򣬴洢�ö����Ӧ���±� */
	int weight;		/* ���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VertexNode /* ������� */
{
	int in;	/* ������� */
	int data; /* �����򣬴洢������Ϣ */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numVertexes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}graphAdjList,*GraphAdjList;
/* **************************** */


void CreateMGraph(MGraph *G)/* ����ͼ */
{
	int i, j;
	
	G->numEdges = MAXEDGE;
	G->numVertexes = MAXVEX;
	
	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		G->vexs[i] = i;
	}
	
	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j] = 0;
		}
	}
	
	/* ����ڽӾ��� */
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

/* �����ڽӾ��󹹽��ڽӱ� */
void CreateALGraph(MGraph G, GraphAdjList *GL)
{
	int i, j;
	EdgeNode *e;
	
	// �����ڽӱ��ڴ�
	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));
	
	// ����ڴ�����Ƿ�ɹ�
	if (*GL == NULL) 
	{
		printf("Memory allocation failed for GraphAdjList!\n");
		return;
	}
	
	(*GL)->numVertexes = G.numVertexes;
	(*GL)->numEdges = G.numEdges;
	
	// ��ʼ������
	for (i = 0; i < G.numVertexes; i++) 
	{
		(*GL)->adjList[i].in = 0;
		(*GL)->adjList[i].data = G.vexs[i];
		(*GL)->adjList[i].firstedge = NULL; 	/* ���߱���Ϊ�� */
	}
	
	// �����߱�
	for (i = 0; i < G.numVertexes; i++) 
	{
		for (j = 0; j < G.numVertexes; j++) 
		{
			if (G.arc[i][j] == 1) 
			{
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				
				// ����ڴ�����Ƿ�ɹ�
				if (e == NULL) 
				{
					printf("Memory allocation failed for EdgeNode!\n");
					return;
				}
				
				e->adjvex = j;
				e->next = (*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge = e;
				(*GL)->adjList[j].in++;  // ����Ŀ�궥������
			}
		}
	}
}

/* ����������GL�޻�·������������������в�����1�����л�·����0�� */
Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, currentVertex;
	int top = -1;  /* ջ��ջָ���±� */
	int vertexCount = 0;  /* ����ͳ���������ĸ��� */
	int *stack;  /* ���ڴ�����Ϊ0�Ķ��� */
	
	// ����ջ�ڴ�
	stack = (int *)malloc(GL->numVertexes * sizeof(int));
	
	// ���ջ�ڴ��Ƿ����ɹ�
	if (stack == NULL) 
	{
		printf("Memory allocation failed for stack!\n");
		return ERROR;
	}
	
	// �����Ϊ0�Ķ�����ջ
	for (i = 0; i < GL->numVertexes; i++) 
	{
		if (GL->adjList[i].in == 0) 
		{
			stack[++top] = i;
		}
	}
	
	// ������������
	while (top != -1) 
	{
		currentVertex = stack[top--];
		printf("%d", GL->adjList[currentVertex].data);
		vertexCount++;
		
		// �����������
		if (vertexCount < GL->numVertexes) 
		{
			printf(" -> ");
		}
		
		// ������ǰ������ڽӱ�
		for (e = GL->adjList[currentVertex].firstedge; e; e = e->next) 
		{
			k = e->adjvex;
			if (--GL->adjList[k].in == 0) 
			{
				stack[++top] = k;  // �����ȼ�Ϊ0������ջ
			}
		}
	}
	
	// �ͷ�ջ�ڴ�
	free(stack);
	
	// �ж��Ƿ��л�·
	if (vertexCount < GL->numVertexes) 
	{
		return ERROR;  // ���ڻ�·
	} else 
	{
		return OK;  // �޻�·
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

