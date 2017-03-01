/*
	The Memory function is aligned to 64 byte boundary between values so that
	the contents of the Memory Function "F" are spaced far enough to correct
	False Sharing. 
	
	Note the __attribute__ compiler directive for this purpose in the 'elem' struct
	//so that we can index "F" as a normal 2D array whist the compiler takes care
	//of indirect addressing and any extra offsetting required (Instead of explicit mention).

	Function used to allocate Dynamic Memory:
		void *memalign(size_t alignment, size_t size); //of malloc.h

	On event of a failure or crash => You may have to use Intel/AMD specific directives & prototype
	To work with icc: check __declspec(align(n)) directive as well as
	_aligned_malloc and _aligned_free to deal with heap memory

*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <malloc.h>
typedef struct {
    int x;
} __attribute__((aligned(64))) elem;
int MFKnapsack(int, int); //Function returning the optimal value for a given n and W
int max(int, int);
int n;
int* weights;
int* values;
int W;
elem **F;
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
	F = (elem**)malloc((n+1)*sizeof(elem*));
	for(i=0;i<=n;i++)
		F[i] = (elem*)memalign(64,(W+1)*sizeof(elem));
	for(i=0;i<(W+1);i++)
		(*(F) + i ) -> x = 0; //F[0][i]
	for(i=0;i<(n+1);i++)
		(*(F+i)) -> x = 0; //F[i][0]

	#pragma omp parallel for
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=W;j++)
			(*(F + i) + j) -> x = -1;
	}

	int res;
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			res = MFKnapsack(n, W); //Optimal value for items with given weights and values
		}
	}

	

	printf("Optimal value= %d\n", res);
	
	//printf("Time taken = %lfs",(double)(end-start));
	free(weights);
	free(values);
	return 0;
}
int MFKnapsack(int i, int j)
{
	int value;
	if( ((*(F + i) + j)->x) < 0)
	{
		if(j < weights[i])  //If weight of item is more than current capacity
			value = MFKnapsack(i-1, j); //Value of previous item
		else
		{
			int a;
			int b;

				#pragma omp parallel sections
				{
					#pragma omp  section
					{
						a = MFKnapsack(i-1, j);
					}
					#pragma omp  section
					{
						b =  (values[i] + MFKnapsack(i-1, j - weights[i]));
					}
				}
				value = max(a,b);
			
		}
		(*(F + i) + j)->x = value;
	}
	return (*(F + i) + j)->x;
}
int max(int a, int b)
{
	return (a>b?a:b);
}