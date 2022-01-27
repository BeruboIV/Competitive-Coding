class Node{
public:
    Node *children[2];
    int sz = 0;
    int endOfWord = 0;

    Node(){
        children[0] = children[1] = NULL;
        sz = 0;
        endOfWord = 0;
    }
};

template <typename T = long long>
class Trie{
public:
    int BITS = 31;
    Node *root;
    Trie(){
        root = new Node();
    }

    bool isSet(T val, T k){
        return ((val >> k) & 1LL);
    }

    void insert(T val){
        Node *curr = root;
        curr->sz++;
        for(int i = BITS - 1; i >= 0; i--){
            bool parity = isSet(val, i);
            if(curr->children[parity] == NULL)
                curr->children[parity] = new Node();
            curr = curr->children[parity];
            curr->sz++;
        }

        curr->endOfWord++;
    }

    bool find(T val){
        Node *curr = root;
        for(int i = BITS - 1; i >= 0; i--){
            bool parity = isSet(val, i);
            if(curr->children[parity] == NULL || curr->sz <= 0)
                return false;
            curr = curr->children[parity];
        }

        return (curr->endOfWord);
    }

    bool isEmpty(){
        return (!root->children[0] && !root->children[1]);
    }

    void remove(T val){
        // Make it recursive to acutally remove the nodes, right now only values are being removed
        // not the nodes themselves

        if(!find(val))
            return;

        Node *curr = root;
        curr->sz--;

        for(int i = BITS - 1; i >= 0; i--){
            bool parity = ((val >> i) & 1LL);
            curr = curr->children[parity];
            curr->sz--;
        }

        curr->endOfWord--;
    }

};