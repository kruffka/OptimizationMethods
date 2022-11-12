#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3
#define M N*N

typedef struct T_vertex {
	int num;
	int weightEdge;
	struct T_vertex *next;
}Tvertex;

int initGraf() {
	FILE* file;
	int edges = 0, g[N][N], i, j;

	if ((file = fopen("input.txt", "w+")) == NULL) {
		printf("Error opening file\n");
		return 0;
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
	return 1;
}

int main() {

	FILE* file;
	int endV = 0, V = 0, E = 0, i, j, currentStep, lastStep, numV, breakF;
	int buffer[3],*d, *trueWay, *colorV, *queue;	
	Tvertex **graph, *p, *hp;

	if (!initGraf()) {
		printf("Error opening file\n");
		return 0;
	}

	if ((file = fopen("input.txt", "r+")) == NULL) {
		printf("Error opening file\n");
		return 0;
	}
	//Init DATA
	fscanf(file, "%d %d %d", &V, &E, &endV);
	printf("V = %d; E = %d;\nendV = %d;\n", V, E, endV);
	graph = (Tvertex**)malloc(V * sizeof(Tvertex*));
	d = (int*)malloc(V * sizeof(int));
	trueWay = (int*)malloc(V * sizeof(int));
	colorV = (int*)malloc(V * sizeof(int));
	queue = (int*)malloc(V * sizeof(int));
	for (i = 0; i < V; i++) {
		graph[i] = NULL;
		d[i] = 0;
		trueWay[i] = -1;
		colorV[i] = -1;
		queue[i] = -1;
	}	
	for (i = 0; i < E; i++) {
		fscanf(file, "%d %d %d", &buffer[0], &buffer[1], &buffer[2]);
		if (graph[buffer[0]] != NULL) {
			p = graph[buffer[0]];			
			while (p->next != NULL) {
				p = p->next;
			}
			hp = (Tvertex*)malloc(sizeof(Tvertex));
			hp->next = NULL;
			hp->num = buffer[1];
			hp->weightEdge = buffer[2];
			p->next = hp;
		}
		else {			
			graph[buffer[0]] = (Tvertex*)malloc(sizeof(Tvertex));
			graph[buffer[0]]->next = NULL;
			graph[buffer[0]]->num = buffer[1];
			graph[buffer[0]]->weightEdge = buffer[2];			
		}		
	}	
	//--
	//printf DATA		
	/*for (i = 0; i < V; i++) {
		printf("%2d|\t", i);
		if (graph[i] == NULL)
			continue;
		p = graph[i];
		while (p != NULL) {
			printf("%d(%d); ", p->num, p->weightEdge);
			p = p->next;
		}
		printf("\n");
	}*/
	//--
	//Algoritm
	currentStep = 0;
	lastStep = 1;
	queue[currentStep] = 0;
	breakF = 0;
	while (queue[currentStep] != -1){
		numV = queue[currentStep];
		if (graph[numV] == NULL) {
			if (currentStep+1 < lastStep)				
				currentStep++;
			else
				break;
		}
		p = graph[numV];
		while (p != NULL){			
			if (colorV[p->num] == -1) {
				colorV[p->num] = numV;
				d[p->num] = d[numV] + p->weightEdge;
				queue[lastStep] = p->num;
				lastStep++;
			}
			else {
				if (colorV[endV] != -1) {
					breakF = 1;
					break;
				}
			}
			p = p->next;
		}
		if (breakF)
			break;
		currentStep++;
	}
	//--
	//Printf Result
	/*printf("\nd: ");
	for (i = 0; i < V; i++)
		printf("%d; ", d[i]);
	printf("\nWay: ");
	for (i = 0; i < V; i++)
		printf("%d; ", way[i]);
	printf("\nColor: ");
	for (i = 0; i < V; i++)
		printf("%d; ", colorV[i]);*/

	printf("\nThe shortest length = %d;\n", d[endV]);
	printf("Way: ");
	//revers Way
	i = endV;
	trueWay[0] = endV;
	j = 1;
	while (i != 0) {
		trueWay[j++] = colorV[i];
		i = colorV[i];
	}
	for (i = 0; i < (int)(j / 2); i++) {
		endV = trueWay[i];
		trueWay[i] = trueWay[j - 1 - i];
		trueWay[j - 1 - i] = endV;
	}
	//--
	for (i = 0; i < j; i++)
		printf("%d ", trueWay[i]);
	//--
	//Free memory
	for (i = 0; i < V; i++) {		
		if (graph[i] != NULL){
			p = graph[i];
			if (p->next != NULL) {
				while (p != NULL) {
					hp = p->next;					
					free(p);
					p = hp;
				}
			}
		}
	}
	free(graph);
	free(d);
	free(trueWay);
	free(colorV);
	free(queue);
	fclose(file);

	printf("\n");
	return 0;
}