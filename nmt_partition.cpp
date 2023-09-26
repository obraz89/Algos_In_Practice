#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "nmt_partition.h"

#include <time.h>

int max(int v1, int v2) {
	if (v1 > v2) return v1;
	return v2;
}

int solve_t(const int v[], const int nv, int t) {
	int* last_v = new int[nv];
	if (t == 0) return 0;

	for (int j = 0; j < nv; j++) {
		if (t >= v[j]) {
			last_v[j] = solve_t(v, nv, t - v[j]);
		}
		else {
			last_v[j] = -1;
		}
	}

	int res = -1;

	for (int j = 0; j < nv; j++) {
		res = max(res, last_v[j]);
	}
	delete[] last_v;
	
	if (res >= 0) {
		return res + 1;
	}
	else {
		return res;
	}
}

void solve(const int v[], const int nv, int t) {
	int res, i;
	res = solve_t(v, nv, t);
	if (res >= 0)
		printf("Res:%d", res);
	else {
		i = t - 1;
		res = solve_t(v, nv, i);
		while (res < 0) {
			i--;
			res = solve_t(v, nv, i);
		}
		printf("Res:%d, time remain %d", res, t - i);
	}
}

int nmt_partition_main() {
	int v[2] = { 4, 9 };
	int num;
	scanf("%d", &num);
	printf("Partition for %d", num);
	time_t start_t, end_t;
	time(&start_t);
	solve(v, 2, num);
	time(&end_t);
	double dt = difftime(end_t, start_t);
	printf("Elapsed %lf", dt);
	return 0;
}