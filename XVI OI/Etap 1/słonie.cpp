#include <cstdio>

struct Elephant {
	int weight;
	Elephant *next;
};

int* getNumsFromLine(int count) {
	char c;
	int* ptr = new int[count];
	int index = 0;
	int num = 0;	

	do {
		c = getc(stdin);
		if(c >= '0' && c <= '9') {
			num *= 10;
			num += c - '0';
		} else {
			*(ptr + index) = num;
			num = 0;
			index += 1;
			if(index >= count) break;
		}
	} while( c != '\n' );

	return ptr;
}

Elephant *getElephants(int *count, int *minWeight) {
	int index;
	int *order;
	int *target;
	int *weight;
	int *offset;

	*minWeight = 6501;

	scanf("%d", count);
	getc(stdin);

	Elephant *elephants = new Elephant[*count];
	weight = getNumsFromLine(*count);
	order = getNumsFromLine(*count);
	target = getNumsFromLine(*count);

	offset = new int[*count];
	for(int i = 0; i < *count; i++) {
		index = *(order + i) - 1;
		offset[index] = i;
		if(*minWeight > *(weight + index)) *minWeight = *(weight + index);
		elephants[i].weight = *(weight + index);
	}

	for(int i = 0; i < *count; i++) {
		index = *(target + i) - 1;
		index = offset[index];
		elephants[index].next = &elephants[i];
	}

	delete [] offset;
	delete [] target;
	delete [] order;
	delete [] weight;

	return elephants;
}

int main() {
	int count;
	unsigned int result = 0;

	int method1, method2;
	int minWeight;
	int cycleSize;
	int cycleCost;
	int cycleMin;

	Elephant *start;
	Elephant *ptr;
	Elephant *temp;
	Elephant *elephants;

	elephants = getElephants(&count, &minWeight);

	for(int i = 0; i < count; i++) {
		start = &elephants[i];
		ptr = elephants[i].next;
		cycleCost = 0;
		cycleMin = 6500;
		cycleSize = 1;
		while(start != ptr) {
			cycleCost += ptr->weight;
			if(cycleMin > ptr->weight) cycleMin = ptr->weight;
			temp = ptr;
			ptr = ptr->next;
			temp->next = temp;
			cycleSize += 1;
		}

		if(cycleCost != 0) {
			cycleCost += start->weight;
			if(cycleMin > start->weight) cycleMin = start->weight;
			// printf("Cycle cost: %d\n", cycleCost);
			// printf("Cycle min: %d\n", cycleMin);
			// printf("Cycle count: %d\n", cycleSize);
			// printf("Min weight: %d\n\n", minWeight);
			method1 = cycleCost + (cycleSize - 2) * cycleMin;
			method2 = cycleCost + cycleMin + (cycleSize + 1) * minWeight;
			result += (method1 < method2) ? method1 : method2;
		}
	}

	delete [] elephants;

	printf("%u\n", result);

	return 0;
}
