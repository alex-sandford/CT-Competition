#include <bits/stdc++.h>
using namespace std;


#define ln '\n'
#define ll long long

ll gcd(ll a, ll b){return ((b == 0) ? a: gcd(b, a%b));}
ll lcm(ll a, ll b){return a/gcd(a, b)*b;}

const int UPPER = 2023;
const int SZ = UPPER + 1;

map<int, vector<array<int, 2>>> mp;


void print(const vector<array<int, 2>>& v){
    for (auto& u: v){
        cout << u[0] << ' ' << u[1] << ln;
    }
    cout << ln;}
void print(const vector<array<int, 3>>& v){
    for (auto& u: v){
        cout << u[0] << ' ' << u[1] << ' ' << u[2] << ln;
    }
    cout << ln;}
void print(vector<int>& v){
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++){
        cout << v[i];
        if (i != v.size()) cout << ',';
    }}
void print(const bitset<SZ>& b){
    for (int i = 2; i <= UPPER; i++){
        if (b[i]) cout << i << ',';
    }}

ll rand(ll a, ll b){
    return a + rand() % (b - a + 1LL);
}

int mx = 0;

void solve(){
    srand(time(0));

    array<int, 2> c;
    for (int a = 2; a <= UPPER; a++){
        for (int b = a; b <= UPPER; b++){
            ll l = lcm(a, b);
            ll sum = l/a + l/b;

            ll g = gcd(l, sum);
            l /= g; sum /= g;

            if (l > UPPER || a*sum > UPPER || b*sum > UPPER) continue;
            c[0] = a*sum; c[1] = b*sum;
            if (find(mp[l].begin(), mp[l].end(), c) == mp[l].end()){
                mp[l].push_back(c);
            }
        }
    }

    // for (auto it = mp.begin(); it != mp.end(); it++){
    //     cout << it->first << ln;

    //     for (auto& u: it->second){
    //         cout << u[0] << ' ' << u[1] << ln;
    //     }
    //     cout << ln;
    // }

    vector<int> ans = {2,3,6};
    bitset<SZ> bit, copy;
    vector<int> tmp;
    for (auto& u: ans) bit[u] = 1;


    int T = 1;
    int upper = 1e6;
    int interval = upper/10;
    while (T++ < upper){
        int idx = rand(0, ans.size()-1);

        // if (T % interval == 1) cout << ans.size() << ln;

        bool perfect = false;
        // Looking for perfect collision
        for (auto& u: mp[ans[idx]]){
            int x = u[0], y = u[1];
            if (!(bit[x] || bit[y]) && x != y){
                bit[ans[idx]] = 0;
                bit[x] = bit[y] = 1;
                ans.push_back(x);
                ans.push_back(y);
                ans.erase(find(ans.begin(), ans.end(), ans[idx]));
                perfect = true;
                break;
            }
        }

        if (perfect) continue;

        for (auto& u: mp[ans[idx]]){
            int x = u[0], y = u[1];

            if ((bit[x] && bit[y]) || x == y){
                continue;
            } else {
                if (bit[y]) swap(x, y);

                copy = bit;
                tmp = ans;

                copy[y] = 1;
                copy[ans[idx]] = 0;
                tmp.erase(find(tmp.begin(), tmp.end(), ans[idx]));
                tmp.push_back(y);

                // // even resolve - may reduce term
                // while (x > 1 && (x % 2 == 0) && copy[x]){
                //     tmp.erase(find(tmp.begin(), tmp.end(), x));
                //     copy[x] = 0;
                //     x /= 2;
                // }
                // if (x <= 1) continue;

                // if (!copy[x]){
                //     copy[x] = 1;
                //     tmp.push_back(x);

                //     bit = copy;
                //     ans = tmp;
                //     break;
                // }

                if (x & 1){
                    int a = (x-1)/2;
                    int b = a+1, c = (a+1)*(2*a+1);
                    if (c <= UPPER && !(copy[b] || copy[c]) && b != c){
                        copy[x] = 0;
                        copy[b] = copy[c] = 1;
                        tmp.push_back(b);
                        tmp.push_back(c);
                        tmp.erase(find(tmp.begin(), tmp.end(), x));

                        bit = copy;
                        ans = tmp;
                        break;
                    }

                }

            } // else
        } // for
    } // while

    cout << bit.count() << ln;
    print(bit); cout << ln;
    // mx = max(mx, (int)bit.count());
} // solve




int main(){
    int TT = 1e5;
    while (TT--){
        solve();
    }
    // cout << mx << ln;
    // solve();




}
