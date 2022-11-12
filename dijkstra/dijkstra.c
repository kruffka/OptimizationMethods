#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M N*N

void init_input() {
	FILE* file;
	int edges = 0, g[N][N], i, j;

	if ((file = fopen("input.txt", "w+")) == NULL) {
		printf("Error opening file\n");
		exit(1);
	}	
	edges = 2 * ((N - 1) * N);
	fprintf(file, "%d %d %d\n", M, edges, M - 1);
	edges = 0;
	for (i = 0; i < N; i++) {
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
				fprintf(file, "%d %d %d\n", g[i][j], g[i+1][j], 1);
			}			
		}
	}
	fclose(file);
}

int main() {

	FILE *fileInput;
    int endV = 0, V = 0, E = 0;

    init_input();

	if ((fileInput = fopen("input.txt", "r+")) == NULL) {
		printf("Error opening file\n");
		return 0;
	}

	fscanf(fileInput, "%d %d %d", &V, &E, &endV);

	int **weightV, *d, *way, *trueWay, *colorV;
	int buffer[3], i, j;

    weightV = (int **)malloc(sizeof(int *)*V);
    d = (int *)malloc(sizeof(int)*V);
    way = (int *)malloc(sizeof(int)*V);
    trueWay = (int *)malloc(sizeof(int)*V);
    colorV = (int *)malloc(sizeof(int)*V);
	for (i = 0; i < V; i++) {
        weightV[i] = (int *)malloc(sizeof(int)*V);
		d[i] = 99999;
		way[i] = -1;
		trueWay[i] = -1;
		colorV[i] = 0;
		for (j = 0; j < V; j++) {
			weightV[i][j] = 0;
		}
	}
	for (i = 0; i < E; i++) {		
		fscanf(fileInput, "%d %d %d", &buffer[0], &buffer[1], &buffer[2]);		
		weightV[buffer[0]][buffer[1]] = buffer[2];
		weightV[buffer[1]][buffer[0]] = buffer[2];
	}

	printf("V = %d; E = %d;\nendV = %d;\n", V, E, endV);
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			printf("%2d ", weightV[i][j]);
		}
		printf("\n");
	}


	d[0] = 0;
	for (i = 0; i < V; i++) {
		if (i == endV) {
			continue;
		}
		colorV[i] = 1;
		for (j = 0; j < V; j++) {
			if ((weightV[i][j] == 0) || (colorV[j] == 1)) {
				continue;
			}
			if (d[j] >= d[i] + weightV[i][j]) {
				d[j] = d[i] + weightV[i][j];
				way[j] = i;
			}
		}
		
	}

	// Result
	printf("\nd: ");
	for (i = 0; i < V; i++)
		printf("%d; ", d[i]);
	printf("\nWay: ");
	for (i = 0; i < V; i++)
		printf("%d; ", way[i]);
	printf("\nColor: ");
	for (i = 0; i < V; i++)
		printf("%d; ", colorV[i]);

	printf("\nWay: ");
	
    // Way
	i = endV;
	trueWay[0] = endV;
	j = 1;
	while (way[i] != -1) {
		trueWay[j++] = way[i];
		i = way[i];
	}	
	for (i = 0; i < (int)(j / 2); i++) {
		endV = trueWay[i];
		trueWay[i] = trueWay[j - 1 - i];
		trueWay[j - 1 - i] = endV;
	}

	for (i = 0; i < j; i++)
		printf("%d ", trueWay[i]);

	printf("\n");

    for(int i = 0; i < V; i++) {
        free(weightV[i]);
    }
    free(weightV);
    free(d);
    free(way);
    free(trueWay);
    free(colorV);
	return 0;
}