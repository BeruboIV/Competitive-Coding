// Copied this code from Neal: https://codeforces.com/contest/1771/submission/184731058
// Don't know how this algorithm works, so if you have any question, don't ask me.
// I use this snippet as a blackbox
struct barrett_reduction {
    unsigned mod;
    uint64_t div;
 
    barrett_reduction(unsigned m) : mod(m), div(-1LLU / m) {}
 
    unsigned operator()(uint64_t a) const {
#ifdef __SIZEOF_INT128__
        uint64_t q = uint64_t(__uint128_t(div) * a >> 64);
        uint64_t r = a - q * mod;
        return unsigned(r < mod ? r : r - mod);
#endif
        return unsigned(a % mod);
    }
};

// Time Complexity: O(K * (logN)^3) where K is the number of iterations
bool miller_rabin(unsigned n) {
    if (n < 2)
        return false;
 
    // Check small primes.
    for (unsigned p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
        if (n % p == 0)
            return n == p;
 
    // https://miller-rabin.appspot.com/
    auto get_miller_rabin_bases = [&]() -> vector<uint64_t> {
        if (n < 341531) return {9345883071009581737LLU};
        if (n < 1050535501) return {336781006125, 9639812373923155};
        return {4230279247111683200, 14694767155120705706LLU, 16641139526367750375LLU};
    };
 
    int r = __builtin_ctz(n - 1);
    unsigned d = (n - 1) >> r;
    barrett_reduction barrett(n);
 
    auto mod_pow = [&](unsigned a, unsigned b) -> unsigned {
        unsigned result = 1;
 
        while (b > 0) {
            if (b & 1)
                result = barrett(uint64_t(result) * a);
 
            a = barrett(uint64_t(a) * a);
            b >>= 1;
        }
 
        return result;
    };
 
    for (uint64_t a : get_miller_rabin_bases()) {
        if (a % n == 0)
            continue;
 
        unsigned x = mod_pow(unsigned(a % n), d);
 
        if (x == 1 || x == n - 1)
            continue;
 
        for (int i = 0; i < r - 1 && x != n - 1; i++)
            x = barrett(uint64_t(x) * x);
 
        if (x != n - 1)
            return false;
    }
 
    return true;
}

unsigned binary_gcd(unsigned a, unsigned b) {
    if (a == 0 || b == 0)
        return a + b;
 
    int common = __builtin_ctz(a | b);
    b >>= __builtin_ctz(b);
 
    do {
        a >>= __builtin_ctz(a);
 
        if (a < b)
            swap(a, b);
 
        a -= b;
    } while (a != 0);
 
    return b << common;
}

uint64_t random_address() { char *p = new char; delete p; return uint64_t(p); }
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));

// Time Complexity: O(N^(1/4))
// Goes to an infinite loop if n = 1 OR n is a prime number. Handle those cases separately
unsigned pollard_rho(unsigned n) {
    // Check small primes.
    for (unsigned p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
        if (n % p == 0)
            return p;
 
    barrett_reduction barrett(n);
 
    unsigned increment;
    auto g = [&](uint64_t x) -> unsigned {
        return barrett(x * x + increment);
    };
 
    // Choose a jump size much larger than log(n) but much smaller than n^(1/4).
    int jump = int(sqrt(log(n) * sqrt(sqrt(n))));
 
    while (true) {
        increment = unsigned(rng() % n);
        unsigned start = unsigned(rng() % n);
        unsigned x = start, y = start, p = 1;
        vector<unsigned> products(jump + 1);
 
        // https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants
        do {
            products[0] = 1;
 
            for (int i = 1; i <= jump; i++) {
                x = g(x);
                y = g(g(y));
                products[i] = barrett(uint64_t(products[i - 1]) * (max(x, y) - min(x, y)));
            }
        } while ((p = binary_gcd(products[jump], n)) == 1);
 
        if (p == n) {
            assert(products[jump] == 0);
            int index = jump;
 
            while (index > 0 && products[index] == 0)
                index--;
 
            p = binary_gcd(products[index], n);
        }
 
        if (p != 1 && p != n)
            return p;
    }
}

template<typename T>
map<T, int> prime_factorize(T n) {
    if (n == 1)
        return {};
 
    if (miller_rabin(n))
        return {{n, 1}};
 
    T x = pollard_rho(n);
    map<T, int> A = prime_factorize(x), B = prime_factorize(n / x);
 
    if (A.size() < B.size())
        swap(A, B);
 
    for (pair<T, int> p : B)
        A[p.first] += p.second;
 
    return A;
}