#include <stdio.h>

#define N 8
#define min(a, b) (a < b ? a : b)

int main() {
    
    freopen("king2.in", "r", stdin);
    freopen("king2.out", "w", stdout);

    int arr[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for (int i = 6; i > -1; i--)
        arr[i][0] = arr[i+1][0] + arr[i][0];
    for (int i = 1; i < 8; i++)
        arr[7][i] = arr[7][i-1] + arr[7][i];
 
    for (int i = 6; i > -1; i--)
        for (int j = 1; j < 8; j++) {
            arr[i][j] = min(min(arr[i+1][j-1] + arr[i][j], arr[i+1][j] + arr[i][j]), arr[i][j-1] + arr[i][j]);

        }

    printf("%d", arr[0][N-1]);
    
    return 0;
}
