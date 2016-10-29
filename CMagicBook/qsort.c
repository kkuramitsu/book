#include "mymagic.h"

int a[10] = {
9, 1, 3, 7, 0, 5, 4, 2, 8, 6
};

void p(int a[], int n) {
        for(int i = 0; i < n; i++) {
                printf("%d ", a[i]);
        }
        printf("\n");
}

void swap(int a[], int b[])
{
	int temp = a[0];
	a[0] = b[0];
	b[0] = temp;
}

int rightindex(int a[], int left, int right, int pivot)
{
	for(int i = right; i >= left; i--) {
		if(a[i] < pivot) {
			return i;
		}
	}
	return -1;
}

void quicksort(int a[], int left, int right) 
{
	if(right - left < 2) {
		return ;
	}
	int pivot = a[right-1];
	int mid = right-1;
	for(int i = left; i < right; i++) {
		if(a[i] < pivot) {
			continue;
		}
		assert(a[i] >= pivot);
		mid = rightindex(a, i+1, mid, pivot);
		if(mid == -1) {
			mid = i;
			break;
		}
		swap(&a[i], &a[mid]);
	}
	//assert(a[mid] >= pivot);
	if(mid != right && !(mid - left < 2)) {
		quicksort(a, left, mid);
	}
	if(mid != left && !(right - mid < 2)) {
		quicksort(a, mid, right);
	}
}

int main()
{
	quicksort(a, 0, 10);
	p(a, 10);
}
