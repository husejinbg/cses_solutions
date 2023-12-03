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
 
const int SET = 0, ADD = 1, NONE = 2;
 
int n;
vi st, lazy;
vi lazyType;
 
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
    lazyType.assign(4*n, NONE);
    build(v, 1, 0, n-1);
}
 
void assign_lazy(int node, int val, int type) // only for SET and ADD
{
    if(lazyType[node] == NONE)
    {
        lazy[node] = val;
        lazyType[node] = type;
    }
    else if(type == SET)
    {
        lazy[node] = val;
        lazyType[node] = SET;
    }
    else
    {
        lazy[node] += val;
    }
}
 
void propagate(int node, int segmentL, int segmentR)
{
    if(lazyType[node] == NONE) return;
 
    if(lazyType[node] == SET)
    {
        st[node] = (segmentR-segmentL+1)*lazy[node]; // change this line for different problems, this is for RSQ
        if(segmentL != segmentR)
        {
            int leftChild = 2*node, rightChild = leftChild+1;
            assign_lazy(leftChild, lazy[node], SET);
            assign_lazy(rightChild, lazy[node], SET);
        }
    }
    else
    {
        st[node] += (segmentR-segmentL+1)*lazy[node]; // change this line for different problems, this is for RSQ
        if(segmentL != segmentR)
        {
            int leftChild = 2*node, rightChild = leftChild+1;
            assign_lazy(leftChild, lazy[node], ADD);
            assign_lazy(rightChild, lazy[node], ADD);
        }
    }
 
    lazyType[node] = NONE;
    lazy[node] = 0;
}
 
void update(int node, int segmentL, int segmentR, int queryL, int queryR, int val, int type)
{
    propagate(node, segmentL, segmentR);
    if(segmentR < queryL || queryR < segmentL) return; // out of range
    if(queryL <= segmentL && segmentR <= queryR) // completely in range
    {
        assign_lazy(node, val, type);
        propagate(node, segmentL, segmentR);
        return;
    }
 
    int m = (segmentL + segmentR) / 2;
    int leftChild = 2*node, rightChild = leftChild+1;
    update(leftChild, segmentL, m, queryL, queryR, val, type);
    update(rightChild, m+1, segmentR, queryL, queryR, val, type);
    st[node] = combine(st[leftChild], st[rightChild]);
}
 
void update(int queryL, int queryR, int val) // range update
{
    update(1, 0, n-1, queryL, queryR, val, SET);
}
 
void update_add(int queryL, int queryR, int val) // range update
{
    update(1, 0, n-1, queryL, queryR, val, ADD);
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
        int t;
        cin >> t;
        if(t == 1)
        {
            // add to range
            int l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            update_add(l, r, val);
        }
        else if(t == 2)
        {
            // set range
            int l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            update(l, r, val);
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
 
// https://cses.fi/problemset/task/1735
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