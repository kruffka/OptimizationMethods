#include <stdio.h>
 
#define max(a, b) ((a > b) ? a : b)


 
int main() {
    int N = 4;
    int S = 20;
    int max = 0;

    // freopen("knapsack.in", "r", stdin);
    // freopen("knapsack.out", "w", stdout);

    scanf("%d %d", &S, &N);
    N++;
    S++;
    int backpack[N];
    backpack[0] = 0;
    for (int i = 1; i < N; i++) {
        scanf("%d", &backpack[i]);
    }

    int dp[N][S];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < S; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < S; j++) {
            dp[i][j] = dp[i-1][j];
            if ((backpack[i] <= j) && (dp[i-1][j-backpack[i]] == 1)){
                dp[i][j] = 1;
            }
        }
    }
    
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < S; j++) {
    //         printf("%d ", dp[i][j]);
    //     }printf("\n");
    // }
    for (int j = S-1; j > -1; j--) {
        if (dp[N-1][j] == 1) {
            max = j;
            break;
        }
    }
    printf("%d", max);
    

    return 0;
}