#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

#define MAX_EDGE_NUM 20	 	 /* ������ */
#define MAX_VERTEX_NUM 20	 /* ��󶥵��� */
#define GRAPH_INFINITY 65535

typedef struct 
{
	int from, to; 		/*�ߵ������˵�*/ 
	int weight;   		/*�ߵ�Ȩֵ*/
} EdgeType;

typedef struct 
{
	int vertex[MAX_VERTEX_NUM];		/*���ͼ���������*/
	EdgeType edge[MAX_EDGE_NUM];	/*�߼�����*/
	int vertexNum, edgeNum; 		/*ͼ�Ķ������ͱ���*/
} EdgeGraph;

/* ����ͼ */
void CreateGraph(EdgeGraph *G) 
{
	G->vertexNum = 9;
	G->edgeNum = 15;
	
	/* ��ʼ���������� */
	for (int i = 0; i < G->vertexNum; i++) 
	{
		G->vertex[i] = i;
	}
	
	/* �ṹ�������� */
	G->edge[0] = (EdgeType){0, 1, 10};
	G->edge[1] = (EdgeType){0, 5, 11};
	G->edge[2] = (EdgeType){1, 2, 18};
	G->edge[3] = (EdgeType){1, 8, 12};
	G->edge[4] = (EdgeType){1, 6, 16};
	G->edge[5] = (EdgeType){2, 8, 8};
	G->edge[6] = (EdgeType){2, 3, 22};
	G->edge[7] = (EdgeType){3, 8, 21};
	G->edge[8] = (EdgeType){3, 6, 24};
	G->edge[9] = (EdgeType){3, 7, 16};
	G->edge[10] = (EdgeType){3, 4, 20};
	G->edge[11] = (EdgeType){4, 7, 7};
	G->edge[12] = (EdgeType){4, 5, 26};
	G->edge[13] = (EdgeType){5, 6, 17};
	G->edge[14] = (EdgeType){6, 7, 19};
}

/* ������ */
void SwapEdges(EdgeType *a, EdgeType *b) 
{
	EdgeType temp = *a;
	*a = *b;
	*b = temp;
}

/* ��Ȩֵ�Ա�ð������ */
void SortEdges(EdgeGraph *G) 
{
	for (int i = 0; i < G->edgeNum - 1; i++) 
	{
		for (int j = 0; j < G->edgeNum - i - 1; j++) 
		{
			if (G->edge[j].weight > G->edge[j + 1].weight) 
			{
				SwapEdges(&G->edge[j], &G->edge[j + 1]);
			}
		}
	}
}


/* ���Ҹ��ڵ� */
int findRoot(int parent[], int v) 
{
	int t = v;
	while (parent[t] > -1) 
	{
		t = parent[t];
	}
	return t;
}

/* Kruskal�㷨������С������ */
void Kruskal(EdgeGraph *G) 
{
	
	SortEdges(G);
	
	int parent[MAX_VERTEX_NUM]; /* ��¼����i��˫�׽�� */
	int num = 0; // �Ѽ�����С�������ı���
	
	for (int i = 0; i < G->vertexNum; i++) 
	{
		parent[i] = -1; /* ��ʼʱ����iû��˫�ף��ý���������������ĸ��ڵ�*/
	}
	
	
	printf("��С�������ı����£�\n");
	for (int i = 0; i < G->edgeNum; i++) 
	{
		int v1 = findRoot(parent, G->edge[i].from); /* v1��v2�ֱ��ʾ���������������ĸ��ڵ� */
		int v2 = findRoot(parent, G->edge[i].to);
		
		/* ��v1 == v2���ʾ�γɻ�·*/
		if (v1 != v2) 
		{
			printf("(%d, %d) %d\n", G->edge[i].from, G->edge[i].to, G->edge[i].weight);
			parent[v2] = v1; /* �ϲ���������v1�Ǹ��ڵ� */
			num++;
			
			if (num == G->vertexNum - 1) 
			{
				return; // ��С���������
			}
		}
	}
}

int main() 
{
	EdgeGraph G;
	CreateGraph(&G);
	Kruskal(&G);
	return 0;
}

