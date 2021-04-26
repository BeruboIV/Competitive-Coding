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