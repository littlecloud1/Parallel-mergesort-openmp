// mergesort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void exchange(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;

}


int BinarySearch(int x, int* T, int p, int r)
{
	int low = p;
	int high = (p >(r + 1)) ? p : (r + 1);	//max(p,r+1)
	while (low < high) {
		int mid = (low + high) / 2;
		if (x <= *(T + mid))
			high = mid;
		else low = mid + 1;
	}
	return high;
}

void Pmerge(int* T, int p1, int r1, int p2, int r2, int* A, int p3)
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
		Pmerge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
		Pmerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
	}


}

void Pmergesort(int* A, int p, int r, int* B, int s)
{

	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	}
	else {
		int* T = (int*)malloc(n * sizeof(int*));
		int q = (p + r) / 2;
		int qt = q - p + 1;
		Pmergesort(A, p, q, T, 1);
		Pmergesort(A, q + 1, r, T, qt + 1);
		Pmerge(T, 1, qt, qt + 1, n, B, s);
	}

}


void parallelSort(int N, int* A)
{

	int* B = (int*)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++) {
		B[i] = 0;
	}
	Pmergesort(A, 0, N, B, 0);
	//sequentialSort(N, A);

}

int main()
{
	int A[13] = { 4, 6, 7, 2, 4, 6, 3, 21, 435, 123, 43534, 213, 443 };
	parallelSort(13, A);
	for (int i = 0; i < 13; i++) {
		printf("%d ", A[i]);
	}
	return 0;
}

