#define debug(x...) cerr << "Line(" << __LINE__ << ") "; _Print(vec_splitter(#x), x); cerr << endl;

/* 
*   All function prototypes
*/

template<class T>
void _print(T &x);

template<class T>
void _print(const T &x);

template<class T>
void _print(vector<T> &v1);

template<class T>
void _print(set<T> &s1);

template<class T>
void _print(multiset<T> &s1);

template<class T, class V>
void _print(map<T, V> &mp);

template<class T, class V, class R>
void _print(map<pair<T, V>, R> &mp);

template<class T, class V>
void _print(map<T, vector<V>> &mp);

template<class T, class V>
void _print(const pair<T, V> &p);

template<class T, class V>
void _print(pair<T, V> &p);

template<class T>
void _print(vector<vector<T>> &vec);

template<class T, class V>
void _print(vector<pair<T, V>> &vec);

template<class T, class V>
void _print(vector<vector<pair<T, V>>> &vec);

template<class T, class V>
void _print(set<pair<T, V>> &sett);

template<class T, class V>
void _print(multiset<pair<T, V>> &sett);

template<class T>
void _print(queue<T> q);

template<class T>
void _print(priority_queue<T, vector<T>, greater<T>> Minheap);

template<class T>
void _print(priority_queue<T> Maxheap);

template<class T>
void _print(stack<T> st);


/*
*   All function definitions
*/ 

template<class T>
void _print(T &x){
    cerr << x;
}

template<class T>
void _print(const T &x){
    cerr << x;
}

template<class T>
void _print(vector<T> &v1){
    cerr << "[";
    int sz = v1.size();
    for(int i = 0; i < sz - 1; i++)
        cerr << v1[i] << ", ";
    if(!v1.empty())
        cerr << v1.back();
    cerr << "]";
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

template<class T, class V, class R>
void _print(map<pair<T, V>, R> &mp){
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
void _print(map<T, vector<V>> &mp){
    cerr << "[";
    int n = mp.size();
    for(auto p : mp){
        cerr << "{";
        _print(p.first);
        cerr << ": ";
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
void _print(const pair<T, V> &p){
    cerr << "{" << p.first << ", " << p.second << "}";
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

template<class T, class V>
void _print(vector<vector<pair<T, V>>> &vec){
    cerr << "[";
    int n = vec.size();
    for(vector<pair<T, V>> &vec1 : vec){
        _print(vec1);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T, class V>
void _print(set<pair<T, V>> &sett){
    cerr << "[";
    int n = sett.size();
    for(const pair<T, V> &p : sett){
        _print(p);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T, class V>
void _print(multiset<pair<T, V>> &sett){
    cerr << "[";
    int n = sett.size();
    for(const pair<T, V> &p : sett){
        _print(p);
        n--;
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T>
void _print(queue<T> q){
    cerr << "[";
    int n = q.size();
    while(n--){
        _print(q.front());
        q.pop();
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T>
void _print(priority_queue<T, vector<T>, greater<T>> Minheap){
    cerr << "[";
    int n = Minheap.size();
    while(n--){
        _print(Minheap.top());
        Minheap.pop();
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T>
void _print(priority_queue<T> Maxheap){
    cerr << "[";
    int n = Maxheap.size();
    while(n--){
        _print(Maxheap.top());
        Maxheap.pop();
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

template<class T>
void _print(stack<T> st){
    cerr << "[";
    int n = st.size();
    while(n--){
        _print(st.top());
        st.pop();
        if(n == 0)
            break;
        cerr << ", ";
    }
    cerr << "]";
}

vector<string> vec_splitter(string s) {
    vector<string> res;
    s += ',';

    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }

    return res;
}

// Recursive Variadic Lambda: https://stackoverflow.com/questions/49495015/c-recursive-variadic-lambda

template<class T, class... Types>
void _Print(T var1, Types&&... Var2){
    vector<string> res = var1;
    int i = 0;

    // Here Var2 = var2. Had to change case because of -Wshadow compiler warning
    auto Print_recursive = [&](auto& self, auto&& h, auto&&... var2) {
        // std::cout << sizeof...(var2) << endl;

        if constexpr ( sizeof...(var2) >= 0 ){
            cerr << res[i] << " = ";
            i++;
            _print(h);
            if constexpr ( sizeof...(var2) > 0 ){
                cerr << ", ";
                self(self,var2...);
            }
        }
    };
    return Print_recursive(Print_recursive, Var2...);
};
