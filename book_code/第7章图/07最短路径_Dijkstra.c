#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MAXEDGE 20	 	 /* ������ */
#define MAXVEX 20	 	 /* ��󶥵��� */
#define GRAPH_INFINITY 65535

typedef int Status; /* ������������ */

typedef struct
{
	int vexs[MAXVEX];          /* ����� */
	int arc[MAXVEX][MAXVEX];   /* �ڽӾ��� */
	int numVertexes, numEdges; /* ͼ�ĵ�ǰ�������ͱ��� */
} MGraph;

/* 
 * ����� dist �� path ���麬����ʾ����һ�£�
 * - dist[i]: ��¼����� startV ������ i �ĵ�ǰ��̾���
 * - path[i]: ��¼����㵽 i �����·���ϣ�i ��ǰ������
 * - s[i]:    �ж϶��� i �Ƿ����������·������ (S)��1��ʾ�����룬0��ʾδ����
 */

/*------------------ ͼ�������� ------------------*/
void CreateMGraph(MGraph *G)
{
	int i, j;
	
	/* ��ʼ���������ͱ��� */
	G->numVertexes = 9;
	G->numEdges = 16;
	
	/* ��ʼ������ */
	for (i = 0; i < G->numVertexes; i++)
	{
		G->vexs[i] = i;
	}
	
	/* ��ʼ���ڽӾ��� */
	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			if (i == j)
			{
				G->arc[i][j] = 0;
			}
			else
			{
				G->arc[i][j] = GRAPH_INFINITY;
			}
		}
	}
	
	/* ��ӱ߼���Ȩֵ������ͼ�����ԶԳƣ� */
	G->arc[0][1] = 1;
	G->arc[0][2] = 5; 
	G->arc[1][2] = 3; 
	G->arc[1][3] = 7; 
	G->arc[1][4] = 5; 
	G->arc[2][4] = 1; 
	G->arc[2][5] = 7; 
	G->arc[3][4] = 2; 
	G->arc[3][6] = 3; 
	G->arc[4][5] = 3;
	G->arc[4][6] = 6;
	G->arc[4][7] = 9; 
	G->arc[5][7] = 5; 
	G->arc[6][7] = 2; 
	G->arc[6][8] = 7;
	G->arc[7][8] = 4;
	
	/* ����ͼ�ԳƸ�ֵ */
	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = i + 1; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

/*------------------ ���ߺ�����Ѱ�� dist[] ����δ���� S �Ҿ�����С�Ķ����±� ------------------*/
int findMinDist(int dist[], int s[], int n)
{
	int i;
	int minIndex = -1;
	int minValue = GRAPH_INFINITY;
	
	for(i = 0; i < n; i++)
	{
		/* s[i] == 0 ��ʾ���� i ������ S �� */
		if(s[i] == 0 && dist[i] < minValue)
		{
			minValue = dist[i];
			minIndex = i;
		}
	}
	return minIndex;
}

/*------------------ Dijkstra �㷨����� startV ���������ж�������·�� ------------------*/
void Dijkstra(MGraph G, int startV, int dist[], int path[])
{
	/* s[] ���ڱ�Ƕ����Ƿ��Ѿ����� S��1 ��ʾ���룬0 ��ʾ���� S */
	int s[MAXVEX];
	int i, num, min;
	
	/* 1. ��ʼ�� dist[]��path[]��s[] */
	for(i = 0; i < G.numVertexes; i++)
	{
		dist[i] = G.arc[startV][i];
		if(dist[i] != GRAPH_INFINITY)
		{
			path[i] = startV;
		}
		else
		{
			path[i] = -1;
		}
		s[i] = 0;  /* ��ʼʱ�����ж��㶼���� S �� */
	}
	
	/* ������� S */
	dist[startV] = 0;      
	path[startV] = -1;
	s[startV] = 1;
	num = 1;  /* S �������Ѿ��� 1 �������� */
	
	/* 2. ������ֱ�����ж��㶼���� S */
	while(num < G.numVertexes)
	{
		/* 2.1 ����δ���� S �Ķ����У��ҳ� dist ��С�� */
		min = findMinDist(dist, s, G.numVertexes);
		
		/* ����Ҳ����ɸ��µĶ��㣬˵��ʣ�ඥ��Բ��ɴ���Ѿ�ȫ�������꣬��ǰ���� */
		if(min == -1)
		{
			break;
		}
		
		/* ���ҵ��Ķ������� S */
		s[min] = 1;
		num++;
		
		/* 2.2 ��������Ķ��� min ��������������� dist �� path */
		for(i = 0; i < G.numVertexes; i++)
		{
			/* ������� i ������ S���ҿ���ͨ�� min �õ����̵ľ��룬�͸��� */
			if(s[i] == 0 && (dist[min] + G.arc[min][i] < dist[i]))
			{
				dist[i] = dist[min] + G.arc[min][i];
				path[i] = min;
			}
		}
	}
}

/*------------------ ��ӡ���·��������� ------------------*/
void displayPath(int dist[], int path[], int startV, int n)
{
	int i, j;
	
	printf("���·����������:\n");
	for(i = 0; i < n; i++)
	{
		if(i == startV)
		{
			continue;
		}
		
		/* ���յ� i ����׷��ǰ�� */
		printf("v%d - v%d : ", startV, i);
		j = i;
		printf("%d ", j);
		while(path[j] != -1)
		{
			j = path[j];
			printf("%d ", j);
		}
		printf("\n");
	}
	
	printf("\nԴ�㵽����������·������Ϊ:\n");
	for(i = 0; i < n; i++)
	{
		if(i == startV)
		{
			continue;
		}
		printf("v%d - v%d : %d\n", startV, i, dist[i]);
	}
}

/*------------------ ������ ------------------*/
int main(void)
{
	MGraph G;
	int dist[MAXVEX]; /* �洢��̾��� */
	int path[MAXVEX]; /* �洢ǰ����Ϣ */
	int startV = 0;   /* Դ�㣨��㣩���ɸ�����Ҫ�޸� */
	
	/* 1. ����ͼ */
	CreateMGraph(&G);
	
	/* 2. ���� Dijkstra �㷨�������·�� */
	Dijkstra(G, startV, dist, path);
	
	/* 3. ��ӡ��� */
	displayPath(dist, path, startV, G.numVertexes);
	
	return 0;
}



