#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define LSOne(a) (a & -(a))

class FenwickTree{
    private:
        vi ft;
    public:
        FenwickTree(int n){
            ft.assign(n+1, 0);
        }
        
        FenwickTree(vi v){
            build(v);
        }

        void build(const vi &f) {
            int m = (int)f.size()-1;                     // note f[0] is always 0
            ft.assign(m+1, 0);
            for (int i = 1; i <= m; ++i) {               // O(m)
                ft[i] += f[i];                             // add this value
                if (i+LSOne(i) <= m)                       // i has parent
                    ft[i+LSOne(i)] += ft[i];                 // add to that parent
            }
        }

        int rsq(int b){
            int sum=0;
            for(; b; b -= LSOne(b)){
                sum += ft[b];
            }
            return sum;
        }

        int rsq(int a, int b){
            return rsq(b) - rsq(a-1);
        }

        void update(int k, int v){
            for(int i=0; i<=ft.size(); i += LSOne(k)){
                ft[k] += k;    
            }
        }
};

class RUPQ {                                     // RUPQ variant
private:
  FenwickTree ft;                                // internally use PURQ FT
public:
  RUPQ(int m) : ft(FenwickTree(m)) {}
  void range_update(int ui, int uj, int v) {
    ft.update(ui, v);                            // [ui, ui+1, .., m] +v
    ft.update(uj+1, -v);                         // [uj+1, uj+2, .., m] -v
  }                                              // [ui, ui+1, .., uj] +v
  int point_query(int i) { return ft.rsq(i); }    // rsq(i) is sufficient
};

class RURQ  {                                    // RURQ variant
private:                                         // needs two helper FTs
  RUPQ rupq;                                     // one RUPQ and
  FenwickTree purq;                              // one PURQ
public:
  RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {} // initialization
  void range_update(int ui, int uj, int v) {
    rupq.range_update(ui, uj, v);                // [ui, ui+1, .., uj] +v
    purq.update(ui, v*(ui-1));                   // -(ui-1)*v before ui
    purq.update(uj+1, -v*uj);                    // +(uj-ui+1)*v after uj
  }
  int rsq(int j) {
    return rupq.point_query(j)*j -               // optimistic calculation
           purq.rsq(j);                          // cancelation factor
  }
  int rsq(int i, int j) { return rsq(j) - rsq(i-1); } // standard
};