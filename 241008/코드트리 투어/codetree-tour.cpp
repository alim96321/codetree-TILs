#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
#include <map>

using namespace std;

#define N_MAX 2005
#define M_MAX 10005

struct Products{
    int plus, id;

    Products(int a, int b) : plus(a), id(b) {}

    bool operator<(const Products ex) const{
        if(this->plus != ex.plus) return this->plus > ex.plus;
        return this->id < ex.id;
    }
};

vector<vector<pair<int, int>>> graph(N_MAX, vector<pair<int, int>>());  // (도착지, 비용)
vector<Products> thing; // (이윤-거리, id)
map<int, pair<int, int>> product;  // (이윤, 도착지)

int start = 0; // 출발지

bool compare(Products a, Products b){
    if(a.plus != b.plus) return a.plus > b.plus;
    return a.id < b.id;
}

void Dijkstra(int distance[N_MAX],int start){
    priority_queue<pair<int, int>> pq;
    for(int i = 0; i < N_MAX; i++){
        distance[i] = INT_MAX;
    }

    distance[start] = 0;
    pq.push(make_pair(0, start));

    while(!pq.empty()){
        int nCost = -pq.top().first;
        int sNode = pq.top().second;
        int num = graph[sNode].size();
        pq.pop();

        for(int i = 0; i < num; i++){
            int nNode = graph[sNode][i].first;
            int Cost = graph[sNode][i].second;

            if(distance[nNode] > Cost + nCost){
                distance[nNode] = Cost + nCost;
                pq.push(make_pair(-distance[nNode], nNode));
            }
        }
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int distance[N_MAX];

    int Q;
    int order;
    cin >> Q;


    for(int i = 0; i < Q; i++){
        cin >> order;
        switch(order){
            case 100:{
                int n, m;
                cin >> n >> m;
                for(int j = 0; j < m; j++){
                    int v, u, w;
                    cin >> v >> u >> w;
                    graph[v].emplace_back(u, w);
                }
                Dijkstra(distance, 0);
                break;
            }
            case 200:{
                int id, rev, dest;
                cin >> id >> rev >> dest;
                product[id] = make_pair(rev, dest);
                thing.emplace_back(Products(rev-distance[dest], id));
                break;
            }
            case 300:{
                int id;
                cin >> id;
                product.erase(id);
                
                int num = thing.size();
                for(int j = 0; j < num; j++){
                    if(thing[j].id == id){
                        thing.erase(thing.begin() + j);
                        break;
                    }
                }
                
                break;
            }
            case 400:{
                if(thing.empty()){
                    cout << -1 << '\n';
                }
                else{
                    sort(thing.begin(), thing.end(), compare);
                    if(distance[product[thing.front().id].second] == INT_MAX || (thing.front().plus < 0)){
                        cout << -1 << '\n';
                    }
                    else{
                        cout << thing.front().id << '\n';
                        thing.erase(thing.begin());
                    }
                    
                }
                break;
            }
            case 500:{
                int s;
                cin >> s;
                Dijkstra(distance, s);

                int num = thing.size();
                for(int j = 0; j < num; j++){
                    int tmp_id = thing[j].id;
                    thing[j].plus = product[tmp_id].first - distance[product[tmp_id].second];
                }
                break;
            }
        }
    }

    return 0;
}