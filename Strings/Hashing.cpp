const long long prime = 31;	// Prime numebr just greater than number of characters
const long long MOD = 1e9 + 7;
const long long N = 2e5;
long long hash_val[N + 1], inv[N + 1];	// inv[i] = 1/(prime^i)

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

long long substring_hash(int l, int r){
	long long result = hash_val[r];
	if(l > 0)
		result -= hash_val[l - 1];
	if(result < 0)
		result += MOD;
	result = (result * inv[l]) % MOD;

	return result;
}

//	If we don't need to store the hash values, use this
long long getHash(const string &str){
	long long hash_value = 0;
	long long prime_pow = 1;
	for(char ch : str){
		hash_value = (hash_value + (ch - 'a' + 1) * prime_pow) % MOD;
		prime_pow = (prime_pow * prime) % MOD;
	}
	return hash_value;
}