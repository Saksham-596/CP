//-------------------sieve-SPF----------------------------------
vector<ll> sieve_spf(ll N) {
    vector<ll> spf(N+1, 0);
    if (N >= 1) spf[1] = 1;
    ll limit = (ll)floor(sqrt((double)N));
    for (ll p = 2; p <= limit; ++p) {
        if (spf[p] == 0) {
            spf[p] = p;
            ll start = 1LL * p * p;
            for (ll j = start; j <= N; j += p) {
                if (spf[j] == 0) spf[j] = p;
            }
        }
    }
    for (ll i = 2; i <= N; ++i) if (spf[i] == 0) spf[i] = i;
    return spf;
}
//------------------linear-spf---------------------------------------
vector<ll> computeSPF(ll N){
    vector<ll> spf(N + 1, 0);
    vector<ll> primes;

    for(ll i = 2; i <= N; i++){
        if (spf[i] == 0) {          // i is prime
            spf[i] = i;
            primes.push_back(i);
        }

        for(ll p : primes){
            ll x = 1LL * p * i;
            if (x > N) break;

            spf[x] = p;             // p is the smallest prime factor of x

            if (p == spf[i])        // stop when p > spf[i]
                break;
        }
    }
    return spf;
}




