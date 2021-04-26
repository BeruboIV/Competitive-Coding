long long mulmod(long long a, long long b, long long MOD){
	long long x = 0, y = a%MOD;
	while(b > 0){
		if(b&1)
			x = (x + y)%MOD;
		y = (y*2LL)%MOD;
		b >>= 1;
	}
	return x%MOD;
}

long long binpow(long long x,long long n, long long MOD){
    long long result = 1;
    while(n > 0){
        if(n&1)
            result = mulmod(result, x, MOD);
        x = mulmod(x, x, MOD);
        n >>= 1;
    }
    return result%MOD;
}

bool isPrime(long long n , int iterations = 5){
    if(n <= 4)
        return (n == 2 || n == 3);
 
    for(int i = 1; i <= iterations; i++){
        long long a = 2 + rand() % (n - 3);
        long long res = binpow(a , n - 1 , n);
 
        if(res != 1) 
            return false;
    }
 
    return true;
}

void solve(){
    long long n;
    cin >> n;
    if(isPrime(n))
        cout << "YES\n";
    else
        cout << "NO\n";
}