long long mod_add(long long a, long long b, long long modulo = 1e9 + 7){
    long long res = (a + b) % modulo;
    while(res < 0)
        res += modulo;
    return res;
}

long long mod_mul(long long a, long long b, long long modulo = 1e9 + 7){
    long long res = (a * b % modulo);
    while(res < 0)
        res += modulo;
    return res;
}

long long mod_sub(long long a, long long b, long long modulo = 1e9 + 7){
    long long res = (a - b) % modulo;
    while(res < 0)
        res += modulo;
    return res;
}

// 0-based indexing is followed here
class Hashing{
    long long N = 2e5;
    long long MOD = 1e9 + 7;
    long long PRIME = 31; // Prime numebr just greater than number of characters
    vector<long long> hash_val, inv;  // inv[i] = 1/(PRIME^i)
public:

    Hashing(){
    }


    Hashing(string str){
        N = str.size();
        hash_val.resize(N + 1, 0);
        inv.resize(N + 1, 0);
        init(str);
    }

    Hashing(string str, long long MOD, long long PRIME)
        :MOD(MOD), PRIME(PRIME){
            N = str.size();
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
            init(str);
        }

    void set_mod(long long MOD){
        this->MOD = MOD;
    }

    void set_prime(long long PRIME){
        this->PRIME = PRIME;
    }

    long long binpow(long long x, long long n)
    {
        long long result = 1;
        while(n > 0)
        {
            if(n&1)
                result = mod_mul(result, x, MOD);
            x = mod_mul(x, x, MOD);
            n /= 2;
        }
        return result;
    }

    void init(const string &str){
        long long prime_pow = 1;
        inv[0] = 1;
        hash_val[0] = (str[0] - 'a' + 1);

        int n = str.size();
        for(int i = 1; i < n; i++){
            char ch = str[i];

            prime_pow = mod_mul(prime_pow, PRIME, MOD);
            inv[i] = binpow(prime_pow, MOD - 2);

            // hash_val[i] = (hash_val[i - 1] + (ch - 'a' + 1) * prime_pow) % MOD;
            hash_val[i] = mod_add(hash_val[i - 1], mod_mul(ch - 'a' + 1, prime_pow, MOD), MOD);
        }
    }

    long long getHash(int l, int r){
        long long result = hash_val[r];
        if(l > 0)
            result = mod_sub(result, hash_val[l - 1]);
        result = mod_mul(result, inv[l], MOD);
        return result;
    }

    //  If we don't need to store the hash values, use this to get hash value
    // of a substring/ string
    long long string_hash(const string &str){
        long long hash_value = 0;
        long long prime_pow = 1;
        for(char ch : str){
            hash_value = mod_add(hash_value, mod_mul(ch - 'a' + 1, prime_pow, MOD), MOD);
            prime_pow = mod_mul(prime_pow, PRIME, MOD);
        }
        return hash_value;
    }
};

void solve(){
    string str1;
    cin >> str1;
    cout << str1 << "\n";
    Hashing s(str1);
    cout << s.getHash(1, 2);

}