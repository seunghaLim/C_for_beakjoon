#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct _NODE
{
	int data;
	struct _NODE* link;
} NODE;

typedef struct _QUEUE {

	NODE* front;
	int cap;
	NODE* rear;

} QUEUE;

void pushX(int X, QUEUE* queue);
void pop(QUEUE* queue);
void size(QUEUE* queue);
void empty(QUEUE* queue);
void front(QUEUE* queue);
void back(QUEUE* queue);


int main()
{
	int order;
	scanf("%d", &order);

	QUEUE* queue;
	queue = (QUEUE *)malloc(sizeof(QUEUE));

	if (queue)
	{
		queue->cap = 0;
		queue->front = NULL;
		queue->rear = NULL;
	}

	while (order != 0)
	{
        char bumper[4];
        scanf("%s", bumper);

		if (strcmp(bumper, "push") == 0)
		{
			int x;
			scanf("%d", &x);

			pushX(x, queue);

			--order;
		}
		else if (strcmp(bumper, "pop") == 0)
		{
			pop(queue);
			--order;
		}
		else if (strcmp(bumper, "size") == 0)
		{
			size(queue);
			--order;

		}
		else if (strcmp(bumper, "empty") == 0)
		{
			empty(queue);
			--order;
		}
		else if (strcmp(bumper, "front") == 0)
		{
			front(queue);
			--order;

		}
		else if (strcmp(bumper, "back") == 0)
		{
			back(queue);
			--order;

		}
		else 
		{
			printf("Error: Command is not available\n");
			--order;
		}
	}

	if (order == 0)
	{
		free(queue);
	}


}

void pushX(int X, QUEUE* queue)
{
	NODE* newN;
	newN = (NODE *)malloc(sizeof(NODE));
	newN->data = X;
	newN->link = NULL;

	if (queue->cap == 0)
		queue->front = newN;
	else
		queue->rear->link = newN;

	queue->rear = newN;

	++queue->cap;
	
}

void pop(QUEUE* queue)
{
	if (queue->cap == 0)
		printf("-1\n");
	else
	{
		NODE* temp;
		temp = queue->front;
		queue->front = queue->front->link;
		printf("%d\n", temp->data);
		
		free(temp);

		--queue->cap;
	}
	
}

void size(QUEUE* queue)
{
	printf("%d\n", queue->cap);
}

void empty(QUEUE* queue)
{
	if (queue->cap == 0)
		printf("1\n");
	else
		printf("0\n");
}

void front(QUEUE* queue)
{
	if (queue->cap == 0)
		printf("-1\n");
	else
		printf("%d\n", queue->front->data);
}

void back(QUEUE* queue)
{
	if (queue->cap == 0)
		printf("-1\n");
	else
		printf("%d\n", queue->rear->data);
}