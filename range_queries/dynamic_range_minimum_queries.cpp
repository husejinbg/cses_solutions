#include <bits/stdc++.h>
 
#define loop(n) for(int $i = 0; $i < n; $i++)
#define fast ios_base::sync_with_stdio(false); cin.tie(nullptr)
 
#define int ll
 
using namespace std;
 
typedef long long ll;
 
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef tuple<int, int, int, int> iiii;
typedef tuple<int, int, int, int, int> iiiii;
 
typedef vector<bool> vb;
 
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<iiii> viiii;
typedef vector<iiiii> viiiii;
 
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<viii> vviii;
typedef vector<viiii> vviiii;
typedef vector<viiiii> vviiiii;
 
template<typename T>
ostream & operator<<(ostream &os, const vector<T> &v)
{
    for(auto &x:v) cout << x << ' ';
    return os;
}
 
const int INF = 1e9+7;
 
int n;
vi st, lazy;
 
int combine(int x, int y) // change this function for different problems, this is for RMQ
{
    if(x == -1) return y;
    if(y == -1) return x;
    return min(x, y);
}
 
void build(vi &v, int node, int segmentL, int segmentR)
{
    if(segmentL == segmentR)
    {
        st[node] = v[segmentL];
        return;
    }
 
    int m = (segmentL + segmentR) / 2;
    int leftChild = 2*node, rightChild = leftChild+1;
    build(v, leftChild, segmentL, m);
    build(v, rightChild, m+1, segmentR);
    st[node] = combine(st[leftChild], st[rightChild]);
}
 
void build(vi &v)
{
    st.assign(4*n, -1);
    lazy.assign(4*n, -1);
    build(v, 1, 0, n-1);
}
 
void propagate(int node, int segmentL, int segmentR)
{
    if(lazy[node] == -1) return;
    st[node] = lazy[node]; // change this line for different problems, this is for RMQ
    if(segmentL != segmentR)
    {
        int leftChild = 2*node, rightChild = leftChild+1;
        lazy[leftChild] = lazy[node];
        lazy[rightChild] = lazy[node];
    }
    lazy[node] = -1;
}
 
void update(int node, int segmentL, int segmentR, int queryL, int queryR, int val)
{
    propagate(node, segmentL, segmentR);
    if(segmentR < queryL || queryR < segmentL) return; // out of range
    if(queryL <= segmentL && segmentR <= queryR) // completely in range
    {
        lazy[node] = val;
        propagate(node, segmentL, segmentR);
        return;
    }
 
    int m = (segmentL + segmentR) / 2;
    int leftChild = 2*node, rightChild = leftChild+1;
    update(leftChild, segmentL, m, queryL, queryR, val);
    update(rightChild, m+1, segmentR, queryL, queryR, val);
    st[node] = combine(st[leftChild], st[rightChild]);
}
 
void update(int queryL, int queryR, int val) // range update
{
    update(1, 0, n-1, queryL, queryR, val);
}
 
void update(int pos, int val) // point update (range update with queryL = queryR)
{
    update(pos, pos, val);
}
 
int query(int node, int segmentL, int segmentR, int queryL, int queryR)
{
    propagate(node, segmentL, segmentR);
    if(segmentR < queryL || queryR < segmentL) return -1; // out of range
    if(queryL <= segmentL && segmentR <= queryR) return st[node]; // completely in range
 
    int m = (segmentL + segmentR) / 2;
    int leftChild = 2*node, rightChild = leftChild+1;
    int leftAns = query(leftChild, segmentL, m, queryL, queryR);
    int rightAns = query(rightChild, m+1, segmentR, queryL, queryR);
    return combine(leftAns, rightAns);
}
 
int query(int queryL, int queryR) // range query
{
    return query(1, 0, n-1, queryL, queryR);
}
 
 
void $main()
{
    int q;
    cin >> n >> q;
    vi v(n);
    for(int &x:v) cin >> x;
    build(v);
    loop(q)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            // point update
            int pos, val;
            cin >> pos >> val;
            pos--;
            update(pos, val);
        }
        else
        {
            // range query
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << query(l, r) << '\n';
        }
    }
}

// https://cses.fi/problemset/task/1649/
int32_t main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    fast;
    int t;
    // cin >> t;
    t = 1;
    loop(t) $main();
 
 
}
