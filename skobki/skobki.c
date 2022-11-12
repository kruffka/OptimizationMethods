#include <stdio.h>

#define N 10
#define SIZE N-1

void skobki(int(*g)[N], int min, int max);

int main(void) {

	// int r[] = {10, 20, 50, 1, 100};
	// int r[] = {10, 20, 5, 4, 30, 6};
	int r[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

	int optim = 0, min = 9999999;
	int f[N][N] = {0};
	int g[N][N] = {0};

	for (int i = 0; i < SIZE; i++) {
		printf("M%d [%d*%d] ", i + 1, r[i], r[i+1]);
	}
	printf("\n");

	for (int t = 1; t < SIZE; t++) {
		for (int k = 1; k < SIZE; k++) {
			if (k + t <= SIZE) {
				for (int j = k; j < k + t; j++) {
					int optim = f[k][j] + f[j + 1][k + t] + r[k - 1] * r[j] * r[k + t];
					if (j == k)
					{
						min = optim;
						g[k][k + t] = j;
					}

					if (j != k && optim < min)
					{
						min = optim;
						g[k][k + t] = j;
					}
				}

				f[k][k + t] = min;
			}
		}
	}


	for(int i = 0; i <= SIZE; i++) {
		for(int j = 0; j <= SIZE; j++) {
			printf("%d\t", f[i][j]);
		}
		printf("\n");
	}


	skobki(g, 1, SIZE);

	printf("\n");

	return 0;
}

void skobki(int(*g)[N], int min, int max) {
	
	if (max - min == 0) {
		printf("M%d", min);
		return;
	} else if (max - min == 1) {
		printf("(M%d * M%d)", min, max);
		return;
	} else {
		printf("( ");
		skobki(g, min, g[min][max]);
		skobki(g, g[min][max] + 1, max);
		printf(" )");
	}
}
