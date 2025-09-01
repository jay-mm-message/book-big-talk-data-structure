#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */
#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 /* ����ɢ�б�Ϊ����ĳ��� */
#define NULLKEY -32768 

typedef int Status;  /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

typedef struct
{
	int *elem; /* ����Ԫ�ش洢��ַ����̬�������� */
	int count; /* ��ǰ����Ԫ�ظ��� */
	int size;  /* ɢ�б�Ĵ�С */
} HashTable;

/* ��ʼ��ɢ�б� */
Status InitHashTable(HashTable *H, int size)
{
	int i;
	H->size = size;
	H->count = 0;
	H->elem = (int *)malloc(H->size * sizeof(int));
	if (H->elem == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return ERROR;
	}
	
	for (i = 0; i < H->size; i++)
		H->elem[i] = NULLKEY; 
	
	return OK;
}

/* ɢ�к��� */
int Hash(int key, int size)
{
	return key % size; /* ���������� */
}

/* ����ؼ��ֽ�ɢ�б� */
void InsertHash(HashTable *H, int key)
{
	int addr = Hash(key, H->size); /* ��ɢ�е�ַ */
	while (H->elem[addr] != NULLKEY) /* �����Ϊ�գ����ͻ */
	{
		addr = (addr + 1) % H->size; /* ���Ŷ�ַ��������̽�� */
	}
	H->elem[addr] = key; /* ֱ���п�λ�����ؼ��� */
	H->count++;
}

/* ɢ�б���ҹؼ��� */
Status SearchHash(HashTable H, int key, int *position)
{
	// Step 1: �����ϣ��ַ
	*position = Hash(key, H.size); 
	
	// Step 2: �жϵ�ǰλ���Ƿ�Ϊ��
	if (H.elem[*position] == NULLKEY)
	{
		return UNSUCCESS;  // ��Ϊ�գ������ʧ��
	}
	
	// Step 3: �жϵ�ǰλ���Ƿ�洢���ǹؼ���
	while (H.elem[*position] != key)
	{
		// Step 4: ʹ�ó�ͻ������������һ��ַ
		*position = (*position + 1) % H.size; 
		
		// Step 5: �����ǰλ��Ϊ�գ������ʧ��
		if (H.elem[*position] == NULLKEY)
		{
			return UNSUCCESS;
		}
		
		// Step 6: ����ص�ԭ�㣬�����ʧ��
		if (*position == Hash(key, H.size))
		{
			return UNSUCCESS;
		}
	}
	
	// Step 7: �ҵ��ؼ��֣����ҳɹ�
	return SUCCESS;
}


int main()
{
	int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
	int i, position, key, result;
	HashTable H;
	
	key = 39;
	
	// ��ʼ��ɢ�б�
	if (InitHashTable(&H, HASHSIZE) == ERROR)
		return 1;
	
	// �������ݵ�ɢ�б�
	for (i = 0; i < HASHSIZE; i++)
		InsertHash(&H, arr[i]);
	
	// ����ָ���� key
	result = SearchHash(H, key, &position);
	if (result)
		printf("���� %d �ĵ�ַΪ��%d \n", key, position);
	else
		printf("���� %d ʧ�ܡ�\n", key);
	
	// �������в��������
	for (i = 0; i < HASHSIZE; i++)
	{
		key = arr[i];
		result = SearchHash(H, key, &position);
		if (result)
			printf("���� %d �ĵ�ַΪ��%d \n", key, position);
		else
			printf("���� %d ʧ�ܡ�\n", key);
	}
	
	free(H.elem); // �ͷ��ڴ�
	return 0;
}

