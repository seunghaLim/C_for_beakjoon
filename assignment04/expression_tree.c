#include <stdlib.h> // malloc, atoi
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert
#include <string.h> // strlen

#define MAX_STACK_SIZE	50 // 내부적으로 스택 사용 - 스택의 크기 50

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	char		data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE; // 루트만 가리키는 구조체. 연결리스트의 헤드라고 보면 됨
 
////////////////////////////////////////////////////////////////////////////////
// Prototype declarat  ions

/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
TREE *createTree(void) // 빈 트리 만드는 함수. 트리구조체(두번째 구조체) 만들어서 반환
{
	TREE* tree;
	tree = malloc(sizeof(TREE));
	tree->root = NULL;

	if(tree)
		return tree;
}


void destroyTree( TREE *pTree); 

static void _destroy( NODE *root) // 실제 딜리트하는 얘 순회하면서 노드 전부 해제 
{
	if (root)
	{
		if (root->left)
		{
			_destroy(root->left);
		}
		
		free(root);
		
		if (root->right)
		{
			_destroy(root->right);
		}
	}
}


/*  Allocates dynamic memory for a node and returns its address to caller
	return	node pointer
			NULL if overflow
*/
static NODE *_makeNode( char ch)    // 연산자 및 피연산자의 데이터가 들어가는 노드 하나 만들어줌
{									 // 연산자든 피연산자든 입력받아서 메모리 할당해서 노드 만들어주고 왼오 링크 널로 해주고 포인터 주소 반환 
	NODE* node;
	node = malloc(sizeof(NODE));
	
	if (node)
	{
		node->data = ch;
		node->left = NULL;
		node->right = NULL;
		
		return node;
	}
	else
	{
		return NULL;
	}
	
}
									
/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree( char *expr, TREE *pTree)  // _makeNode 얘 호출
{											// 사용자가 입력한 후위표기식을 expr로 받아서 expression tree 만든 다음에 pTree가 헤드 구조를 가리키게 함
	// 1 2 + 3 4 * - 들어왔다고 가정
	int num = strlen(expr); //  num = 7 
	NODE* nodeArr = malloc(sizeof(NODE) * MAX_STACK_SIZE); // 길이가 7인 nodeArr 배열 만들기
	int top = -1;
	
	for (int i = 0; i < num; i++)
	{	
		if (expr[i] >= '0' && expr[i] <= '9')
		{
			NODE* newN;
			newN = _makeNode(expr[i]);
			
			top++;
			nodeArr[top].right = newN; // nodeArr[top]->right = newN 이렇게 안해도 되는지 고민
		}
		else 
		{
			NODE* newN;
			newN = _makeNode(expr[i]);
			
			newN->right = nodeArr[top].right;
			top--;
			
			if (top <= -1)
			{
				free(newN->right);
				free(newN);
				free(nodeArr);
				return 0;
			}

			newN->left = nodeArr[top].right;
			top--;
			
			top++;
			nodeArr[top].right = newN;
			
		}
	}
	
	if (top == 0)
	{
		pTree->root = nodeArr[0].right;
		free(nodeArr);
		return 1;
	}
	else if (top > 0)
	{
		for (int i = top; i >= 0; i--)
		{
			free(nodeArr[i].right); 
		}
		free(nodeArr);
		return 0;
	}
	
}	


void traverseTree( TREE *pTree);		

/* internal traversal function			
	an implementation of ALGORITHM 6-6
*/
static void _traverse(NODE *root)		// infix 수식으로 바꿔줄 때 필요함 중위 순회를 해 가면서 중위표기식으로 바꿔줌
{
	if (root)
	{
		if (root->data >= '0' && root->data <= '9')	// 루트가 피연산자일 경우
		{
			printf("%c ", root->data);
		}
		else
		{
			printf("( ");
			_traverse(root->left);
			printf("%c ", root->data);
			_traverse(root->right);
			printf(") ");
		}			
	}
}

