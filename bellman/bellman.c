#include <stdio.h>
#include <stdlib.h>


const int INF = 999;
const int LIMIT = 1000;
int i, j;
int* result;

int* FordBellman(int** C, int n, int start, int *W);
void PrintWay(int *W, int n, int start, int end);

int main(){
	FILE* input;
	int n;
	int start_vertex;
	
	if ((input = fopen("input.txt","r")) == NULL){
		printf("\tFile wasn't open!\n\n");
		return (-1);
	}
	else {
		printf("\tFile was open!\n\n");	
	}
	
	//read 2d-array
	fscanf(input, "%d", &n);
	
	int** a = (int**)malloc(n * sizeof(int**));
	for (i = 0; i < n; i++){
		a[i] = (int*)malloc(n * sizeof(int*));
	}
	int* w = (int*)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			fscanf(input, "%d", &a[i][j]);
		}
	}
	fclose(input);
	
	// print input graph
	printf("\tInput graph:\n");
	for (i = 0; i < n; i++){
		printf("\t");
		for (j = 0; j < n; j++){
			printf("%3d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	//init before ford-bellman
	printf("\tInit before Ford-Bellman\n");
	for (i = 0; i < n; i++){
		printf("\t");
		for (j = 0; j < n; j++){
			if (i != j && a[i][j] == 0){
				a[i][j] = INF;
			}
			a[i][j] != INF ? printf("%3d ", a[i][j]) : printf("INF ");
		}
		printf("\n");
	}
	printf("\n\n");
	
	printf("\tEnter start vertex (from %d to %d): ", 0, n - 1), scanf("%d", &start_vertex);
	for (i = 0; i < n; i++){
		w[i] = start_vertex;
	}
	
	result = FordBellman(a, n, start_vertex, w);
	
	for (i = 0; i < n; i++){
		printf("\tWay from %d to %d cost: %d\n", start_vertex, i, result[i]);
		printf("\tPath: ");
		PrintWay(w, n, start_vertex, i);
		printf("\n\n");
	}
	
	// free memory
	free(w);
	
	for (i = 0; i < n; i++){
		free(a[i]);
	}
	free(a);
	return 0;
}

int* FordBellman(int **C, int n, int Start, int *W) 
{
	int Step, i, j, k;
	int **D = new int *[2];
	
	for (i = 0; i < 2; i++) 
	{
		D[i] = new int [n];
		for (j = 0; j < n; j++)
			D[i][j] = INF;
	}
	
	D[0][Start] = 0;

	k = 1;
	int t = 0;
	
	for (Step = 1; Step < n; Step++) 
	{
		bool Changed = false;
		printf("\tCalculation cost, Step %d\n", Step);
		k = (++k) % 2;
		t = (k + 1) % 2;
		for (i = 0; i < n; i++)//obhod vertex
		{
			D[t][i] = D[k][i];
			for (j = 0; j < n; j++) //find minimum	
			{
				if (D[t][i] > D[k][j] + C[j][i]) 
				{ 
					D[t][i] = D[k][j] + C[j][i]; // recalculating cost of all vertices using the formula
					W[i] = j;
					Changed = true;
				}
	    	}
	    	printf("\t");
			if (D[t][i] > LIMIT){
				D[t][i] = INF;
			}
				printf("%3d ", D[t][i]);
		}
		if (!Changed){ //пока не всё стабилизировано
			printf("\n\n\tThe Value array stabilized in Step %d\n\n", Step);
			break;
		}
		printf("\n\n");
	}	
	return D[t];
}

void PrintWay(int *W, int n, int Start, int End){
	int i = End;
	while((i != Start)) {
		printf("%d<-", i);
		i = W[i];
	}
	printf("%d", i);
	return;
}