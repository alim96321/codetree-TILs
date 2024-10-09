#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
#include <map>
//#include <cstdio>

using namespace std;

#define N_MAX 2005
#define M_MAX 10005

// first : 이윤(매출-거리), second : id
struct cmp{
    bool operator()(pair<int, int>& a, pair<int, int>& b){
        if(a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    }
};

vector<vector<pair<int, int>>> graph(N_MAX, vector<pair<int, int>>());  // (도착지, 비용)
map<int, pair<int, int>> product;  // (이윤, 도착지)
map<int, bool> arr_id;  // (id, true or false)
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> ppq;

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
    //freopen("input.txt", "r", stdin);

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
                Dijkstra(distance, 0);
                break;
            }
            case 200:{
                int id, rev, dest;
                cin >> id >> rev >> dest;
                product[id] = make_pair(rev, dest);
                ppq.push(make_pair(rev-distance[dest], id));
                arr_id[id] = true;
                break;
            }
            case 300:{
                int id;
                cin >> id;
                product.erase(id);
                arr_id[id] = false;
                
                break;
            }
            case 400:{
                while(true){
                    if(ppq.empty()){
                        cout << -1 << '\n';
                        break;
                    }
                    else{
                        pair<int, int> np = ppq.top();
                        if(!arr_id[np.second]){
                            ppq.pop();
                            continue;
                        }

                        if((distance[product[np.second].second] != INT_MAX) && (np.first >= 0)){
                            cout << np.second << '\n';
                            arr_id[np.second] = false;
                            ppq.pop();
                            product.erase(np.second);
                            break;
                        }
                        else{
                            cout << -1 << '\n';
                            break;
                        }
                    }
                }
                break;
            }
            case 500:{
                int s;
                cin >> s;
                Dijkstra(distance, s);

                int num = ppq.size();
                priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> tmp;
                for(int j = 0; j < num; j++){
                    int tmp_id = ppq.top().second;
                    ppq.pop();
                    tmp.push(make_pair(product[tmp_id].first - distance[product[tmp_id].second], tmp_id));
                }
                ppq = tmp;
                break;
            }
        }
    }

    return 0;
}