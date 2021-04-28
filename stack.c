#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE {

	int data;
	struct _NODE* link;

} NODE;

typedef struct _STACK {

	int cap;
	NODE* top;

} STACK;


void pushX(int X, STACK* stack);
void pop(STACK* stack);
void size(STACK* stack);
void empty(STACK* stack);
void top(STACK* stack); 


int main()
{
	int order;	// 명령은 어떻게 쓸겨..? 
	scanf("%d", &order); // 명령의 수 받기

	STACK* stack; // 스택 만들기
	stack = (STACK *)malloc(sizeof(STACK)); 
	
	if (stack)
	{
		stack->cap = 0;
		stack->top = NULL;
	}
	
	while (order != 0)
	{
		char *bumper;
		scanf("%s/n", bumper);

		if (strcmp(bumper, "push") == 0)
		{
			int x;
			scanf("%d", &x);
			pushX(x, stack);
			--order; 
		}
		else if (strcmp(bumper, "pop") == 0)
		{
			pop(stack);
			--order; 
		}
		else if (strcmp(bumper, "size") == 0)
		{
			size(stack);
			--order; 
		}
		else if (strcmp(bumper, "empty") == 0)
		{
			empty(stack);
			--order; 
		}
		else if (strcmp(bumper, "top") == 0)
		{
			top(stack);
			--order; 
		}
		else
		{
			printf("Error: order is not available\n");
		}
	
	}

	if (order == 0)
	{
		free(stack);
	}

}



void pushX(int X, STACK* stack)
{
	NODE* newN;	// 뉴노드 선언 및 메모리 할당
	newN = (NODE *)malloc(sizeof(NODE));

	newN->data = X; // 뉴노드에 데이터 할당

	newN->link = stack->top;	// 뉴노드가 첫번째 노드로 오게 해줌
	stack->top = newN; 

	++stack->cap;
}

void pop(STACK* stack)
{
	if (stack->cap == 0)	// 0이면 오류
		printf("-1\n");

	else
	{
		
		NODE* temp;	// 임시 노드 선언

		temp = stack->top;	// 탑노드 제거	
		stack->top = stack->top->link;

		printf("%d\n", temp->data);

		free(temp);

		--stack->cap;
	}

}

void size(STACK* stack)
{
	printf("%d\n", stack->cap);
}

void empty(STACK* stack)
{
	if (stack->top == 0)
		printf("1\n");
	else
		printf("0\n");
}

void top(STACK* stack)
{
	if (stack->top == 0)
		printf("-1\n");
	else
	{
		printf("%d\n", stack->top->data);
	}
}