#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int MFKnapsack(int, int); //Function returning the optimal value for a given n and W
void knapsack(int,int); //Function used to populate the Knapsack Memory Function
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
	F = (int**)malloc((W+1)*sizeof(int*));
	for(i=0;i<=W;i++)
		F[i] = (int*)malloc((n+1)*sizeof(int));
	for(i=0;i<(n+1);i++)
		F[0][i] = 0;
	for(i=0;i<(W+1);i++)
		F[i][0] = 0;
	for(i=1;i<=W;i++)
	{
		for(j=1;j<=n;j++)
			F[i][j] = -1;
	}

	

	for(i=1;i<=W;i++)
	{
		for(j=1;j<=n;j++)
		{
			knapsack(i,j); //Populate the Memory Function
		}
	}


	//clock_t start = clock();
	int res = MFKnapsack(W, n); //Optimal value for items with given weights and values
	
	//clock_t end = clock();

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
	
	//printf("Time taken = %lfs",(double)(end-start));
	free(weights);
	free(values);
	return 0;
}
int MFKnapsack(int i, int j)
{
/*
	int value;
	if(F[i][j] < 0)
	{
		if(j < weights[i])  //If weight of item is more than current capacity
			value = MFKnapsack(i-1, j); //Value of previous item
		else
			value = max(MFKnapsack(i-1, j), (values[i] + MFKnapsack(i-1, j - weights[i]))); //
		F[i][j] = value;
	}
*/
	return F[i][j];
}

void knapsack(int i, int j)
{
	int value;
	if(F[i][j] < 0)
	{
		if(i < weights[j])  //If weight of item is more than current capacity
			value = MFKnapsack(i, j-1); //Value of previous item
		else
			value = max(MFKnapsack(i, j-1), (values[j] + MFKnapsack(i-weights[j], j -1)));
		F[i][j] = value;
	}
}
int max(int a, int b)
{
	return (a>b?a:b);
}
