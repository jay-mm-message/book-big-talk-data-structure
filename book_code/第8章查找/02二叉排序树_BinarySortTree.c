#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;	/* Status�Ǻ��������ͣ���ֵ������ִ��״̬������OK��ERROR�ȣ� */ 

/* �������Ķ���������ṹ���� */
typedef  struct BiTNode	/* ���ṹ */
{
	int data;	/* ������� */
	struct BiTNode *lchild;     /* ����ָ�� */
	struct BiTNode *rchild;     /* �Һ���ָ�� */
} BiTNode, *BiTree;


/*-----------------------------------------------------------
  �ݹ���Ҷ���������T���Ƿ���ڹؼ���key��
  ����˵����
  T : ��ǰ���������������ָ��
  key : �����ҹؼ���
  f : ��ǰ���ĸ����ָ�루��ʼ����ʱΪNULL��
  p : ����ֵָ�롣������ҳɹ���*pָ���㣻������ʧ�ܣ�*pָ�����·�������һ�����ʵĽ��
  ����ֵ��
  TRUE  : �ҵ��ؼ���key�Ľ��
  FALSE : û�ҵ�
  ------------------------------------------------------------*/
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p) 
{  
	if (T == NULL)	/*  ���Ҳ��ɹ� */
	{ 
		*p = f;		//*p = f��*p ʵ�����Ƕ�ָ����ָ��Ķ�������ã����ں����ڶ�ָ��ָ�������޸ģ���һ�޸Ļ�Ӱ�쵽���еݹ���õķ���ֵ����Ϊ���ǹ��������ַ��	
		//����ں����ڲ��� p = &f���������غ�f��ʧЧ��ָ��p��ָ��һ����Ч�ĵ�ַ������δ������Ϊ��
		return FALSE; 
	}
	else if (key == T->data) /*  ���ҳɹ� */
	{ 
		*p = T;  
		return TRUE; 
	} 
	else if (key < T->data) 
		return SearchBST(T->lchild, key, T, p);  /*  ���������м������� */
	else  
		return SearchBST(T->rchild, key, T, p);  /*  ���������м������� */
}


/*-----------------------------------------------------------
  ������������T�в����ڹؼ��ֵ���key�Ľ�㣬
  �����key��������TRUE�����򷵻�FALSE��
  ------------------------------------------------------------*/
Status InsertBST(BiTree *T, int key) 
{  
	BiTree p,s;
	if (!SearchBST(*T, key, NULL, &p)) /* ���Ҳ��ɹ� */
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;  
		s->lchild = s->rchild = NULL;
		
		if (p == NULL) 
			*T = s;			/*  ����������sΪ�µĸ���� */
		else if (key<p->data) 
			p->lchild = s;	/*  ����sΪ���� */
			//�ں����ڶ�ָ��ָ�������޸ģ�����ָ������������͵ı���������ִ����Ϻ�ᱣ���޸ġ�
		else 
			p->rchild = s;  /*  ����sΪ�Һ��� */
		return TRUE;
	} 
	else 
		return FALSE;  /*  �������йؼ�����ͬ�Ľ�㣬���ٲ��� */
}

/* �Ӷ�����������ɾ�����p�����ؽ���������������� */
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild==NULL) /* �������գ���ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧) */
	{
		q=*p; 
		*p=(*p)->lchild; 
		free(q);
	}
	else if((*p)->lchild==NULL) /* ������Ϊ�գ���ֻ���ؽ������� */
	{
		q=*p; 
		*p=(*p)->rchild; 
		free(q);
	}
	else /* �������������գ���Ҫ������ǰ�� */
	{
		q=*p; 
		s=(*p)->lchild;
		while(s->rchild) /* ���������ĸ��ڵ㿪ʼ��s��������������������ǰ����ֱ��sû�����ӽڵ�Ϊֹ�������õ���s���������������Ҳ�Ľڵ㣬Ҳ���Ǹýڵ��Ǳ�ɾ���ڵ������ǰ�� */
		{
			q=s;	/* q��������s�ĸ��ڵ� */
			s=s->rchild;
		}
		(*p)->data=s->data; /*  sָ��ɾ����ֱ��ǰ��������ɾ���ǰ����ֵȡ����ɾ����ֵ�� */
		if(q!=*p)
			q->rchild=s->lchild; /*  ��s���������ӵ�q����������λ�� */ 
		else
			q->lchild=s->lchild; /*  ��s���������ӵ�Ҫɾ���ڵ���������� */
		free(s);
	}
	return TRUE;
}

/* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��, */
/* ������TRUE�����򷵻�FALSE�� */
Status DeleteBST(BiTree *T,int key)
{ 
	if(*T == NULL) /* �����ڹؼ��ֵ���key������Ԫ�� */ 
		return FALSE;
	else
	{
		if (key==(*T)->data) /* �ҵ��ؼ��ֵ���key������Ԫ�� */ 
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
	
	printf("��ͨ���ϵ���Ի����������鿴�����������ṹ��\n");
	return 0;
}
