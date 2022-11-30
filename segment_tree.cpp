#include <bits/stdc++.h>
using namespace std;
struct SegmentTree{
    vector<int> t;

    SegmentTree(vector<int> &vals){
        int n= vals.size();
        t.resize(n*4);
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
        t[u] = t[2*u] + t[2*u+1];
    }

    int query(int a, int b, int u, int l, int r){
        if(r<a || b<l){
            return 0;
        }
        if(l <= a && b<=r){
            return t[u];
        }
        int m = (a+b)/2;
        return query(a, m, u*2, l, r) + query(m+1, b, u*2+1, l, r);
    }

    void update(int a, int b, int u, int pos, int val){
        if(a == b){
            t[u] = val;
            return;
        }
        int m = (a+b)/2;
        if(pos <= m){
            update(a, m, 2*u, pos, val);
        } else {
            update(m+1, b, 2*u+1, pos, val);
        }
        t[u] = t[u*2] + t[u*2+1];
    }
};
