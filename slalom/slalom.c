#include <stdio.h>

#define max(a, b) (a > b ? a:b)
 
int main() {

    freopen("slalom.in", "r", stdin);
    freopen("slalom.out", "w", stdout);

    int n, i, j;
    scanf("%d", &n);
    int a[100][100];
    scanf("%d", &a[0][0]);
    
    for (i = 1; i < n; i++) {
        for (j = 0; j <= i; j++) {
            scanf("%d", &a[i][j]);
            if (j == 0)
                a[i][0] += a[i-1][0];
            else if (j == i)
                a[i][j] += a[i-1][j-1];
            else 
                a[i][j] += max(a[i-1][j-1], a[i-1][j]);
        }
    }
    
    i = n - 1;
    short int ans = a[i][0];
    for (j = 1; j < n; j++) {
        if (a[i][j] > ans)
            ans = a[i][j];
    }
    printf("%d", ans);
    return 0;
}