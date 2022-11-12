#include <stdio.h>

#define max(a, b) (a > b ? a : b)

int main() {

  freopen("lepus.in", "r", stdin);
  freopen("lepus.out", "w", stdout);

  short int n;
  scanf("%d", &n);

  char s[n];
  int line[n];
  scanf("%s", s);

  for(int i = 0; i < n; i++) line[i] = -1;

  line[0] = 0;

  for (int i = 0; i < n; ++i) {
    if (line[i] != -1) {
      for (int j = 1; j <= 5; j += 2) {
        if (j <= n - 1 - i && s[i + j] != 'w') { // если не болото и не вышли за границу
          int is_grass = s[i + j] == '"';
          line[i + j] = max(line[i + j], line[i] + is_grass);
        }
      }
    }
  }

  printf("%d\n", line[n - 1]);
}