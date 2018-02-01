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
#include <omp.h>
#include "sort.hh"

void exchange(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;

}


int BinarySearch(int x, keytype* T, int p, int r)
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

void Pmerge(keytype* T, int p1, int r1, int p2, int r2, keytype* A, int p3)
{
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2) {
		exchange(p1, p2);
		exchange(r1, r2);
		exchange(n1, n2);
	}
	if (n1 == 0) return;
	else {
		int q1 = (p1 + r1) / 2;
		int q2 = BinarySearch(T[q1], T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		A[q3] = T[q1];
		#pragma omp parallel sections
		{
#pragma omp section
			Pmerge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
#pragma omp section
			Pmerge(T, q1 + 1, r1, q2, r2, A, q3 + 1); 
		
		}
	}


}

void Pmergesort(keytype* A, int p, int r, keytype* B, int s)
{

	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	}
	else {
		keytype* T = newKeys(n);
		int q = (p + r) / 2;
		int qt = q - p + 1;
		#pragma omp task
		Pmergesort(A, p, q, T, 1);
		Pmergesort(A, q + 1, r, T, qt + 1);
		#pragma omp taskwait
		#pragma omp parallel sections
		{
			#pragma omp section
			Pmergesort(A, p, q, T, 1);
			#pragma omp section
			Pmergesort(A, q + 1, r, T, qt + 1); 
		}
		Pmerge(T, 1, qt, qt + 1, n, B, s);
	}

}


void parallelSort(int N, keytype* A)
{
	#pragma omp parallel num_threads(64);
	keytype* B = newKeys(N);
	B = A;
	#pragma omp parallel{
		#pragma omp single
		Pmergesort(B, 0, N - 1, A, 0);	
	}
	
	#pragma omp parallel
	Pmergesort(B, 0, N - 1, A, 0);

}