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

// Faster Method
int32_t mul(int64_t a, int32_t b){
    return a * b % M;
}

int32_t add(int32_t a, int32_t b){
    int32_t res = a + b;
    if(res >= M)
        res -= M;
    return res;
}

int32_t sub(int32_t a, int32_t b){
    int32_t res = a - b;
    if(res < 0)
        res += M;
    return res;
}

int32_t binpow(int32_t x, int64_t n)
{
    int64_t result = 1;
    while(n > 0)
    {
        if(n & 1)
            result = mul(result, x);
        x = mul(x, x);
        n >>= 1;
    }
    return result;
}