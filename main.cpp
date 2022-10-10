#include<string>
#include<iostream>
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

struct node{
    int open,close,full;
    node(){
        open=0;
        close=0;
        full=0;
    }
    node(int _o,int _c,int _f)  {
        open=_o;
        close=_c;
        full=_f;
    }
};


node merge(node left,node right){
    node ans=node(0,0,0);
    ans.full=left.full+right.full+min(left.open,right.close);
    ans.open=left.open+right.open-min(left.open,right.close);
    ans.close=left.close+right.close-min(left.open,right.close);
    return ans;
}

void build(int index,int low,int high,string &s,node seg[]){
    if(low==high){
        seg[index]= node((int)(s[low]=='('),(int)(s[high]==')'),0);
        return ;
    }
    int mid=(low+high)/2;
    build(2*index+1,low,mid,s,seg);
    build(2*index+2,mid+1,high,s,seg);
    node left=seg[2*index+1];
    node right=seg[2*index+2];
    seg[index]=merge(left,right);
}

node query(int index,int low,int high,int l,int r,node seg[]){
    if(l>high||r<low) return node();
    else if(low>=l&&high<=r) return seg[index];

    int mid=(low+high)/2;

    node left=query(2*index+1,low,mid,l,r,seg);
    node right=query(2*index+2,mid+1,high,l,r,seg);

    return merge(left,right);
}


void solve(){
    string s;
    ll q;
    cin>>s;
    cin>>q;
    int n=s.size();
    node seg[4*n];

    build(0,0,n-1,s,seg);

    while(q--){
        int ans=0;
        int l,r;
        cin>>l>>r;
        node a=query(0,0,n-1,l-1,r-1,seg);
        ans=a.full*2;
        cout<<ans<<"\n";
    }

}


int main(){
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // #endif
    fast
    // ll t=1;
    // cin>>t;
    // while(t--) 
    solve();

    return 0;
}