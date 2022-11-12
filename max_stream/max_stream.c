#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M N*N

int min_func(int a, int b) {
	if (a < b)
		return a;
	return b;
}

char str[] = "sopqrt";

int findPath(int **table, int *v_is, int u, int t, int f, int V) {
	
	// нашли путь, можно пустить f потока
	if (u == t)
		return f;

	int v, diff;

	v_is[u] = 1;
	for (v = 0; v < V; v++) {
		if ((!v_is[v]) && (table[u][v] > 0)) {
			diff = findPath(table, v_is, v, t, min_func(f, table[u][v]), V);
			if (diff > 0) {
				// нашли путь по которому можно пустить x потока
				table[u][v] -= diff;
				table[v][u] += diff;
				printf("%c -> ", str[v]);

				return diff;
			}
		}	

	}

	// не существует пути из v в t
	
	return 0;
}

int maxFlow(int **table, int s, int t, int V) {

	int flow, diff, *v_is, i;

	v_is = (int*)malloc(V * sizeof(int));
	for (i = 0; i < V; i++)
		v_is[i] = 0;

	for (flow = 0;;) {
		diff = findPath(table, v_is, s, t, 9999999, V);
		if (diff == 0)
			return flow;
		printf("%c", str[0]);
		printf("\nFlow = %d\n", diff);
		flow += diff;

	}
	free(v_is);
}

void init_input() {

	FILE* file;
	int edges = 0, **g, i, j;

	if ((file = fopen("input.txt", "w+")) == NULL) {
		printf("Error opening file\n");
		exit(1);
	}
	edges = 2 * ((N - 1) * N);
	fprintf(file, "%d %d %d\n", M, edges, M - 1);
	edges = 0;
	g = (int**)malloc(N * sizeof(int*));
	for (i = 0; i < N; i++) {
		g[i] = (int*)malloc(N * sizeof(int));
		for (j = 0; j < N; j++) {
			g[i][j] = edges++;
			//printf("%2d ", g[i][j]);
		}
		//printf("\n");
	}
	edges = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (j + 1 < N) {
				edges++;
				fprintf(file, "%d %d %d\n", g[i][j], g[i][j + 1], 1);
			}
			if (i + 1 < N) {
				edges++;
				fprintf(file, "%d %d %d\n", g[i][j], g[i + 1][j], 1);
			}
		}
	}
	// fprintf(file, "%d %d %d\n", 0, 3, 1);

	fclose(file);

	for (i = 0; i < N; i++) {
		free(g[i]);
	}
	free(g);
}

int main() {
	
	FILE* file;
	int endV = 0, V = 0, E = 0, i, j;
	int buffer[3], *trueWay;
	int **table;

	// init_input();

	if ((file = fopen("input2.txt", "r+")) == NULL) {
		printf("Error opening file\n");
		return 0;
	}

	fscanf(file, "%d %d %d", &V, &E, &endV);
	printf("V = %d; E = %d;\nendV = %d;\n", V, E, endV);
	table = (int**)malloc(V * sizeof(int*));
	trueWay = (int*)malloc(V * sizeof(int));
	for (i = 0; i < V; i++) {
		trueWay[i] = -1;
		table[i] = (int*)malloc(V * sizeof(int));
		for (j = 0; j < V; j++) {
			table[i][j] = 0;
		}
	}
	for (i = 0; i < E; i++) {
		fscanf(file, "%d %d %d", &buffer[0], &buffer[1], &buffer[2]);
		table[buffer[0]][buffer[1]] = buffer[2];		
	}
	fclose(file);

	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			printf("%2d ", table[i][j]);
		}
		printf("\n");
	}


	int result = 0, flow = 1;

	while (flow != 0) {
		flow = maxFlow(table, 0, endV, V);
		result += flow;
	}
	

	printf("\n\nMax flow = %d\n", result);

	free(table);
	free(trueWay);

	printf("\n");
	return 0;
}