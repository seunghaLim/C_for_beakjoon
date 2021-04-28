#include <stdio.h>

void swap(int* a, int* b);

int main()
{
	int num;
	scanf("%d\n", &num);
	
	int count = num;
	int array[1001];

	for (int i = 0; i < num; i++)
	{
		scanf("%d", &array[i]);
		--count; 
	}
	
	if (count == 0)
	{
		for (int i = 0; i < num - 1; i++)
		{
			int s = i;

			for (int j = i + 1; j < num; j++)
			{
				if (array[s] > array[j])
				{
					s = j;
				}
			}
			swap(&array[i], &array[s]);
		}
	}
	
	for (int i = 0; i < num; i++)
	{
		printf("%d\n", array[i]);
	}
}

void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}