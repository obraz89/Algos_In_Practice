#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_SIZE 100
//#define _CRT_SECURE_NO_WARNINGS 1


int get_shortest_line_ind(int lines[], int nlines) {
	int shortest = 0;
	for (int i = 0; i< nlines; i++)
		if (lines[i] < lines[shortest]) shortest = i;
	return shortest;
}

void print_lines(int lines[], int nlines) {
	for (int i = 0; i < nlines; i++)
		printf("%d", lines[i]);
	printf("\n");
}

int food_main() {
	int lines[MAX_SIZE];

	int n, m;

	printf("Type in number of lines, number of ppl to come\n");

	scanf("%d%d", &n, &m);

	printf("Type in number of ppl in each line\n");

	for (int i = 0; i < n; i++) scanf("%d", &lines[i]);

	for (int i = 0; i < m; i++) {
		print_lines(lines, n);
		int s = get_shortest_line_ind(lines, n);
		lines[s]++;
	}

	getchar();

	return 0;
}