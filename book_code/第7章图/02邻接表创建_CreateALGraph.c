#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  

#define MAXVEX 100 /* ��󶥵�����Ӧ���û����� */

typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct EdgeNode /* �߱��� */
{
	int adjvex;    /* �ڽӵ���, �洢�ö����Ӧ���±� */
	EdgeType info; /* ���ڴ洢Ȩֵ */
	struct EdgeNode *next; /* ����, ָ����һ���ڽӵ� */
} EdgeNode;

typedef struct VertexNode /* ������� */
{
	VertexType data; /* ������, �洢������Ϣ */
	EdgeNode *firstedge; /* �߱�ͷָ�� */
} VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numNodes, numEdges; /* ͼ�е�ǰ�������ͱ��� */
} GraphAdjList;

/* ��������ͼ���ڽӱ�ṹ */
void CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	EdgeNode *e;
	printf("���붥�����ͱ���:\n");
	scanf("%d %d", &G->numNodes, &G->numEdges);
	
	printf("���붥����Ϣ:\n");
	for (i = 0; i < G->numNodes; i++) 
	{
		printf("���� %d: ", i + 1);
		scanf(" %c", &G->adjList[i].data); /* ��ȡ������Ϣ��ע��ǰ��Ŀո���Ϊ�˺��Ի��з���հ׷��� */
		G->adjList[i].firstedge = NULL; /* ��ʼ���߱� */
	}
	
	for (k = 0; k < G->numEdges; k++) 
	{
		printf("�����(vi, vj)�Ķ������:\n");
		scanf("%d %d", &i, &j);
		
		/* ����� (i, j) */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (e == NULL) 
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(1);
		}
		e->adjvex = j;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;
		
		/* ����� (j, i)����Ϊ������ͼ */
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (e == NULL) 
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(1);
		}
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

/* ��ӡ����ͼ���ڽӱ� */
void PrintGraph(GraphAdjList *G)
{
	EdgeNode *e;
	printf("\n�ڽӱ�:\n");
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

