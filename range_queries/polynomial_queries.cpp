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
vi lazy2;
 
int combine(int x, int y) // change this function for different problems, this is for RSQ
{
    return x+y;
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
    st.assign(4*n, 0);
    lazy.assign(4*n, 0);
    lazy2.assign(4*n, 0);
    build(v, 1, 0, n-1);
}
 
void propagate(int node, int segmentL, int segmentR)
{
    if(lazy[node] == 0) return;
 
    int a = lazy[node];
    int k = lazy2[node];
    int b = a + (segmentR-segmentL)*k;
    int n = (b-a)/k + 1;
    int temp = n * (a + b) / 2;
    st[node] += temp;
    if(segmentL != segmentR)
    {
        int leftChild = 2*node, rightChild = leftChild+1;
        int m = (segmentL + segmentR) / 2;
        lazy[leftChild] += a;
        lazy[rightChild] += a + (m-segmentL+1)*k;
        lazy2[leftChild] += k;
        lazy2[rightChild] += k;
        // propagate(leftChild, segmentL, m);
        // propagate(rightChild, m+1, segmentR);
    }
    
    lazy[node] = 0;
    lazy2[node] = 0;
}
 
void update(int node, int segmentL, int segmentR, int queryL, int queryR)
{
    int a = segmentL-queryL+1;
    propagate(node, segmentL, segmentR);
    if(segmentR < queryL || queryR < segmentL) return; // out of range
    if(queryL <= segmentL && segmentR <= queryR) // completely in range
    {
        // lazy[node] += a;
        lazy[node] += a;
        lazy2[node] += 1;
        propagate(node, segmentL, segmentR);
        return;
    }
    int m = (segmentL + segmentR) / 2;
    int leftChild = 2*node, rightChild = leftChild+1;
    update(leftChild, segmentL, m, queryL, queryR);
    update(rightChild, m+1, segmentR, queryL, queryR);
    st[node] = combine(st[leftChild], st[rightChild]);
}
 
void update(int queryL, int queryR) // range update
{
    update(1, 0, n-1, queryL, queryR);
}
 
int query(int node, int segmentL, int segmentR, int queryL, int queryR)
{
    propagate(node, segmentL, segmentR);
    if(segmentR < queryL || queryR < segmentL) return 0; // out of range
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
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if(t == 1)
        {
            update(l, r);
        }
        else
        {
            cout << query(l, r) << '\n';    
        }
    }
}
 
// https://cses.fi/problemset/task/1736
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