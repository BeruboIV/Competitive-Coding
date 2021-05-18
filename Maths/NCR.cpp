const long long N = 5e5, M = 1e9+7;
long long inv[N + 1], f1[N + 1], f2[N + 1];	// inv[n] = 1/n; f1[n] = n!; f2[n] = 1/(n!) 

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

// Use this approach for finding f2[n] if you don't want to use inv[n];

const long long N = 5e5, M = 1e9+7;
long long f1[N + 1], f2[N + 1];	// f1[n] = n!; f2[n] = 1/(n!),  

long long ncr(long long n, long long k) {
	return f1[n]*f2[k]%M*f2[n-k]%M;
}

ll binpow(ll x, ll n){
    ll result = 1;
    while(n > 0){
        if(n&1)
            result = (result * x)%M;
        x = (x*x)%M;
        n /= 2;
    }
    return result;
}

void init(){
	f1[0] = 1;
	for(ll i = 1; i <= N; i++)
		f1[i] = (f1[i - 1]*i)%M;

	f2[N] = binpow(f1[N], M - 2);
	for(ll i = N - 1; i >= 0; i--)
		f2[i] = (f2[i + 1]*(i + 1))%M;	// f2[i] = 1/i! = (i + 1) / (i + 1)! 
}