/* Print tree using inorder right-to-left traversal
*/
void printTree( TREE *pTree);  

/* internal traversal function
*/
static void _infix_print( NODE *root, int level)  // 중위순회지만 오- 자기자신 - 왼으로 순회하면서 프린트 하도록 함 level = 0인 상태
{												   // level이 커질수록 tap키가 많이 필요하기 때문에 
    													  //- level이 0인 루트는 tap 출력 안함 level이 1인 애들이 tap 하나 출력하고 출력 이렇게 
												// tap키 프린트 어케함????? 
	if (root)
	{
		level += 4;

		if (root->right)
		{
			_infix_print(root->right, level);
		}
		
		printf("\n");
		for (int i = 4; i < level; i++)
			printf(" ");
		printf("%c\n", root->data);
		
		if (root->left)
		{	
			_infix_print(root->left, level);
		}
	}											 
}												  
												  
								  
												  
												  
/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix(char *expr)  // 후위표기식을 받아서 내부에서 계산해서 리턴
{
	int num = strlen(expr); //  num = 7 
	char* arr = malloc(sizeof(char) * MAX_STACK_SIZE); // 길이가 7인 nodeArr 배열 만들기
	int top = -1;
	
	for (int i = 0; i < num; i++)
	{	
		if (expr[i] >= '0' && expr[i] <= '9')
		{
			top++;
			arr[top] = expr[i] - 48; // 포인터를 char형 배열에 넣을 수 있나..? 캐스팅 안해도 됨? 
		}
		else 
		{
			if (top < -1)		// ????
			{
				return -12345;		// 실패할 경우 리턴값 어떻게? 
			}
			
			int b = arr[top];
			top--;
			int a = arr[top];
			top--;
			
			int result;
			if (expr[i] == '+')
			{
				result = a + b;
			}
			else if (expr[i] == '-')
			{
				result = a - b;
			}
			else if (expr[i] == '*')
			{
				result = a * b;
			}
			else if (expr[i] == '/')
			{
				result = a / b;
			}

			top++;
			arr[top] = result;
		}
	}
		
	if (top == 0)
	{
		free(arr);
		return (float)arr[0];
	}
	else if (top > 0)
	{
		free(arr);
		return -12345;
	}

		
}

////////////////////////////////////////////////////////////////////////////////
void destroyTree( TREE *pTree)
{
	if (pTree)
	{
		_destroy( pTree->root);
	}
		
	free(pTree);
}

////////////////////////////////////////////////////////////////////////////////

void printTree( TREE *pTree)
{
	_infix_print(pTree->root, 0);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
void traverseTree( TREE *pTree)
{
	_traverse(pTree->root);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	char expr[1024];
	
	fprintf( stdout, "\nInput an expression (postfix): "); // 후위표기식 입력하라
	
	while (fscanf( stdin, "%s", expr) == 1)
	{
		
		tree = createTree();	// creates a null tree
		
		if (!tree)
		{
			printf( "Cannot create tree\n");
			return 100;
		}
		
		// postfix expression -> expression tree
		int ret = postfix2tree( expr, tree);	//	invalid한 트리가 만들어졌을 때 이 함수 안에서 메모리 해제해야 함 
		if (!ret) // 리턴값이 잘못되었을 경우
		{
			fprintf( stdout, "invalid expression!\n");
			destroyTree( tree);
			fprintf( stdout, "\nInput an expression (postfix): ");
		 	continue;
		}
		
		// expression tree -> infix expression
		fprintf( stdout, "\nInfix expression : "); // 중위표기식 프린트
		traverseTree( tree);
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "\n\nTree representation:\n"); // 트리 표현 프린트
		printTree(tree);
		
		// evaluate postfix expression
		float val = evalPostfix( expr);
		fprintf( stdout, "\nValue = %f\n", val); // 후위표기식 계산값 프린트
		
		//destroy tree
		destroyTree( tree);
		
		fprintf( stdout, "\nInput an expression (postfix): ");
	}
	return 0;
}

