#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main(int argc, char const *argv[])
{
	int __attribute__((aligned(16))) *arr = (int*)memalign(16,10*sizeof(int));
	int l = 16*9;
	for (int i = 0; i < l; i += 16)
	{
		arr[i] = i/16;
	}
	for (int i = 0; i < l; ++i)
	{
		printf("%d\n",arr[i]);
	}
	return 0;
}