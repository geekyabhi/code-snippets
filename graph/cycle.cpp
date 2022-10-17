#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

class Graph{
    int n;
    unordered_map<int,vector<int>>graph;
    public:
    Graph(int n,unordered_map<int,vector<int>>&mp):n{n}{
        this->graph=mp;
    }

    void print(){
        for(auto root:graph){
            cout<<root.first<<"-> ";
            for(auto n:graph[root.first]){
                int node=n;
                cout<<node<<" ";
            }
            cout<<"\n";
        }
    }

    bool util_icd(int root,vector<bool>&visited,vector<bool>&reached){
        visited[root]=true;
        reached[root]=true;
        if(graph.count(root)){
            for(auto node:graph[root]){
                if(!visited[node]&&util_icd(node,visited,reached)) return true;
                else if(reached[node]) return true;
            }
        }
        reached[root]=false;
        return false;
    }

    bool isCycleDirected(){
        vector<bool>visited(n+1,false);
        vector<bool>reached(n+1,false);

        for(auto root:graph){
            if(!visited[root.first]){
                if(util_icd(root.first,visited,reached)){
                    return true;
                }
            }
        }
        return false;
    }

    bool util_icud(int root,int parent,vector<bool>&visited){
        visited[root]=true;

        if(graph.count(root)){
            for(auto node:graph[root]){
                if(!visited[node]&&util_icud(node,root,visited)) return true;
                else if(node!=parent) return true;
            }
        }

        return false;
    }

    bool isCycleUndirecteddfs(){
        vector<bool>visited(n+1,false);
        for(auto root:graph){
            if(!visited[root.first]&&util_icud(root.first,-1,visited)) return true;
        }
        return false;
    }

    bool util_icub(int src,vector<bool>&visited){
        queue<pair<int,int>>q;
        q.push({src,-1});
        while(q.size()){
            auto tp=q.front();
            q.pop();
            int root=tp.first;
            int parent=tp.second;
            if(graph.count(root)){
                for(auto node:graph[root]){
                    if(!visited[node]){ 
                        visited[node]=true;
                        q.push({node,root});
                    }else if(node!=parent){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool isCycleUndirectedbfs(){
        vector<bool>visited(n+1,false);
        for(auto root:graph){
            if(!visited[root.first]&&util_icub(root.first,visited)) return true;
        }
        return false;
    }

};

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    unordered_map<int,vector<int>>mp;
    int n;cin>>n;
    int N=-1e9;
    while(n--){
        int a,b;cin>>a>>b;
        N=max({N,a,b});
        mp[a].push_back(b);
        mp[b].push_back(a);
    }

    Graph g(N,mp);

    bool ans=g.isCycleUndirecteddfs();

    cout<<ans;

    return 0;
}