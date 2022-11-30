#include <bits/stdc++.h>
using namespace std;
struct SegmentTree{
    vector<int> t, modifier;

    SegmentTree(vector<int> &vals){
        int n= vals.size();
        t.resize(n*4);
        modifier.resize(n*4);
        build(0, n-1, 1, vals);
    }

    void build(int a, int b, int u, vector<int> &vals){
        if(a==b){
            t[u] = vals[a];
            return;
        }
        int m = (a+b)/2;
        build(a, m, u*2, vals);
        build(m+1, b, u*2+1, vals);
        t[u] = min( t[2*u], t[2*u+1]);
    }

    void push(int u){
        t[u*2] += modifier[u];
        modifier[u*2] += modifier[u];
        t[u*2+1] += modifier[u];
        modifier[u*2+1] += modifier[u];
        modifier[u] = 0;
    }

    int query(int a, int b, int u, int l, int r){
        if(r<a || b<l){
            return INT_MAX;
        }
        if(l <= a && b <= r){
            return t[u];
        }
        if(modifier[u] != 0){
            push(u);
        }
        int m = (a+b)/2;
        return min(query(a, m, u*2, l, r), query(m+1, b, u*2+1, l, r));
    }

    void update(int a, int b, int u, int l, int r, int v){
        if(r < a || b < l){
            return;
        }
        if(l <= a && b <= r){
            t[u] += v;
            modifier[u] += v;
            return;
        }
        if (modifier[u] != 0){
            push(u);
        }
        int m = (a+b)/2;
        update(a, m, 2*u, l, r, v);
        update(m+1, b, 2*u+1, l, r, v);
        t[u] = min(t[u*2], t[u*2+1]);
    }
};
