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

    //Only valid for directed acyclic graph
    vector<int>ktopo(){
        //here n is the node number so choose it carefully
        vector<int>indegree(n+1,0);
        vector<int>ans;
        queue<int>q; 
        for(auto root:graph)
            for(auto node:graph[root.first])
                indegree[node]++;

        for(int i=0;i<indegree.size();i++) if(indegree[i]==0) q.push(i);

        while(q.size()){
            int root=q.front();
            q.pop();
            ans.push_back(root);

            for(auto node:graph[root]){
                if(!(--indegree[node])){
                    q.push(node);
                }
            }

        }   
        return ans;
    }

    void util(int root,vector<int>&visited,stack<int>&st){
        visited[root]=1;
        if(graph.count(root)){
            for(auto node:graph[root]){
                if(!visited[node]){
                    util(node,visited,st);
                }
            }
        }
        st.push(root);
    }

    vector<int> topo(){
        vector<int>ans;
        stack<int>st;
        vector<int>visited(n+1,0);
        for(auto root:graph){
            if(!visited[root.first]){
                util(root.first,visited,st);
            }
        }
        while(st.size()){
            ans.push_back(st.top());
            st.pop();
        }
        return ans;
    }

    bool dfs(int root,vector<bool>&visited,vector<bool>&reached){
        visited[root]=true;
        reached[root]=true;
        if(graph.count(root)){
            for(auto node:graph[root]){
                if(!visited[node]&&dfs(node,visited,reached)) return true;
                else if(reached[node]) return true;
            }
        }
        reached[root]=false;
        return false;
    }

    bool isCycle(){
        vector<bool>visited(n+1,false);
        vector<bool>reached(n+1,false);

        for(auto root:graph){
            if(!visited[root.first]){
                if(dfs(root.first,visited,reached)){
                    return true;
                }
            }
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
    }

    Graph g(N,mp);

    g.print();

    bool ans=g.isCycle();

    cout<<ans;
    return 0;
}