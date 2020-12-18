#include "SimpleMedian.h"

int compare(const void * a, const void * b){ /*For Quick-Sort. See: https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/*/
	double A = *(double*) a;
	double B = *(double*) b;
	if(A<B){
		return -1;//Element A goes before B
	}else if(B<A){
		return 1;//Element B goes before A
	}else{
		return 0;//Elements A and B are equivalent
	}
}

double median(double* buffer, int lenBuffer){
	qsort(buffer, lenBuffer, sizeof(double), compare);
	int middle = lenBuffer/2;
	if(lenBuffer%2==0){
		return (buffer[middle] + buffer[middle-1])/2.0;
	}else{
		return buffer[middle];
	}
}
