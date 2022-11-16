template <typename T = long long>
class Node{
public:
    Node *children[2];
    int sz = 0;
    int endOfWord = 0;
    T val = 0;

    Node(){
        children[0] = children[1] = NULL;
        sz = 0;
        endOfWord = 0;
        val = 0;
    }
};

template <typename T = long long>
class Trie{
public:
    const static int BITS = 31;
    Node<T> *root;
    Trie(){
        root = new Node<T>();
    }

    // Check of the k-th bit is set or not
    bool isSet(T val, T k){
        return ((val >> k) & 1LL);
    }

    void insert(T val){
        Node<T> *curr = root;
        curr->sz++;
        for(int i = BITS - 1; i >= 0; i--){
            bool parity = isSet(val, i);
            if(curr->children[parity] == NULL)
                curr->children[parity] = new Node<T>();
            curr = curr->children[parity];
            curr->sz++;
        }

        curr->endOfWord++;
        curr->val = val;
    }

    bool find(T val){
        Node<T> *curr = root;
        for(int i = BITS - 1; i >= 0; i--){
            bool parity = isSet(val, i);
            if(curr->children[parity] == NULL || curr->sz <= 0)
                return false;
            curr = curr->children[parity];
        }

        return (curr->endOfWord);
    }

    bool isEmpty(Node<T> *node){
        return (node->children[0] == NULL && node->children[1] == NULL && node->sz == 0 && node->endOfWord == 0);
    }

    Node<T>* remove_helper(Node<T> *node, T val, int curr_bit = BITS - 1){
        // If trie node is empty
        if(node == NULL)
            return NULL;
        node->sz--;

        // Last bit is being processed
        if(curr_bit == -1){
            // Remove the single occurence
            cerr << node->endOfWord;
            if(node->endOfWord > 0){
                node->endOfWord--;
            }

            // If give is not prefix of any other number
            if(isEmpty(node)){
                cerr << "YO\n";
                delete(node);
                return NULL;
            }
            return node;
        }

        // If not 0th bit, recur for the child
        bool parity = isSet(val, curr_bit);
        node->children[parity] = remove_helper(node->children[parity], val, curr_bit - 1);

        // If trie node does not have any child (its only child got deleted),
        // and it is not end of another number
        if(isEmpty(node) && node->endOfWord == 0){
            delete (node);
            return NULL;
        }

        return node;
    }

    void remove(T val){
        // Make it recursive to acutally remove the nodes, right now only values are being removed
        // not the nodes themselves

        if(!find(val))
            return;

        Node<T> *curr = root;
        remove_helper(curr, val);
    }

    // Number of values s.t val ^ x < k
    T query(T x, T k){
        Node<T> *curr = root;
        T ans = 0;

        for(int i = BITS - 1; i >= 0; i--){
            if(curr == NULL)
                break;
            bool parity_x = isSet(x, i), parity_k = isSet(k, i);
            if(parity_k == true){
                if(curr->children[parity_x])
                    ans += (curr->children[parity_x])->sz;
                curr = curr -> children[!parity_x];
            }
            else
                curr = curr->children[parity_x];
        }

        return ans;
    }

    // Returns maximum of val ^ x
    T get_max(T x){
        Node<T> *curr = root;
        T ans = 0;

        for(int i = BITS - 1; i >= 0; i--){
            if(curr == NULL)
                break;
            bool parity = isSet(x, i);
            if(curr->children[!parity]){
                curr = curr->children[!parity];
                ans <<= 1ll;
                ans++;
            }
            else{
                curr = curr->children[parity];
                ans <<= 1ll;
            }
        }

        return ans;
    }

    // Returns minimum of val ^ x
    T get_min(T x){
        Node<T> *curr = root;
        T ans = 0;

        for(int i = BITS - 1; i >= 0; i--){
            if(curr == NULL)
                break;
            bool parity = isSet(x, i);
            if(curr->children[parity]){
                curr = curr->children[parity];
                ans <<= 1ll;
            }
            else{
                curr = curr->children[!parity];
                ans <<= 1ll;
                ans++;
            }
        }

        return ans;
    }
};
