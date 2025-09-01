#include <stdio.h>    
#include <stdlib.h>   
#include <math.h>  
#include <time.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAX_EDGE_NUM 20	 	 /* 最大边数 */
#define MAX_VERTEX_NUM 20	 /* 最大顶点数 */
#define GRAPH_INFINITY 65535

typedef struct 
{
	int from, to; 		/*边的两个端点*/ 
	int weight;   		/*边的权值*/
} EdgeType;

typedef struct 
{
	int vertex[MAX_VERTEX_NUM];		/*存放图顶点的数据*/
	EdgeType edge[MAX_EDGE_NUM];	/*边集数组*/
	int vertexNum, edgeNum; 		/*图的顶点数和边数*/
} EdgeGraph;

/* 创建图 */
void CreateGraph(EdgeGraph *G) 
{
	G->vertexNum = 9;
	G->edgeNum = 15;
	
	/* 初始化顶点数组 */
	for (int i = 0; i < G->vertexNum; i++) 
	{
		G->vertex[i] = i;
	}
	
	/* 结构体字面量 */
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

/* 交换边 */
void SwapEdges(EdgeType *a, EdgeType *b) 
{
	EdgeType temp = *a;
	*a = *b;
	*b = temp;
}

/* 按权值对边冒泡排序 */
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


/* 查找根节点 */
int findRoot(int parent[], int v) 
{
	int t = v;
	while (parent[t] > -1) 
	{
		t = parent[t];
	}
	return t;
}

/* Kruskal算法生成最小生成树 */
void Kruskal(EdgeGraph *G) 
{
	
	SortEdges(G);
	
	int parent[MAX_VERTEX_NUM]; /* 记录顶点i的双亲结点 */
	int num = 0; // 已加入最小生成树的边数
	
	for (int i = 0; i < G->vertexNum; i++) 
	{
		parent[i] = -1; /* 初始时顶点i没有双亲，该结点是所在生成树的根节点*/
	}
	
	
	printf("最小生成树的边如下：\n");
	for (int i = 0; i < G->edgeNum; i++) 
	{
		int v1 = findRoot(parent, G->edge[i].from); /* v1和v2分别表示两个顶点所在树的根节点 */
		int v2 = findRoot(parent, G->edge[i].to);
		
		/* 若v1 == v2则表示形成回路*/
		if (v1 != v2) 
		{
			printf("(%d, %d) %d\n", G->edge[i].from, G->edge[i].to, G->edge[i].weight);
			parent[v2] = v1; /* 合并两棵树，v1是根节点 */
			num++;
			
			if (num == G->vertexNum - 1) 
			{
				return; // 最小生成树完成
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

