#include <stdio.h>

int matrix[501][2];
int dp[501][501];
int mat(int n);

int Matrix_Chain(int n) {
    int a, b;
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            a = j;
            b = j + i;
            if (a == b) {
                dp[a][b] = 0;
            }
            else {
                dp[a][b] = 987654321; // 무한대
                for (k = a; k < b; k++) {
                    dp[a][b] = min(dp[a][b], dp[a][k] + dp[k + 1][b] + (matrix[a][0] * matrix[k][1] * matrix[b][1]));
                }
            }
        }
    }
    return dp[0][n - 1];
}

int min(int x, int y) {
    return x < y ? x : y; // 최소값
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &matrix[i][0], &matrix[i][1]);
    }
    int ans = Matrix_Chain(n);
    printf("최소연산 횟수 : %d\n", ans);
}