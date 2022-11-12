#include <stdio.h>

int main() {
    
    freopen("knight.in", "r", stdin);
    freopen("knight.out", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);
    int desk[n][m];
     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            desk[i][j] = 0;
        }
    }

    desk[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + 1) < n && (j + 2) < m)
                desk[i + 1][j + 2] = desk[i][j] + desk[i + 1][j + 2];
            if ((i + 2) < n && (j + 1) < m)
                desk[i + 2][j + 1] = desk[i][j] + desk[i + 2][j + 1];
        }
    }
        
    printf("%d", desk[n-1][m-1]);
    
    return 0;
}
