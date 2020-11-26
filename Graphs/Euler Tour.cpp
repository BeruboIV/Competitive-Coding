const int N = 2e5;
vector<int> adj[N + 1], euler_tour;

void EulerTour(int src, int par){
    euler_tour.push_back(src);
    for(int child : adj[src]){
        if(child != par){
            EulerTour(child, src);
            euler_tour.push_back(src);
        }
    }
}