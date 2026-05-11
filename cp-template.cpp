/*-------starting template__________*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<numeric>
#include<set>
#include<string>
#include<chrono>
#include<unordered_map>
#include<queue>
#include<deque>
#include<unordered_set>
#include<utility>
#include<stack>
#include<cstdint>
#include<bitset>

#define pb push_back
#define ALL(x) (x).begin(),(x).end()
#define srt(x) sort(ALL(x))
#define vecout(v) for (auto &x : v) cout << x << ' '; cout << '\n';
#define yes cout << "YES\n"
#define no cout << "NO\n"

using namespace std;

const long long linf = 1e18;
const int mod = 1e9 + 7;
using ll = long long ;

void solve(){
    
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin>>t;
    for(int i = 1 ;i<=t;i++){
        solve();
    }
    return 0;
}

/*----------------------------------------*/



//-------------------SPF----------------------------------

const int MAXN = 10000000;
vector<int> spf(MAXN + 1);
void computeSPF(){
    for (int i = 0; i <= MAXN; i++)
        spf[i] = i;
    
    for (int i = 2; i * i <= MAXN; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= MAXN; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}


// ------------------ Sieve of Eratosthenes ------------------
vector<bool> sieve(ll n) {
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return is_prime;
}

// ------------------ Math Helpers ------------------
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}


//--------------------COMBINATORICS-----------------------

// modular expo
ll modpow(ll  a , ll b , ll m){
    a%=m;
    ll res = 1 ;
    while(b>0){
        if(b&1){
            res = (res*a)%m;
        }
        a =(a*a)%m;
        b>>=1;
    }
    return res ;
}
// --------------invmod---------------
ll invmod(ll a , ll m){
    return modpow(a,m-2,m);
}
// -----------factorial--------------
vector<ll> factorial(ll n ,ll m){
    vector<ll> f(n+1);
    f[0] = 1 ;
    for(ll i = 1 ;i<=n;i++){
        f[i] = (f[i-1]*i)%m;
    }
    return f;
}
// ----------inverse factorial-------------
vector<ll> invfactorial(ll n ,ll m ,ll lastfact){
    vector<ll> invf(n+1);
    invf[n] = modpow(lastfact,m-2,m);
    for(ll i = n-1;i>=0;i--){
        invf[i] = (invf[i+1]*(i+1))%m;
    }
    return invf;
}
// *+++modular addition+++*
ll add(ll x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
    if (x < 0) x += mod;
    return x;
}
// *xxx modular multiplicationxxx*
ll mul(ll x, ll y) {
    return x * 1LL * y % mod;
}
// */// modular division///*
ll divide(ll x, ll  y) {
    return mul(x, modpow(y, mod - 2 , mod ));
}

// *---------------------ncr----------------------------*

ll ncr(ll  n , ll r  , ll mod){
    if(r<0 or n<0 or r>n){
        return 0;
    }
    ll ans = mul(fact[n],inv[r]); // to be DECLARED before hand
    ans = mul(ans,inv[n-r]);      // to be DECLARED before hand
    return ans ;
}

// ------------------ prefix and suffix sum ------------------
vector<ll> prefix_sum(vector<ll> & v){
    ll n = v.size();
    vector<ll> p(n+1,0);
    for(ll i = 1 ; i<=n;i++){
        p[i] = v[i-1] + p[i-1];
    }
    return p ;
}

vector<ll> suffix_sum(vector<ll> & v){
    ll n = v.size();
    vector<ll> s(n+1,0);
    for(ll i = n-1;i>=0;i--){
        s[i] = s[i+1] + v[i];
    }
    return s ;
}


/*-------------cycle detection for undirected graph -----------*/
 // (to be used inside main )
vector<ll> vis(n);
auto cycle = [&](auto self, ll u , ll p)->bool{
    vis[u] = 1;
    bool b = false;
    for(auto it : adj[u]){
        if(it==p)continue;
        if(vis[it]==1){
            return true;
        }
        b|=self(self,it,u);
        if(b==true){
            return true;
        }
    }
    return b;
};

// ------------------ Direction Arrays ------------------
int dx4[4] = {-1, 0, 1, 0};
int dy4[4] = {0, 1, 0, -1};
int dx8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};


// --------------------DSU--------------------------------

class DSU {
    vector<ll> rank , parent ,size;
public:
    DSU(ll n ){
        rank.resize(n+1,0);
        parent.resize(n+1,0);
        size.resize(n+1);
        for(ll i = 0;i<=n;i++){
            parent[i] = i ;
            size[i] = 1;
        }
    }
    ll findUpar(ll node){
        if(node== parent[node]){
            return node ;
        }
        return parent[node] =  findUpar(parent[node]);
    }
    void unionbyrank(ll u , ll v ){
        ll ult_pu =findUpar(u);
        ll ult_pv =findUpar(v);
        if(ult_pu == ult_pv)return;
        if(rank[ult_pu]<rank[ult_pv]){
            parent[ult_pu] = ult_pv ;
        }
        else if(rank[ult_pv] < rank[ult_pu]){
            parent[ult_pv] = ult_pu;
        }else{
            parent[ult_pv] = ult_pu;
            rank[ult_pu]++;
        }
    }
    void unionbysize(ll u , ll v ){
        ll ult_pu =findUpar(u);
        ll ult_pv =findUpar(v);
        if(ult_pu == ult_pv)return;
        if(size[ult_pu] < size[ult_pv]){
            parent[ult_pu] = ult_pv;
            size[ult_pv]+=size[ult_pu];
        }else{
            parent[ult_pv] = ult_pu;
            size[ult_pu]+=size[ult_pv];
        }
    }
};

// -----------------Bellman_Ford ------------------
vector<ll>  bellman_ford(ll n , ll  src , vector<vector<ll>> &  edges) { // edges will contain u , v and their weights ^_^
    vector<ll> dist(n,linf);
    dist[src] = 0 ;
    for(ll i = 0 ;i<n-1;i++){
        bool up = false;
        for(auto it : edges){
            ll u  = it[0];
            ll v = it[1];
            ll w = it[2];
            if(dist[u]!=linf && dist[u] + w < dist[v]){
                dist[v]  =  dist[u] + w ;
                up = true;
            }
        }
        if(!up){
            break;
        }
    }
    for(auto it : edges){
        ll u  = it[0];
        ll v = it[1];
        ll w = it[2];
        if(dist[u]!=linf && dist[u] + w < dist[v]){
            return {-1};
        }
    }
    return dist;
}



//----------------build-lps------------------------//

auto build_lps = [&](string &p)->vector<ll> {
        ll n = p.size();
        vector<ll> lps(n);
        ll len = 0;
        for (ll i  = 1; i < n;) {
            if(p[i]==p[len]) {
                len++;
                lps[i] = len;
                i++;
            }else {
                if (len != 0) {
                    len = lps[len-1] ;
                } else{
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    };

//--------kmp-----------------------------------------//

auto kmp = [&](string & text , string & pat) {
        vector<ll> lps = build_lps(pat);
        vector<ll> occ;
        ll i = 0,j = 0;
        while(i<text.size()) {
            if(text[i]==pat[j]) {
                i++;
                j++;
            }
            if(j==pat.size()) {
                occ.push_back(i-j);
                j = lps[j-1];
            }
            else if(i < text.size () &&  text[i]!=pat[j]) {
                if(j!=0)
                    j = lps[j-1];
                else
                    i++;
            }
        }
        return occ;
    };





