// 0-based indexing is followed here
class Hashing{
    const long long N = 2e5;
    const long long MOD = 1e9 + 7;
    const long long prime = 31; // Prime numebr just greater than number of characters
    vector<long long> hash_val, inv;  // inv[i] = 1/(prime^i)
public:

    Hashing(){
        hash_val.resize(N + 1, 0);
        inv.resize(N + 1, 0);
    }

    Hashing(long long N)
        :N(N){
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
        }

    Hashing(long long N, long long MOD)
        :N(N), MOD(MOD){
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
        }

    Hashing(long long N, long long MOD, long long prime)
        :N(N), MOD(MOD), prime(prime){
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
        }

    Hashing(string str){
        hash_val.resize(N + 1, 0);
        inv.resize(N + 1, 0);
        init(str);
    }

    Hashing(string str, long long N)
        :N(N){
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
            init(str);
        }

    Hashing(string str, long long N, long long MOD)
        :N(N), MOD(MOD){
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
            init(str);
        }

    Hashing(string str, long long N, long long MOD, long long prime)
        :N(N), MOD(MOD), prime(prime){
            hash_val.resize(N + 1, 0);
            inv.resize(N + 1, 0);
            init(str);
        }

    long long binpow(long long x,long long n)
    {
        long long result = 1;
        while(n > 0)
        {
            if(n&1)
                result = (result * x) % MOD;
            x = (x * x) % MOD;
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

            prime_pow = (prime * prime_pow) % MOD;
            inv[i] = binpow(prime_pow, MOD - 2);

            hash_val[i] = (hash_val[i - 1] + (ch - 'a' + 1) * prime_pow) % MOD;
        }
    }

    long long getHash(int l, int r){
        long long result = hash_val[r];
        if(l > 0)
            result -= hash_val[l - 1];
        if(result < 0)
            result += MOD;
        result = (result * inv[l]) % MOD;

        return result;
    }

    //  If we don't need to store the hash values, use this to get hash value
    // of a substring/ string
    long long string_hash(const string &str){
        long long hash_value = 0;
        long long prime_pow = 1;
        for(char ch : str){
            hash_value = (hash_value + (ch - 'a' + 1) * prime_pow) % MOD;
            prime_pow = (prime_pow * prime) % MOD;
        }
        return hash_value;
    }
};

void solve(){
    string str1, str2;
    cin >> str1 >> str2;
    cout << str1 << "\n" << str2 << "\n";
    Hashing s(str1), t;
    t.init(str2);
    cout << s.getHash(1, 2) << "\n" << t.getHash(1, 2);

}