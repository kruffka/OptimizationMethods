#include <stdio.h>
#include <stdlib.h>

#define MAX_JUMP 5
#define N 15

int main(){

    int i, j, pos;
    int min, minPos, jump_num, tmp;

	int stone_num[N] = { 0, 1, 2, 3, 4, 5, 6, 8, 12, 13, 15, 17, 20, 21, 25 };
	
    printf("Input: ");
	for (i = 0; i < N; i++){
		printf("%d ", stone_num[i]);
	}
    printf("\n");
	
    // init
	const int last_stone = stone_num[N - 1];
	int stones[last_stone + 1];
	
	int table[last_stone + 1][MAX_JUMP + 1];
	for (i = 0; i <= last_stone; i++){
		for (j = 0; j <= MAX_JUMP; j++){
			table[i][j] = N;
		}
	}
	
	for (i = 0, j = 0; i <= last_stone; i++) {
		if (stone_num[j] == i) {
			stones[i] = stone_num[j];
			j++;
		}
		else{
			stones[i] = -1;
		}
	}

	table[1][1] = 1;

	for (pos = 2; pos <= last_stone; pos++) {
		if (stones[pos] == -1){
			continue;
		}
		for (i = 1; i <= MAX_JUMP; i++) {
			if (pos - i <= 0){
				continue;
			}
			min = N;			
			for (j = -1; j <= 1; j++) {
				if (((i + j) < 1) || ((i + j) > MAX_JUMP)){
					continue;
				}
				if ((table[pos - i][i + j] == N)){
					continue;
				}
				tmp = table[pos - i][i + j] + 1;				
				if (tmp < min) {
					min = tmp;
				}
			}
			if (min < table[pos][i])
				table[pos][i] = min;			
		}
	}
	

    
	for (i = 0; i <= MAX_JUMP; i++) {		
		printf("%d  ", i);
		for (j = 0; j <= last_stone; j++) {
			if (stones[j] == -1)
				continue;
			if (table[j][i] == N)
				printf("-  ");
			else
				printf("%d  ", table[j][i]);
		}
		printf("\n");
	}
	printf("\n");

	min = N;
	minPos = -1;
	for (i = MAX_JUMP; i > 0; i--) {
		if (table[last_stone][i] < min) {
			min = table[last_stone][i];
			minPos = i;
		}
	}		
	jump_num = min;	
	if (jump_num == N) {
		printf("Impossible to reach last stone\n");
		return 0;
	}		
	printf("Jumps: %d\n", jump_num);
		
	int frogPath[jump_num+1];
	for (i = 0; i <= jump_num; i++){
		frogPath[i] = -1;
	}
		
	tmp = jump_num;
	pos = last_stone;
	frogPath[jump_num] = pos;
	pos -= minPos;
	jump_num--;
	while (jump_num != -1) {
		min = N-1;
		minPos = -1;
		for (i = MAX_JUMP; i > 0; i--) {
			if (table[pos][i] == jump_num) {
				minPos = i;
				break;
			}
		}		
		frogPath[jump_num] = pos;
		jump_num--;
		pos -= minPos;
	}
	jump_num = tmp;
	printf("Path: ");
	for (i = 0; i <= jump_num; i++){
        if (i != jump_num)
		    printf("%d->", frogPath[i]);
        else 
            printf("%d", frogPath[i]);
	}
	printf("\n");
	
	return 0;
}