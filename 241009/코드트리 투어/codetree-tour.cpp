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
};

vector<vector<pair<int, int>>> graph(N_MAX, vector<pair<int, int>>());  // (도착지, 비용)
vector<Products> thing; // (이윤-거리, id)
map<int, pair<int, int>> product;  // (이윤, 도착지)

int start = 0; // 출발지

bool compare(Products a, Products b){
    if(a.plus != b.plus) return a.plus > b.plus;
    return a.id < b.id;
}

// node간의 최소 거리 최신화
void Dijkstra(int distance[N_MAX],int st){
    priority_queue<pair<int, int>> pq;
    for(int i = 0; i < N_MAX; i++){
        distance[i] = INT_MAX;
    }

    distance[st] = 0;
    pq.push(make_pair(0, st));

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
                    if(v != u)
                        graph[u].emplace_back(v, w);
                }
                Dijkstra(distance, start);
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
                    Products np = thing.front();
                    if(distance[product[np.id].second] != INT_MAX && np.plus >= 0){
                        cout << np.id << '\n';
                        thing.erase(thing.begin());
                        product.erase(np.id);
                    }
                    else{
                        cout << -1 << '\n';
                    }
                }
                break;
            }
            case 500:{
                int s;
                cin >> s;
                Dijkstra(distance, s);
                start = s;

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