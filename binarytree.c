#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
	int val;
	struct Node *left;
	struct Node *right;
} Node;
void xt(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	printf("%d ", root->val);
	xt(root->left);
	xt(root->right);
}
void zt(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	zt(root->left);
	printf("%d ", root->val);
	zt(root->right);
}
void ht(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	ht(root->left);
	ht(root->right);
	printf("%d ", root->val);
}
Node *cn(int val)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->val = val;
	node->left = node -> right = NULL;
	return node;
}

void test()
{
	Node *a = cn(1);
	Node *b = cn(2);
	Node *c = cn(3);
	Node *d = cn(4);
	Node *e = cn(5);
	Node *f = cn(6);
	Node *g = cn(7);
	Node *h = cn(8);

	a->left = b; a->right = c;
	b->left = d; b->right = e;
	c->left = f; c->right = g;
	d->left = NULL; d->right = NULL;
	e->left = NULL; e->right = h;
	f->left = NULL; f->right = NULL;
	g->left = NULL; g->right = NULL;
	h->left = NULL; h->right = NULL;
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		printf("%d:%c\n", i + 1, 'A' + i);
	}

	xt(a);
	printf("\n");
	zt(a);
	printf("\n");
	ht(a);

}
int main()
{
	test();
	return 0;
}
