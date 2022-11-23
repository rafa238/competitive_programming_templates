#include <bits/stdc++.h>

using namespace std;

vector<int> criba(int n){
    vector<int> primos;
    vector<bool> not_prime(n+1);

    not_prime[0] = not_prime[1] = true;
    for(int i=3; i*i <= n; i += 2){
        if(not_prime[i] == false){
            for(int j = i*i; j <= n; j += 2 * i)
                not_prime[j] = true;
        }
    }
    primos.push_back(2);
    for(int i=3; i <= n; i += 2){
        if(not_prime[i] == false){
            primos.push_back(i);
        }
    }
    return primos;
}