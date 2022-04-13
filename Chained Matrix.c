#include <stdio.h>

int Matrix[300][2];
int Dp[300][300];

int Matrix_Chain(int n) {
    int a, b;
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            a = j;
            b = j + i;
            if (a == b) {
                Dp[a][b] = 0;
            }
            else {
                Dp[a][b] = 999999999; // 지속적으로 더 작은 값으로 바뀌기 위해 넣은 최대값
                for (k = a; k < b; k++) {
                    Dp[a][b] = Min(Dp[a][b], Dp[a][k] + Dp[k + 1][b] + (Matrix[a][0] * Matrix[k][1] * Matrix[b][1])); // DP의 점화식
                }
            }
        }
    }
    return Dp[0][n - 1]; // 최소 연산 횟수 반환
}

int Min(int x, int y )  // 더 작은 값을 반환하는 함수 Min
{
    return x < y ? x : y; // x가 y보다 크면 x return else y return
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &Matrix[i][0], &Matrix[i][1]);
    }
    printf("최소연산 횟수 = %d\n", Matrix_Chain(n));
}
