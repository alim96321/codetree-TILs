#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

struct Node{
    int m_id, p_id, color, max_depth;
    
    // 생성자
    Node(int a, int b, int c, int d) : m_id(a), p_id(b), color(c), max_depth(d) {}
};

void changeColor(vector<pair<int, vector<Node>>>& tree, int m, int c){
    queue<int> q;
    q.push(m);

    while(!q.empty()){
        int num = q.front();
        q.pop();
        for(int i = 0; i < tree.size(); i++){
            if(num == tree[i].first){
                for(int j = 0; j < tree[i].second.size(); j++){ // 자기 자신과 서브트리의 색깔 변경
                    tree[i].second[j].color = c;
                    if(j == 0){
                        continue;
                    }
                    else{
                        q.push(tree[i].second[j].m_id);
                    }
                } // m_id가 num인 노드와 서브트리의 색깔 변화
                for(int p = 0; p < tree.size(); p++){
                    for(int z = 0; z < tree[p].second.size(); z++){
                        if(tree[p].second[z].m_id == m){
                            tree[p].second[z].color = c;
                        }
                    }
                } // m_id가 num인 노드를 가지고 있는 루트의 서비트리에서 색깔 변화
                break;
            }
        }
    }
    return;
}

int calculateTree(const vector<pair<int, vector<Node>>>& tree){
    queue<int> q;
    int i = 0;
    int sum = 0;
    vector<int> arr;

    while(i != tree.size()){
        q.push(tree[i].first);
        while(!q.empty()){
            int num = q.front();
            q.pop();
            for(int j = 0; j < tree.size(); j++){
                if(num == tree[j].first){
                    arr.emplace_back(tree[j].second[0].color);
                    for(int k = 0; k < tree[j].second.size(); k++){
                        if(k == 0){
                            continue;
                        }
                        else{
                            q.push(tree[j].second[k].m_id);
                        }
                    }
                    break;
                }
            }
        }
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        sum += pow(arr.size(), 2);
        arr.clear();
        i++;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int n;
    int order;
    int m, p, c, d;

    vector<pair<int, vector<Node>>> tree;

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> order;
        if(order == 100){
            cin >> m >> p >> c >> d;
            Node nd(m, p, c, d);
            vector<Node> st;
            st.emplace_back(nd);

            if(p == -1){
                // 새 트리 만들기
                tree.emplace_back(make_pair(m, st));
            }
            else{
                if(!tree.empty()){
                    for(int j = 0; j < tree.size();j++){
                        if(p == tree[j].first && d <= tree[j].second[0].max_depth){
                            tree[j].second.emplace_back(nd);
                            tree.emplace_back(make_pair(m, st));
                        }
                    }
                }
                else continue;
            }
        }
        else if(order == 200){
            cin >> m >> c;
            changeColor(tree, m, c);
        }
        else if(order == 300){
            cin >> m;
            for(int j = 0; j < tree.size(); j++){
                if(m == tree[j].first){
                    cout << tree[j].second[0].color << endl;
                    break;
                }
            }
        }
        else if(order == 400){
            cout << calculateTree(tree) << endl;
        }
    }

    return 0;
}