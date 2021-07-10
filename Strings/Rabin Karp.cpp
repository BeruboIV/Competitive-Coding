vector<int> rabin_karp(string const& t, string const& p) {
    // t -> text string
    // p -> pattern string
    const long long prime = 31; 
    const long long MOD = 1e9 + 7;
    int T = t.size(), P = p.size();

    vector<long long> prime_pow(max(T, P)); 
    prime_pow[0] = 1; 
    int n = prime_pow.size();
    for (int i = 1; i < n; i++) 
        prime_pow[i] = (prime_pow[i - 1] * prime) % MOD;

    vector<long long> hash_val(T + 1, 0); 
    for (int i = 0; i < T; i++)
        hash_val[i + 1] = (hash_val[i] + (t[i] - 'a' + 1) * prime_pow[i]) % MOD; 
    long long hash_p = 0; 
    for (int i = 0; i < P; i++) 
        hash_p = (hash_p + (p[i] - 'a' + 1) * prime_pow[i]) % MOD; 

    vector<int> occurences;
    for (int i = 0; i + P - 1 < T; i++) { 
        long long cur_hash = (hash_val[i + P] - hash_val[i] + MOD) % MOD; 
        if (cur_hash == hash_p * prime_pow[i] % MOD)
            occurences.push_back(i);
    }
    return occurences;
}