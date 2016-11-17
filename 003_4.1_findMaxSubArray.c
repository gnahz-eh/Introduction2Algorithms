#include<stdio.h>
#include<limits>
typedef struct backData{
	int left;
	int right;
	int sum;
}returnType;


returnType find_max_crossing_subArray(int a[], int low, int mid, int high) {
	int left_sum, right_sum;
	int sum;
	int max_left, max_right;

	sum = 0;
	left_sum = INT_MIN;//-9999;
	
	for(int i = mid; i >= low; i--) {
		sum = sum + a[i];
		
		if(sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	
	}

	right_sum = INT_MIN;//-9999;
	sum = 0;

	for(int j = mid + 1; j <= high; j++) {
		sum = sum + a[j];

		if(sum > right_sum) {
			right_sum = sum;
			max_right = j;
		}
	}

	returnType r = {max_left, max_right, left_sum + right_sum};
	return r;

}

returnType find_max_subArray(int a[], int low, int high) {

	if(high == low) {
		returnType r = {low, high, a[low]};
		return r;
	} else {
		
		int mid = (low + high) / 2;
		returnType left = find_max_subArray(a, low, mid);
		returnType right = find_max_subArray(a, mid + 1, high);
		returnType cross = find_max_crossing_subArray(a, low, mid, high);

		if(left.sum >= right.sum && left.sum >= cross.sum) {
			return left;	
		} else if (right.sum >= left.sum && right.sum >= cross.sum) {
			return right;
		} else {
			return cross;
		}
	}
}


void main() {
	
	int a[16];
	a[0] = 13; 
	a[1] = -3;
	a[2] = -25;
	a[3] = 20;
	a[4] = -3;
	a[5] = -16;
	a[6] = -23;
	a[7] = 18;
	a[8] = 20;
	a[9] = -7;
	a[10] = 12;
	a[11] = -5;
	a[12] = -22;
	a[13] = 15;
	a[14] = -4;
	a[15] = 7;

	returnType result = find_max_subArray(a, 0, 15);
	printf("左区间是：%d\n右区间是：%d\n总和是：%d\n", result.left, result.right, result.sum); 
}
