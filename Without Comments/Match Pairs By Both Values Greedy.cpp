#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define all(x) x.begin(),x.end()
#define allr(x) x.rbegin(),x.rend()
const ll MOD=998244353,INF=1e18;
void fastIO() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);}

void preCompute() {
    
}

struct Item {
    ll x, y;
    ll id;
};

void solve() {
    ll n, m;
    if (!(cin >> n >> m)) return;

    vector<Item> consumers(n);
    for (ll i = 0; i < n; ++i) {
        cin >> consumers[i].x >> consumers[i].y;
        consumers[i].id = i;
    }

    vector<Item> resources(m);
    for (ll i = 0; i < m; ++i) {
        cin >> resources[i].x >> resources[i].y;
        resources[i].id = i + 1;
    }

    if (m < n) {
        cout << -1 << "\n";
        return;
    }

    sort(all(consumers), [](const Item& a, const Item& b) {
        if (a.x != b.x) return a.x > b.x;
        return a.y > b.y;
    });

    sort(all(resources), [](const Item& a, const Item& b) {
        return a.x > b.x;
    });

    set<pair<ll, ll>> pool;
    vector<ll> ans(n);
    ll res_ptr = 0;

    for (const auto& con : consumers) {
        while (res_ptr < m && resources[res_ptr].x >= con.x) {
            pool.insert({resources[res_ptr].y, resources[res_ptr].id});
            res_ptr++;
        }

        auto it = pool.lower_bound({con.y, -1LL});

        if (it == pool.end()) {
            cout << -1 << "\n";
            return;
        }

        ans[con.id] = it->second;
        pool.erase(it);
    }

    for (ll i = 0; i < n; ++i) {
        cout << ans[i] << (i + 1 == n ? "" : " ");
    }
    cout << "\n";
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
