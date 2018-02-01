/**
*  \file parallel-mergesort.cc
*
*  \brief Implement your parallel mergesort in this file.
*/
//Jan.30.2018

// lai man tang, yuan qin
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.hh"

void mexchange(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;

}


int mBinarySearch(int x, keytype* T, int p, int r)
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

void merge(keytype* T, int p1, int r1, int p2, int r2, keytype* A, int p3)
{
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2) {
		mexchange(p1, p2);
		mexchange(r1, r2);
		mexchange(n1, n2);
	}
	if (n1 == 0) return;
	else {
		int q1 = (p1 + r1) / 2;
		int q2 = mBinarySearch(T[q1], T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		A[q3] = T[q1];
		merge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
		merge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
	}


}

void mergesort(keytype* A, int p, int r, keytype* B, int s)
{

	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	}
	else {
		keytype* T = newKeys(n);
		int q = (p + r) / 2;
		int qt = q - p + 1;
		mergesort(A, p, q, T, 1);
		mergesort(A, q + 1, r, T, qt + 1);
		merge(T, 1, qt, qt + 1, n, B, s);
	}

}


void mSort(int N, keytype* A)
{

	keytype* B = newKeys(N);
	B = A;
	mergesort(B, 0, N - 1, A, 0);

}