//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ONLINE_JUDGE
#define debug(x) cerr << "Line(" << __LINE__ << ") " << #x << " = "; _print(x); cerr << "\n";
#else
#define debug(x)
#endif 

void _print(int &x){
    cerr << x;
}

void _print(const int &x){
    cerr << x;
}

void _print(int64_t &x){
    cerr << x;
}

void _print(const int64_t &x){
    cerr << x;
}

void _print(char &x){
    cerr << x;
}

void _print(const char &x){
    cerr << x;
}

void _print(string &x){
    cerr << x;
}

void _print(const string &x){
    cerr << x;
}

void _print(bool &x){
    cerr << x;
}

void _print(const bool &x){
    cerr << x;
}

template<class T>
void _print(vector<T> &v1){
    cerr << "[";
    int sz = v1.size();
    for(int i = 0; i < sz - 1; i++)
        cerr << v1[i] << ", ";
    cerr << v1.back() << "]";
}

template<class T>
void _print(set<T> &s1){
    cerr << "{";
    int n = s1.size();
    for(T i : s1){
        _print(i);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "}";
}

template<class T>
void _print(multiset<T> &s1){
    cerr << "{";
    int n = s1.size();
    for(T i : s1){
        _print(i);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "}";
}

template<class T, class V>
void _print(map<T, V> &mp){
    cerr << "[";
    int n = mp.size();
    for(auto p : mp){
        cerr << "{";
        _print(p.first);
        cerr << ", ";
        _print(p.second);
        cerr << "}";
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T, class V>
void _print(pair<T, V> &p){
    cerr << "{" << p.first << ", " << p.second << "}";
}

template<class T>
void _print(vector<vector<T>> &vec){
    cerr << "[";
    int n = vec.size();
    for(vector<T> &v1 : vec){
        _print(v1);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T, class V>
void _print(vector<pair<T, V>> &vec){
    cerr << "[";
    int n = vec.size();
    for(pair<T, V> &p : vec){
        _print(p);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////