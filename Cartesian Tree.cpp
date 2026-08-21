#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define all(x) x.begin(),x.end()
#define allr(x) x.rbegin(),x.rend()
const ll MOD=1e9+7,INF=1e18;
void fastIO() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);}


template <typename T>
struct CartesianTree {
    int n;
    int root;
    vector<T> a;
    vector<int> lc;
    vector<int> rc;

    CartesianTree(const vector<T>& arr) {
        n = arr.size();
        a = arr;
        lc.assign(n, -1);
        rc.assign(n, -1);
        build();
    }

    void build() {
        if (n == 0) {
            root = -1;
            return;
        }
        vector<int> st; 
        for (int i = 0; i < n; i++) {
            int last_popped = -1;
            while (!st.empty() && a[st.back()] > a[i]) {
                last_popped = st.back();
                st.pop_back();
            }
            if (last_popped != -1) {
                lc[i] = last_popped;
            }
            if (!st.empty()) {
                rc[st.back()] = i;
            }
            st.push_back(i);
        }
        root = st[0];
    }
};


void preCompute() {

}

void solve() {
    
}

int main() {
    fastIO();
    preCompute();
    ll TestCases=1;
    cin>>TestCases;
    while(TestCases--) {
        solve();
    }
}
