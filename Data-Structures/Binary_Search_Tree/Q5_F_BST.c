//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root) {
	if (root == NULL) {
		return ;
	}

	Stack s1, s2;
	BSTNode *popped;
	
	s1.top = NULL;
	s2.top = NULL;
	Stack *sp1 = &s1;
	Stack *sp2 = &s2;

	push(sp1, root);

	while(sp1->top != NULL) {
		popped = pop(sp1);
		push(sp2, popped);

		if (popped->left != NULL) {
			push(sp1, popped->left);
		}
		
		if (popped->right != NULL) {
			push(sp1, popped->right);
		}
	}

	while (s2.top != NULL) {
		popped = pop(sp2);
		printf("%d ", popped->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value) {
// 기본 사례: 트리가 비어있으면, 아무것도 하지 않고 반환합니다.
    if (root == NULL) {
        return NULL;
    }

    // 삭제할 노드를 찾습니다.
    if (value < root->item) {
        // 값이 현재 노드보다 작으면 왼쪽 서브트리로 이동합니다.
        // 재귀 호출의 결과를 root->left에 다시 할당하여 트리의 연결을 업데이트합니다.
        root->left = removeNodeFromTree(root->left, value);
    }
    else if (value > root->item) {
        // 값이 현재 노드보다 크면 오른쪽 서브트리로 이동합니다.
        root->right = removeNodeFromTree(root->right, value);
    }
    else {
        // 삭제할 노드를 찾았습니다 (value == root->item).

        // 경우 1: 자식이 없거나 오른쪽 자식만 있는 경우
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp; // 오른쪽 자식(또는 NULL)이 이 서브트리의 새로운 루트가 됩니다.
        }
        // 경우 2: 왼쪽 자식만 있는 경우
        else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp; // 왼쪽 자식이 새로운 루트가 됩니다.
        }

        // 경우 3: 자식이 두 개인 노드
        // 오른쪽 서브트리에서 가장 작은 노드(in-order successor)를 찾습니다.
        BSTNode* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        // 찾은 후계자(successor)의 값을 현재 노드에 복사합니다.
        root->item = temp->item;

        // 오른쪽 서브트리에서 후계자 노드를 삭제합니다.
        root->right = removeNodeFromTree(root->right, temp->item);
    }
    return root;
}
/////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
