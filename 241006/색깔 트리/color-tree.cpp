#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

using namespace std;

struct Node{
    int m_id, p_id, color, max_depth; // p_id는 해쉬의 key로 사용
    vector<int> children;

    // 생성자
    Node(int a, int b, int c, int d) : m_id(a), color(b), max_depth(c), p_id(d) {}
};

unordered_map<int, Node*> tree;

bool canAddNode(int node_id){
    int min_depth = tree[node_id]->max_depth;
    if(min_depth == 1){
        return false;
    }
    else{
        int count = 1;

        while(tree[node_id]->p_id != -1){
            node_id = tree[node_id]->p_id;

            if(min_depth > tree[node_id]->max_depth){
                min_depth = tree[node_id]->max_depth;
                count++;
            }
        }
        return min_depth >= count;
    }

}

// 서브트리 내 색깔 변경
void changeColor(int m, int c){
    Node* node = tree[m];
    node->color = c;
    for(int child : node->children){
        changeColor(child, c); // DFS로 자식 순회
    }
}

void countUniqueColors(int m, unordered_set<int>& uniqueColors){
    Node* node = tree[m];
    uniqueColors.insert(node->color);
    for(int child : node->children){
        countUniqueColors(child, uniqueColors); // DFS로 자식 순회
    }
}

int calculateTree(){
    int totalScore = 0;
    for(auto& it : tree){
        Node* node = it.second;
        unordered_set<int> uniqueColors;
        countUniqueColors(node->m_id, uniqueColors);
        totalScore += pow(uniqueColors.size(), 2);
    }
    return totalScore;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int order;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> order;
        
        if(order == 100){
            int m, p, c, d;
            cin >> m >> p >> c >> d;
            if(p == -1){
                // 새 트리 추가
                tree[m] = new Node(m, c, d, -1);
            }
            else{
                Node* parent = tree[p];
                if(canAddNode(p)){
                    tree[m] = new Node(m, c, d, p);
                    parent->children.emplace_back(m);
                }
            }
        }
        else if(order == 200){
            int m, c;
            cin >> m >> c;
            changeColor(m, c);
        }
        else if(order == 300){
            int m;
            cin >> m;
            cout << tree[m]->color << endl;
        }
        else if(order == 400){
            cout << calculateTree() << endl;
        }
    }

    return 0;
}