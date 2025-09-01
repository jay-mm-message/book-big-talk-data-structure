#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵�����Ӧ���û����� */
#define GRAPH_INFINITY 65535 /* ��65535������� */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char VertexType; /* ��������Ӧ���û�����  */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct 
{
	VertexType vexs[MAXVEX]; /* ����� */
	EdgeType arc[MAXVEX][MAXVEX]; /* �ڽӾ��󣬿ɿ����߱� */
	int numNodes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ��� */
} MGraph;

/* �������������ڽӾ����ʾ */
void CreateUDN(MGraph *G) 
{
	int i, j, k, w;
	printf("���붥�����ͱ���:\n");
	scanf("%d %d", &G->numNodes, &G->numEdges); /* ���붥�����ͱ��� */
	
	printf("���붥����Ϣ:\n");
	for (i = 0; i < G->numNodes; i++) 
	{
		printf("���� %d: ", i + 1);
		scanf(" %c", &G->vexs[i]); /* ���붥����Ϣ, ���������. �ո���Ϊ�˺���ǰ��Ļ��з���հ׷�����ȷ����ȷ��ȡ�ַ����롣*/
	}
	
	/* ��ʼ���ڽӾ��� */
	for (i = 0; i < G->numNodes; i++) 
	{
		for (j = 0; j < G->numNodes; j++) 
		{
			G->arc[i][j] = GRAPH_INFINITY;
		}
	}
	
	/* ����ߵ���Ϣ�������ڽӾ��� */
	for (k = 0; k < G->numEdges; k++) 
	{
		printf("�����(vi, vj)���±� i, j ��Ȩ w:\n");
		scanf("%d %d %d", &i, &j, &w); /* ����� (vi, vj) ��Ȩ�� */
		G->arc[i][j] = w;
		G->arc[j][i] = w; /* ��Ϊ������ͼ������Գ� */
	}
}

/* ��ӡ�ڽӾ��� */
void PrintGraph(MGraph *G) 
{
	printf("\n�ڽӾ���:\n");
	for (int i = 0; i < G->numNodes; i++) 
	{
		for (int j = 0; j < G->numNodes; j++) 
		{
			if (G->arc[i][j] == GRAPH_INFINITY)
				printf("%4s", "��");
			else
				printf("%4d", G->arc[i][j]);
		}
		printf("\n");
	}
}

int main(void) 
{    
	MGraph G;    
	CreateUDN(&G);    
	PrintGraph(&G); /* ��ӡ�ڽӾ��� */
	return 0;
}
