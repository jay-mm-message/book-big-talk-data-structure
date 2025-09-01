#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MAXEDGE 20	 /* 最大边数 */
#define MAXVEX 20	 /* 最大顶点数 */
#define GRAPH_INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* 构件图 */
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=15;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
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

/* Prim算法生成最小生成树  */
void MiniSpanTree_Prim(MGraph G) 
{
	int min, i, j, k;
	int adjvex[MAXVEX];     // 保存最小生成树顶点集中到i点最小权值的那个顶点
	int lowcost[MAXVEX];    // 保存最小生成树顶点集到i点的最小权值
	
	// 初始化，将起始顶点设置为V0
	lowcost[0] = 0;       //将起点V0并入集合U，即V0属于最小生成树中的顶点集
	adjvex[0] = 0;         
	
	// 初始化起始顶点V0到其他顶点的边权值
	for (i = 1; i < G.numVertexes; i++) 
	{
		lowcost[i] = G.arc[0][i];  // 设置从顶点V0到其他顶点的边的权值
		adjvex[i] = 0;              // V0到其他各个顶点
	}
	
	// 选择其余G.numVertexes-1个顶点加入最小生成树
	for (i = 1; i < G.numVertexes; i++) 
	{
		min = GRAPH_INFINITY;  // 初始化最小边权值为一个较大的数
		j = -1;                // 初始化最小边的下标为-1
		
		// 查找权值最小且未加入最小生成树的边和顶点
		for (k = 1; k < G.numVertexes; k++) 
		{
			if (lowcost[k] != 0 && lowcost[k] < min) 
			{
				min = lowcost[k];  // 更新最小边的权值
				j = k;             // 记录最小边的顶点
			}
		}
		
		// 输出当前最小生成树的边（即：前驱顶点和当前顶点，以及它们之间的边权）
		printf("(%d, %d) 权值: %d\n", adjvex[j], j, min);
		
		// 将顶点 j 加入最小生成树
		lowcost[j] = 0;
		
		// 新顶点并入U集合后，更新U集合到V-U集合各边的权值
		for (k = 1; k < G.numVertexes; k++) 
		{
			if (lowcost[k] != 0 && G.arc[j][k] < lowcost[k]) 
			{
				lowcost[k] = G.arc[j][k];   // 更新顶点 k 到最小生成树顶点集合U的最小边权值
				adjvex[k] = j;               // 更新顶点 k 的前驱为顶点 j
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
