#include <stdio.h>

#define max(a, b) (a > b ? a:b)

int main() {

    freopen("ladder.in", "r", stdin);
    freopen("ladder.out", "w", stdout);

    char n;
    scanf("%hhd", &n);
    int max_sum[n];
    short step[n];

    for (int i = 0; i < n; i++) {
        scanf("%hd", &step[i]);
    }

    max_sum[0] = step[0];
    
    if (n > 1)
        max_sum[1] = max(step[1] + max_sum[0], step[1]);
    else
        max_sum[n] = 0;
 
    for (int jump = 2; jump < n; jump++)
        max_sum[jump] = step[jump] + max(max_sum[jump-1], max_sum[jump-2]);
    
    printf("%d", max_sum[n-1]);
    return 0;
}
