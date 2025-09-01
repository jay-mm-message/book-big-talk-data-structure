#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define MAXEDGE 20	 	 /* 最大边数 */
#define MAXVEX 20	 	 /* 最大顶点数 */
#define GRAPH_INFINITY 65535

typedef int Status; /* 函数返回类型 */

typedef struct
{
	int vexs[MAXVEX];          /* 顶点表 */
	int arc[MAXVEX][MAXVEX];   /* 邻接矩阵 */
	int numVertexes, numEdges; /* 图的当前顶点数和边数 */
} MGraph;

/* 
 * 这里的 dist 和 path 数组含义与示例中一致：
 * - dist[i]: 记录从起点 startV 到顶点 i 的当前最短距离
 * - path[i]: 记录从起点到 i 的最短路径上，i 的前驱顶点
 * - s[i]:    判断顶点 i 是否已纳入最短路径集合 (S)，1表示已纳入，0表示未纳入
 */

/*------------------ 图构建函数 ------------------*/
void CreateMGraph(MGraph *G)
{
	int i, j;
	
	/* 初始化顶点数和边数 */
	G->numVertexes = 9;
	G->numEdges = 16;
	
	/* 初始化顶点 */
	for (i = 0; i < G->numVertexes; i++)
	{
		G->vexs[i] = i;
	}
	
	/* 初始化邻接矩阵 */
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
	
	/* 添加边及其权值（无向图，所以对称） */
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
	
	/* 无向图对称赋值 */
	for (i = 0; i < G->numVertexes; i++)
	{
		for (j = i + 1; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
}

/*------------------ 工具函数：寻找 dist[] 中尚未纳入 S 且距离最小的顶点下标 ------------------*/
int findMinDist(int dist[], int s[], int n)
{
	int i;
	int minIndex = -1;
	int minValue = GRAPH_INFINITY;
	
	for(i = 0; i < n; i++)
	{
		/* s[i] == 0 表示顶点 i 还不在 S 中 */
		if(s[i] == 0 && dist[i] < minValue)
		{
			minValue = dist[i];
			minIndex = i;
		}
	}
	return minIndex;
}

/*------------------ Dijkstra 算法：求从 startV 出发到所有顶点的最短路径 ------------------*/
void Dijkstra(MGraph G, int startV, int dist[], int path[])
{
	/* s[] 用于标记顶点是否已经纳入 S；1 表示纳入，0 表示不在 S */
	int s[MAXVEX];
	int i, num, min;
	
	/* 1. 初始化 dist[]、path[]、s[] */
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
		s[i] = 0;  /* 初始时，所有顶点都不在 S 中 */
	}
	
	/* 起点纳入 S */
	dist[startV] = 0;      
	path[startV] = -1;
	s[startV] = 1;
	num = 1;  /* S 集合中已经有 1 个顶点了 */
	
	/* 2. 迭代，直至所有顶点都纳入 S */
	while(num < G.numVertexes)
	{
		/* 2.1 从尚未纳入 S 的顶点中，找出 dist 最小者 */
		min = findMinDist(dist, s, G.numVertexes);
		
		/* 如果找不到可更新的顶点，说明剩余顶点皆不可达或已经全部处理完，提前结束 */
		if(min == -1)
		{
			break;
		}
		
		/* 将找到的顶点纳入 S */
		s[min] = 1;
		num++;
		
		/* 2.2 用新纳入的顶点 min 来更新其他顶点的 dist 和 path */
		for(i = 0; i < G.numVertexes; i++)
		{
			/* 如果顶点 i 还不在 S，且可以通过 min 得到更短的距离，就更新 */
			if(s[i] == 0 && (dist[min] + G.arc[min][i] < dist[i]))
			{
				dist[i] = dist[min] + G.arc[min][i];
				path[i] = min;
			}
		}
	}
}

/*------------------ 打印最短路径及其距离 ------------------*/
void displayPath(int dist[], int path[], int startV, int n)
{
	int i, j;
	
	printf("最短路径倒序如下:\n");
	for(i = 0; i < n; i++)
	{
		if(i == startV)
		{
			continue;
		}
		
		/* 从终点 i 逆向追溯前驱 */
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
	
	printf("\n源点到各顶点的最短路径长度为:\n");
	for(i = 0; i < n; i++)
	{
		if(i == startV)
		{
			continue;
		}
		printf("v%d - v%d : %d\n", startV, i, dist[i]);
	}
}

/*------------------ 主函数 ------------------*/
int main(void)
{
	MGraph G;
	int dist[MAXVEX]; /* 存储最短距离 */
	int path[MAXVEX]; /* 存储前驱信息 */
	int startV = 0;   /* 源点（起点），可根据需要修改 */
	
	/* 1. 创建图 */
	CreateMGraph(&G);
	
	/* 2. 调用 Dijkstra 算法计算最短路径 */
	Dijkstra(G, startV, dist, path);
	
	/* 3. 打印结果 */
	displayPath(dist, path, startV, G.numVertexes);
	
	return 0;
}



