ll mod = 1e9 + 7;

vvl c(n + 1);
for (int i = 0; i <= n; i++)
    c[i].resize(n + 1), c[i][0] = c[i][i] = 1;
for (int i = 0; i <= n; i++)
    for (int j = 1; j < i; j++)     
        c[i][j] = c[i-1][j] + c[i-1][j-1], c[i][j] %= mod;