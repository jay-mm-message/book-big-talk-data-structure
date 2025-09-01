#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */
#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 /* 定义散列表长为数组的长度 */
#define NULLKEY -32768 

typedef int Status;  /* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

typedef struct
{
	int *elem; /* 数据元素存储基址，动态分配数组 */
	int count; /* 当前数据元素个数 */
	int size;  /* 散列表的大小 */
} HashTable;

/* 初始化散列表 */
Status InitHashTable(HashTable *H, int size)
{
	int i;
	H->size = size;
	H->count = 0;
	H->elem = (int *)malloc(H->size * sizeof(int));
	if (H->elem == NULL)
	{
		printf("内存分配失败！\n");
		return ERROR;
	}
	
	for (i = 0; i < H->size; i++)
		H->elem[i] = NULLKEY; 
	
	return OK;
}

/* 散列函数 */
int Hash(int key, int size)
{
	return key % size; /* 除留余数法 */
}

/* 插入关键字进散列表 */
void InsertHash(HashTable *H, int key)
{
	int addr = Hash(key, H->size); /* 求散列地址 */
	while (H->elem[addr] != NULLKEY) /* 如果不为空，则冲突 */
	{
		addr = (addr + 1) % H->size; /* 开放定址法的线性探测 */
	}
	H->elem[addr] = key; /* 直到有空位后插入关键字 */
	H->count++;
}

/* 散列表查找关键字 */
Status SearchHash(HashTable H, int key, int *position)
{
	// Step 1: 计算哈希地址
	*position = Hash(key, H.size); 
	
	// Step 2: 判断当前位置是否为空
	if (H.elem[*position] == NULLKEY)
	{
		return UNSUCCESS;  // 若为空，则查找失败
	}
	
	// Step 3: 判断当前位置是否存储的是关键字
	while (H.elem[*position] != key)
	{
		// Step 4: 使用冲突处理方法计算下一地址
		*position = (*position + 1) % H.size; 
		
		// Step 5: 如果当前位置为空，则查找失败
		if (H.elem[*position] == NULLKEY)
		{
			return UNSUCCESS;
		}
		
		// Step 6: 如果回到原点，则查找失败
		if (*position == Hash(key, H.size))
		{
			return UNSUCCESS;
		}
	}
	
	// Step 7: 找到关键字，查找成功
	return SUCCESS;
}


int main()
{
	int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
	int i, position, key, result;
	HashTable H;
	
	key = 39;
	
	// 初始化散列表
	if (InitHashTable(&H, HASHSIZE) == ERROR)
		return 1;
	
	// 插入数据到散列表
	for (i = 0; i < HASHSIZE; i++)
		InsertHash(&H, arr[i]);
	
	// 查找指定的 key
	result = SearchHash(H, key, &position);
	if (result)
		printf("查找 %d 的地址为：%d \n", key, position);
	else
		printf("查找 %d 失败。\n", key);
	
	// 查找所有插入的数据
	for (i = 0; i < HASHSIZE; i++)
	{
		key = arr[i];
		result = SearchHash(H, key, &position);
		if (result)
			printf("查找 %d 的地址为：%d \n", key, position);
		else
			printf("查找 %d 失败。\n", key);
	}
	
	free(H.elem); // 释放内存
	return 0;
}

