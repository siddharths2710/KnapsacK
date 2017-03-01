#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
int knapsack(int, int);
int max(int, int);
int n;
int* weights;
int* values;
int W;
int** F;
int main()
{
	scanf("%d", &n);
	weights = (int*)malloc((n+1)*sizeof(int));
	values = (int*)malloc((n+1)*sizeof(int));
	int i, j;
	for(i=1;i<=n;i++)
		scanf("%d", &weights[i]);
	for(i=1;i<=n;i++)
		scanf("%d", &values[i]);
	scanf("%d", &W);
	F = (int**)malloc((n+1)*sizeof(int*));

	for(i=0;i<=n;i++)
		F[i] = (int*)malloc((W+1)*sizeof(int));

	for(i=0;i<(W+1);i++)
		F[0][i] = 0;

	for(i=0;i<(n+1);i++)
		F[i][0] = 0;

	for(i=1;i<=n;i++)
	{
		
		for(j=1;j<=W;j++)
			F[i][j] = -1;
	}


	int res = knapsack(n, W); //Invoke Memory Function	
	/*
	printf("\n\t--------\t");	
	for(j=1;j<=W;j++)
	{
			printf("-------");	
	}
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("\t%d\t|\t",i);
		for(j=1;j<=W;j++)
		{
			printf("%d\t",F[i][j]);			
		}
		printf("\n");
	}
	*/
	printf("Optimal value= %d\n", res);
	free(weights);
	free(values);
	return 0;
}
int knapsack(int i, int j)
{
	int value;
	
	if(F[i][j] < 0)
	{
		if(j < weights[i])  //If weight of item is more than current capacity
			value = knapsack(i-1, j); //Value of previous item
		else
			value = max(knapsack(i-1, j), (values[i] + knapsack(i-1, j - weights[i]))); //
		F[i][j] = value;
	}
	return F[i][j];
}
int max(int a, int b)
{
	return (a>b?a:b);
}
