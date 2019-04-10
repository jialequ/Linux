

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	struct Node *left;
	struct Node *right;
	char value;
}Node;
Node *creatnode(char value)
{
	//创造一个节点
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}

Node *creattesttree()
{
	//创造一颗二叉树
	Node *a = creatnode('A');
	Node *b = creatnode('B');
	Node *c = creatnode('C');
	Node *d = creatnode('D');
	Node *e = creatnode('E');
	Node *f = creatnode('F');
	Node *g = creatnode('G');
	Node *h = creatnode('H');
	a->left = b; a->right = c;
	b->left = d; b->right = e;
	c->left = f; c->right = g;
	e->right = h;
	d->left = NULL; d->right = NULL;
	e->left = NULL; 
	f->left = NULL; f->right = NULL;
	g->left = NULL; g->right = NULL;
	h->left = NULL; h->right = NULL;
	return a;

}

//遍历节点个数  (思路一)
int count = 0;
void preorder(Node *root)
{
	if (root != NULL)
	{
		//根节点存在,树不为空,count++
		count++;
		preorder(root->left);//遍历左子树
		preorder(root->right);//遍历右子树
	}
}

// 子问题  (思路二)
int NodeSize(Node *root)
{
	//增加结束条件,一些简单的情况减少时间浪费
	if (root == NULL)
	{
		//空树
		return 0;
	}
	else if (root->left == NULL && root->right == NULL)
	{
		//只有一个根节点
		return 1;
	}
	else
	{
		int left = NodeSize(root->left);
		int right = NodeSize(root->right);
		return left + right + 1;//1是根节点
	}
}
//叶子节点个数
int leafSize(Node *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	else
	{
		int left = leafSize(root->left);
		int right = leafSize(root->right);
		return left + right;//不加根节点,包括子树的根节点(叶子节点除外)
	}
}

#define MAX(a,b) ((a) > (b) ? (a) : (b))
//二叉树的高度
int height(Node *root)
{
	if (root == NULL)
	{
		return 0;
	}

	int left = height(root->left);
	int right = height(root->right);
	return MAX(left, right) + 1;
}

//求某一层节点个数
//1.递推    左 k-1 层  右k-1 层  left + right
//终止   1.空树  0  2.k==1 1
int klevesize(Node *root,int k)
{
	if(root == NULL)
	{
		return 0;
	}

	if (k == 1)
	{
		return 1;
	}
	int left = klevesize(root->left, k - 1);
	int right = klevesize(root->right, k - 1);
	return left + right;
}

//查找:包含value的节点地址,没找到返回NULL
Node *find(Node *root, char v)
{
	if (root == NULL)
	{
		return NULL;
	}
	//不为空,查找
	if (root->value == v)
	{
		return root;
	}
	else
	{
		Node *cur = find(root->left, v);
		if (cur != NULL)
		{
			return cur;
		}
		cur = find(root->right, v);
		if (cur != NULL)
		{
			return cur;
		}
	}
	return NULL;
}

//二叉树遍历
//空树 Node *root = NULL;
//只有一个节点  root!= NULL  左右为空
//先序
void preordertraversal(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%c ", root->value);
	preordertraversal(root->left);
	preordertraversal(root->right);
}
//中序
void inordertraversal(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	inordertraversal(root->left);
	printf("%c ", root->value);
	inordertraversal(root->right);
}
//后序
void postordertraversal(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	postordertraversal(root->left);
	postordertraversal(root->right);
	printf("%c ", root->value);
}
void test1()
{
	Node *root = creattesttree();
	printf("节点个数%d\n\n", NodeSize(root));
	printf("叶子节点个数%d\n\n", leafSize(root));
	printf("高度: %d\n\n", height(root));
	for(int i = 1; i <= height(root); ++i)
	{
		printf("第 %d 层节点个数: %d\n", i, klevesize(root,i));
	}
	printf("\n");
	Node *node = creatnode('F');
	Node *ret = find(node, 'F');
	if (ret != NULL)
	{
		printf("%c找到了\n\n",ret->value);
	}

	preordertraversal(creattesttree());
	printf("\n");
	inordertraversal(creattesttree());
	printf("\n");
	postordertraversal(creattesttree());
}
int main()
{
  test1();
  system("pause");
  return 0;
}
