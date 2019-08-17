#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//链表的节点
typedef struct Node
{
	int value;
	struct Node *next;
	struct Node *random;
}Node;

//初始化链表
void SListinit(Node **ppfirst)
{
	*ppfirst = NULL;
}

//销毁
void SLiistdestroy(Node *first)
{
	Node *next;
	for (Node *cur = first; cur != NULL; cur = next)
	{
		next = cur->next;
		free(cur);
	}
}

//头插(给定值)
void SListpushfront(Node **ppfirst, int v)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;
	node->next = *ppfirst;
	*ppfirst = node;
}

//头插(给定节点)
void pushfront(Node *head, Node *node)
{
	node->next = head;
	head = node;
}

///头删
void SListpopfront(Node **ppfirst)
{
	assert(*ppfirst != NULL);
	Node *next = (*ppfirst)->next;
	free(*ppfirst);
	*ppfirst = next;
}
//尾插(给定值)
void SListpushback(Node **ppfirst, int v)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = v;
	node->next = NULL;

	if (*ppfirst = NULL)
	{
		*ppfirst = node;
		return;
	}

	//找到next为空的节点
	Node *cur = *ppfirst;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	//插入
	cur->next = node;
}

//尾插(给定节点)
void pushback(Node *head, Node *node)
{
	node->next = NULL;
	if (head == NULL)
	{
		//链表中一个节点都没有
		head = NULL;
	}
	else
	{
		//找最后一个节点
		Node *cur = head;
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = node;
	}
}

//尾删
void SListpopback(Node **ppfirst)
{
	assert(*ppfirst != NULL);
	if ((*ppfirst)->next == NULL)
	{
		free(*ppfirst);
		*ppfirst = NULL;
		return;
	}
	//找到倒数第二个节点
	Node *cur = *ppfirst;
	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	//释放最后一个节点
	free(cur->next);
	cur->next = NULL;
}

//随机插入
void SListinsertafter(Node *pos, int v)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;
	node->next = pos->next;
	pos->next = node;
}

//随机删除
void SListeraseafter(Node *pos)
{
	Node *next = pos->next;
	pos->next = pos->next->next;
	free(next);
}

//查找
Node * SLfirstfind(Node *first, int v)
{
	for (Node *cur = first; cur != NULL; cur = cur->next)
	{
		if (cur->value == v)
		{
			return cur;
		}
	}
}

//删除链表中第一个遇到的v所在的节点
void Remove(Node **ppfirst, int v)
{
	if (*ppfirst == NULL)
	{
		return;
	}
	Node *cur = *ppfirst;
	if (cur->value == v)
	{
		*ppfirst = cur->next;
		free(cur);
		return;
	}
	while (cur->next != NULL)
	{
		if (cur->next->value == v)
		{
			Node *next = cur->next;
			cur->next = next->next;
			free(next);
			return;
		}
	}
}

//封装
static Node * BuyNode(int v)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;
	node->next = NULL;
	return node;
}

void test()
{
	Node *first;
	SListinit(&first);

	SListpushfront(&first, 1);

}
