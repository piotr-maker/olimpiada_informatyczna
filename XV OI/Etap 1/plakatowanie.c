#include <stdio.h>
#include <stdlib.h>


int main() {
	int n, d, w;
	int result = 1, index = 0;
	int *stack;

	scanf("%d", &n);
	stack = (int*)calloc(sizeof(int), n);
	scanf("%d %d", &d, &w);
	stack[index] = w; 

	for(int i = 1; i < n; i++) {
		scanf("%d %d", &d, &w);
		while( index > 0 && w < stack[index]) index -= 1;
		if(stack[index] !=w) {	
			index += 1;	
			result += 1;	
			stack[index] = w;
		}
	}

	printf("%d\n", result);
	free(stack);
	return 0;
}
