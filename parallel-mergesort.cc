/**
 *  \file parallel-mergesort.cc
 *
 *  \brief Implement your parallel mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.hh"

void
parallelSort (int N, keytype* A)
{
	mergesort(A, 0, N);
	//sequentialSort(N, A);

}

void mergesort(keytype* A, int p, int r) 
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergesort(A, p, q);
		mergesort(A, q + 1, r);	
		Pmerge(A, p, q, q+1, r, T,sorted);//!!!!!!!

	}

}
void Pmerge (keytype* T, int p1, int r1, int p2, int r2,keytype* A, int p3)
{
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2) {//ensure that n1>=n2
		exchange(p1, p2);
		exchange(r1, r2);
		exchange(n1, n2);
	}
	if (n1 == 0) return;
	else {
		int q1 = (p1 + r1) / 2;
		int q2 = BinarySearch(*(T + q1), T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		*(A + q3) = *(T + q1);
		Pmerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
	
	}


}

void exchange(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;

}
int BinarySearch(int x, keytype* T, int p, int r)
{
	int low = p;
	int high = (p >(r+1))? p:(r+1);	//max(p,r+1)
	while (low < high) {
		int mid = (low + high) / 2;
		if (x <= *(T + mid))
			high = mid;
		else low = mid + 1;
	}
	return high;
}
/* eof */