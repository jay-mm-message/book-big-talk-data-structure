#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MAXEDGE 20	 /* ������ */
#define MAXVEX 20	 /* ��󶥵��� */
#define GRAPH_INFINITY 65535

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* ����ͼ */
{
	int i, j;

	/* printf("����������Ͷ�����:"); */
	G->numEdges=15;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = GRAPH_INFINITY;
		}
	}

	G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19; 

	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/* Prim�㷨������С������  */
void MiniSpanTree_Prim(MGraph G) 
{
	int min, i, j, k;
	int adjvex[MAXVEX];     // ������С���������㼯�е�i����СȨֵ���Ǹ�����
	int lowcost[MAXVEX];    // ������С���������㼯��i�����СȨֵ
	
	// ��ʼ��������ʼ��������ΪV0
	lowcost[0] = 0;       //�����V0���뼯��U����V0������С�������еĶ��㼯
	adjvex[0] = 0;         
	
	// ��ʼ����ʼ����V0����������ı�Ȩֵ
	for (i = 1; i < G.numVertexes; i++) 
	{
		lowcost[i] = G.arc[0][i];  // ���ôӶ���V0����������ıߵ�Ȩֵ
		adjvex[i] = 0;              // V0��������������
	}
	
	// ѡ������G.numVertexes-1�����������С������
	for (i = 1; i < G.numVertexes; i++) 
	{
		min = GRAPH_INFINITY;  // ��ʼ����С��ȨֵΪһ���ϴ����
		j = -1;                // ��ʼ����С�ߵ��±�Ϊ-1
		
		// ����Ȩֵ��С��δ������С�������ıߺͶ���
		for (k = 1; k < G.numVertexes; k++) 
		{
			if (lowcost[k] != 0 && lowcost[k] < min) 
			{
				min = lowcost[k];  // ������С�ߵ�Ȩֵ
				j = k;             // ��¼��С�ߵĶ���
			}
		}
		
		// �����ǰ��С�������ıߣ�����ǰ������͵�ǰ���㣬�Լ�����֮��ı�Ȩ��
		printf("(%d, %d) Ȩֵ: %d\n", adjvex[j], j, min);
		
		// ������ j ������С������
		lowcost[j] = 0;
		
		// �¶��㲢��U���Ϻ󣬸���U���ϵ�V-U���ϸ��ߵ�Ȩֵ
		for (k = 1; k < G.numVertexes; k++) 
		{
			if (lowcost[k] != 0 && G.arc[j][k] < lowcost[k]) 
			{
				lowcost[k] = G.arc[j][k];   // ���¶��� k ����С���������㼯��U����С��Ȩֵ
				adjvex[k] = j;               // ���¶��� k ��ǰ��Ϊ���� j
			}
		}
	}
}


int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
  
	return 0;
 
}
