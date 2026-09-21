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
    ll id; // 0-based for consumers, 1-based for resources (or vice versa)
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
        resources[i].id = i + 1; // 1-based index for output
    }

    if (m < n) {
        cout << -1 << "\n";
        return;
    }

    // 1. Sort consumers descending by primary constraint (x). Tie-break descending on y.
    sort(all(consumers), [](const Item& a, const Item& b) {
        if (a.x != b.x) return a.x > b.x;
        return a.y > b.y;
    });

    // 2. Sort resources descending by primary attribute (x).
    sort(all(resources), [](const Item& a, const Item& b) {
        return a.x > b.x;
    });

    // 3. Pool holds valid resources: {y_value, resource_id}
    set<pair<ll, ll>> pool;
    vector<ll> ans(n);
    ll res_ptr = 0;

    for (const auto& con : consumers) {
        // Push all available resources satisfying res.x >= con.x
        while (res_ptr < m && resources[res_ptr].x >= con.x) {
            pool.insert({resources[res_ptr].y, resources[res_ptr].id});
            res_ptr++;
        }

        // Greedy choice: smallest valid y >= con.y
        // Using -1 for id ensures lower_bound captures pairs where y == con.y
        auto it = pool.lower_bound({con.y, -1LL});

        if (it == pool.end()) {
            cout << -1 << "\n";
            return;
        }

        ans[con.id] = it->second;
        pool.erase(it); // Consume the resource
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

/*
 ==============================================================================
                          WHEN TO TWEAK THIS PATTERN
 ==============================================================================

 1. Maximizing Matches (Partial matching instead of all-or-nothing):
    - If some consumers can be left unmatched without failing the entire query,
      change `if (it == pool.end()) return;` into a `continue;` and track how many
      matches were made.

 2. Reversed Direction (res.x <= con.x AND res.y <= con.y):
    - Sort BOTH consumers and resources in ASCENDING order of x.
    - Loop through consumers ascending.
    - Push resources while `res.x <= con.x`.
    - Greedy choice: Largest valid y <= con.y.
      Query: `auto it = pool.upper_bound({con.y, INF});`
      If `it != pool.begin()`, use `--it;` to get the element.

 3. No ID Tracking Needed (Only count / pure existence):
    - Replace `set<pair<ll, ll>> pool;` with a simple `multiset<ll> pool;`.
    - Insert `resources[res_ptr].y`.
    - Query: `auto it = pool.lower_bound(con.y);`.
    - Erase via iterator: `pool.erase(it);` (never erase by value, or duplicates vanish).

 4. Secondary Costs / Weights:
    - If each resource has an additional cost and you need minimum total cost,
      a standard 2D greedy sweep may fail and require Min-Cost Max-Flow (MCMF)
      or a Segment Tree with DP depending on bounds.
 ==============================================================================
*/
