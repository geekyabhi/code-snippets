#include<iostream>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
#include<unordered_set>
using namespace std;

class Graph{
    int n;
    unordered_map<int,vector<pair<int,int>>> graph;
    public:

    Graph(){}

    Graph(int n,unordered_map<int,vector<pair<int,int>>>mp):n{n}{
        this->graph=mp;
    }

    void print(){
        for(auto root:graph){
            cout<<root.first<<"-> ";
            for(auto n:graph[root.first]){
                int node=n.first;
                int w=n.second;
                cout<<node<<"W"<<w<<" ";
            }
            cout<<"\n";
        }
    }

    // DIJKSTRA never works on negative weight because it a greedy algorithm 
    // it starts reducing the next min distance when pushed into priotity queue

    // DIJKSTRA USING PRIORITY QUEUE COMPLEXITY->V log(E)

    vector<int> dikstraPQ(int src){
        vector<int>dis(n+1,1e9);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        pq.push({0,src});
        dis[src]=0;
        while(pq.size()){
            auto tp=pq.top();
            int d=tp.first;
            int root=tp.second;
            pq.pop();
            for(auto n:graph[root]){
                int node=n.first;
                int w=n.second;
                if(dis[node]>d+w){
                    dis[node]=d+w;
                    pq.push({dis[node],node});
                }
            }
        }
        return dis;
    }

    //DIJKSTRA USING SETS COMPLEXITY->V log(E)
    vector<int> dikstraST(int src){
        vector<int>dis(n+1,1e9);
        set<pair<int,int>>st;
        st.insert({0,src});
        dis[src]=0;
        while(st.size()){
            auto it=*(st.begin());
            int d=it.first;
            int root=it.second;
            st.erase(it);
            for(auto n:graph[root]){
                int node=n.first;
                int w=n.second;
                if(dis[node]>d+w){
                    if(dis[node]!=1e9) st.erase({dis[node],node});
                    dis[node]=d+w;
                    st.insert({dis[node],node});
                }
            }
        }
        return dis;
    }

    // Bellmand Ford only works on the directed graph
    // Undirected graph can be converted into dorected graph
    // Bellman does not gives ans on negative weight cycle
    // COMPLEXITY (n-1)E

    vector<int> bellmanFord(int src){
        vector<int>dis(n+1,1e9);
        dis[src]=0;
        for(int i=1;i<n;i++){
            for(auto root:graph){
                for(auto node:root.second){
                    int u=root.first;
                    int v=node.first;
                    int w=node.second;
                    if(dis[u]!=1e9&&dis[u]+w<dis[v]){
                        dis[v]=dis[u]+w;
                    }
                }
            }
        }

        for(auto root:graph){
            for(auto node:root.second){
                int u=root.first;
                int v=node.first;
                int w=node.second;
                if(dis[u]!=1e9&&dis[u]+w<dis[v]){
                    cout<<"\n# Its a cycle # \n";
                    return {};
                }
            }
        }

        return dis;
    }

    // Floyd Warshell n3 complexity
    vector<vector<int>> fw(){
        vector<vector<int>>dis(n+1,vector<int>(n+1,1e9));
        for(int i=0;i<=n;i++) dis[i][i]=0;

        for(auto root:graph){
            for(auto n:graph[root.first]){
                int u=root.first;
                int v=n.first;
                int w=n.second;
                dis[u][v]=w;
            }
        }

        for(int k=0;k<=n;k++){
            for(auto root:graph){
                for(auto n:graph[root.first]){
                    int u=root.first;
                    int v=n.first;
                    int w=n.second;
                    dis[u][v]=min(dis[u][v],dis[u][k]+dis[k][v]);
                }
            }
        }

        for(int i=0;i<=n;i++)
            if(dis[i][i]<0){
                cout<<"\n# Its a cycle # \n";
                return {};
            }

        return dis;

    }
};


int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    int n;cin>>n;
    vector<vector<int>>edges;

    int N=-1e9;

    for(int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        N=max(N,a);
        N=max(N,b);
        edges.push_back({a,b,c});
    }

    unordered_map<int,vector<pair<int,int>>> graph;
    for(auto edge:edges){
        graph[edge[0]].push_back({edge[1],edge[2]});
    }

    Graph g(N,graph);

    vector<vector<int>>ans=g.fw();

    for(auto i:ans){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<"\n";
    }

    return 0;
}