// (x ^ n)
long long binpow(long long x,long long n){
    long long result = 1;
    while(n > 0)
    {
        if(n&1)
            result = (result * x);
        x = (x * x);
        n /= 2;
    }
    return result;
}

// (x ^ n) % M

long long binpow(long long x,long long n, long long M){
    long long result = 1;
    while(n > 0)
    {
        if(n&1)
            result = (result * x) % M;
        x = (x * x) % M;
        n /= 2;
    }
    return result;
}