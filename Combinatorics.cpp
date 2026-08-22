#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define all(x) x.begin(),x.end()
#define allr(x) x.rbegin(),x.rend()
const ll MOD=1e9+7,INF=1e18;
void fastIO() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);}


struct Combinatorics{
    ll MOD;
    vector<ll> fac, inv, finv;

    void init(int n, ll mod){
        MOD = mod;
        fac.assign(n + 1, 1);
        inv.assign(n + 1, 1);
        finv.assign(n + 1, 1);
        for(ll i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;
        for(ll i = 2; i <= n; ++i) inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
        for(ll i = 2; i <= n; ++i) finv[i] = finv[i - 1] * inv[i] % MOD;
    }

    ll power(ll b, ll n){
        b %= MOD;
        ll s = 1;
        while(n){
            if(n % 2 == 1) s = s * b % MOD;
            b = b * b % MOD;
            n /= 2;
        }
        return s;
    }

    ll nCr(ll x, ll y){
        if(x < 0 || y > x || y < 0) return 0;
        return fac[x] * finv[y] % MOD * finv[x - y] % MOD;
    }

    ll nPr(ll x, ll y){
        if(x < 0 || y > x || y < 0) return 0;
        return fac[x] * finv[x - y] % MOD;
    }

    ll mul(ll a, ll b){ return (a % MOD) * (b % MOD) % MOD; }
    ll add(ll a, ll b){ return (a % MOD + b % MOD) % MOD; }
    ll sub(ll a, ll b){ return ((a % MOD - b % MOD) + MOD) % MOD; }
    ll divide(ll a, ll b){ return mul(a, power(b, MOD - 2)); }
    ll get_inv(ll x){ return power(x, MOD - 2); }
    ll catalan(int n){ return mul(nCr(2 * n, n), inv[n + 1]); }

    ll StarsAndBars(ll n, ll k){
        if(n < 0 || k < 0) return 0;
        if(n == 0 && k == 0) return 1;
        return nCr(n + k - 1, k - 1);
    }

    ll nPr_LargeN(ll n, ll r){
        if(r < 0 || n < r) return 0;
        if(r == 0) return 1;

        ll ans = 1;
        for(ll i = 0; i < r; ++i){
            ans = mul(ans, (n - i) % MOD);
        }
        return ans;
    }

    ll nCr_LargeN(ll n, ll r){
        if(r < 0 || n < r) return 0;
        if(r == 0) return 1;

        return mul(nPr_LargeN(n, r), finv[r]);
    }

    ll StarsAndBars_LargeN(ll items, ll bins) {
        if(items < 0 || bins < 0) return 0;
        if(items == 0 && bins == 0) return 1;
        return nCr_LargeN(items + bins - 1, bins - 1);
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
