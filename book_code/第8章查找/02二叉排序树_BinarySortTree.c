#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型，其值代表函数执行状态（例如OK、ERROR等） */ 

/* 二叉树的二叉链表结点结构定义 */
typedef  struct BiTNode	/* 结点结构 */
{
	int data;	/* 结点数据 */
	struct BiTNode *lchild;     /* 左孩子指针 */
	struct BiTNode *rchild;     /* 右孩子指针 */
} BiTNode, *BiTree;


/*-----------------------------------------------------------
  递归查找二叉排序树T中是否存在关键字key。
  参数说明：
  T : 当前二叉排序树根结点指针
  key : 待查找关键字
  f : 当前结点的父结点指针（初始调用时为NULL）
  p : 返回值指针。如果查找成功，*p指向结点；若查找失败，*p指向查找路径上最后一个访问的结点
  返回值：
  TRUE  : 找到关键字key的结点
  FALSE : 没找到
  ------------------------------------------------------------*/
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) 
{  
	if (T == NULL)	/*  查找不成功 */
	{ 
		*p = f;		//*p = f，*p 实际上是对指针所指向的对象的引用，即在函数内对指针指向对象的修改，这一修改会影响到所有递归调用的返回值，因为它们共享这个地址。	
		//如果在函数内部让 p = &f，函数返回后f会失效，指针p会指向一个无效的地址，导致未定义行为。
		return FALSE; 
	}
	else if (key == T->data) /*  查找成功 */
	{ 
		*p = T;  
		return TRUE; 
	} 
	else if (key < T->data) 
		return SearchBST(T->lchild, key, T, p);  /*  在左子树中继续查找 */
	else  
		return SearchBST(T->rchild, key, T, p);  /*  在右子树中继续查找 */
}


/*-----------------------------------------------------------
  若二叉排序树T中不存在关键字等于key的结点，
  则插入key，并返回TRUE；否则返回FALSE。
  ------------------------------------------------------------*/
Status InsertBST(BiTree *T, int key) 
{  
	BiTree p,s;
	if (!SearchBST(*T, key, NULL, &p)) /* 查找不成功 */
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;  
		s->lchild = s->rchild = NULL;
		
		if (p == NULL) 
			*T = s;			/*  空树，插入s为新的根结点 */
		else if (key<p->data) 
			p->lchild = s;	/*  插入s为左孩子 */
			//在函数内对指针指向对象的修改，无论指向的是哪种类型的变量，函数执行完毕后会保存修改。
		else 
			p->rchild = s;  /*  插入s为右孩子 */
		return TRUE;
	} 
	else 
		return FALSE;  /*  树中已有关键字相同的结点，不再插入 */
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild==NULL) /* 右子树空，则只需重接它的左子树（待删结点是叶子也走此分支) */
	{
		q=*p; 
		*p=(*p)->lchild; 
		free(q);
	}
	else if((*p)->lchild==NULL) /* 左子树为空，则只需重接右子树 */
	{
		q=*p; 
		*p=(*p)->rchild; 
		free(q);
	}
	else /* 左右子树均不空：需要找中序前驱 */
	{
		q=*p; 
		s=(*p)->lchild;
		while(s->rchild) /* 从左子树的根节点开始（s），不断沿右子树方向前进，直到s没有右子节点为止，这样得到的s就是左子树中最右侧的节点，也就是该节点是被删除节点的中序前驱 */
		{
			q=s;	/* q用来保存s的父节点 */
			s=s->rchild;
		}
		(*p)->data=s->data; /*  s指向被删结点的直接前驱（将被删结点前驱的值取代被删结点的值） */
		if(q!=*p)
			q->rchild=s->lchild; /*  将s的左子树接到q的右子树的位置 */ 
		else
			q->lchild=s->lchild; /*  将s的左子树接到要删除节点的左子树上 */
		free(s);
	}
	return TRUE;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
/* 并返回TRUE；否则返回FALSE。 */
Status DeleteBST(BiTree *T,int key)
{ 
	if(*T == NULL) /* 不存在关键字等于key的数据元素 */ 
		return FALSE;
	else
	{
		if (key==(*T)->data) /* 找到关键字等于key的数据元素 */ 
			return Delete(T);
		else if (key < (*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
		 
	}
}

int main(void)
{    
	int i;
	int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
	BiTree T = NULL;
	
	for (i = 0; i < 10; i++) {
		InsertBST(&T, a[i]);
	}
	
	DeleteBST(&T, 93);
	DeleteBST(&T, 47);
	
	printf("请通过断点调试或其它方法查看二叉排序树结构。\n");
	return 0;
}
