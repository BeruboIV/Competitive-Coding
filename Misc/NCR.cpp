const long long N = 5e5, M = 1e9+7;
long long inv[N + 1], f1[N + 1], f2[N + 1];

long long ncr(long long n, long long k) {
        return f1[n]*f2[k]%M*f2[n-k]%M;
}

void init(){
	inv[1]=1;
    for(long long i = 2; i <= N; ++i)
            inv[i] = M-M/i*inv[M%i]%M; //inv[i] = (1/i)%M 
    f1[0] = f2[0] = 1;
    for(long long i = 1; i <= N; ++i) {
            f1[i] = f1[i-1] * i % M; //f1[i] = i!%M
            f2[i] = f2[i-1] * inv[i] % M; //f2[i] = (1/i!)%M
    }
}