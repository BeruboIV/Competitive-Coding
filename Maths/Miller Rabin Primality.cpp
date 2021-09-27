const int N = 1e9;

int64_t pro(int64_t a,int64_t b,int64_t mod){
    if(a < N && b < N)
        return (a * b) % mod;
    if(b == 0 || a == 0)
        return 0;
    if(b == 1)
        return a % mod;
    else if(b % 2 == 0)
        return pro( (a + a) % mod, b / 2, mod);
    else if(b % 2 == 1)
        return (a + pro( (a + a) % mod, b / 2, mod) ) % mod;
    return -1;
}

int64_t binpow(int64_t p, int64_t q, int64_t mod){
    int64_t result = 1;
    while(q > 0){
        if(q&1)
            result = pro(result, p, mod);
        q >>= 1;
        p = pro(p, p, mod);
    }
    return result;
}

int test(int64_t n,int64_t d,int r){
    int64_t y, a = rand()%(n-4) + 2;
    y = binpow(a, d, n);
    if(y == 1 || y == n-1)
        return 1;
    while(r > 1){
        y = pro(y,y,n);
        r--;
        if(y == 1)
            return 0;
        else if(y == n-1)
            return 1;
    }
    return 0;
}

int mill(int64_t n,int iterations = 5)
{
    if(n == 1)
        return 0;
    else if(n <= 3)
        return 1;
    else if(n % 2 == 0)
        return 0;
    else{
        int i,r = 0;
        int64_t d = n-1;
        while(d % 2==0){
            d /= 2;
            r++;
        }
        for(i = 0; i < iterations; i++){
            if(test(n, d, r) == 0)
                return 0;
        }
        return 1;
    }
    return -1;
}

void solve(){
    int64_t n;
    cin >> n;
    bool isPrime = mill(n, 5);
    cout << isPrime << "\n";
}