#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& adj_list, vector<vector<long long>>& dp, int curr, int prev);
void rerooting(vector<vector<int>>& adj_list, vector<vector<long long>>& dp, vector<long long>& res, int curr, int prev, int n);
void solve(vector<vector<int>>& adj_list, int n);
void print(const vector<long long>& res);

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj_list(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--; // Adjusting indices
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    solve(adj_list, n);

    return 0;
}

void solve(vector<vector<int>>& adj_list, int n) {
    vector<vector<long long>> dp(n, vector<long long>(2, 0));
    vector<long long> res(n);
    dfs(adj_list, dp, 0, -1);
    rerooting(adj_list, dp, res, 0, -1, n);
    print(res);
}

void rerooting(vector<vector<int>>& adj_list, vector<vector<long long>>& dp, vector<long long>& res, int curr, int prev, int n) {
    long long ans = dp[curr][0];
    if (prev != -1) {
        ans += res[prev];
        ans -= dp[curr][0];
        ans = ans - dp[curr][1] - 1;
        ans = ans + (n - dp[curr][1] - 1);
    }
    res[curr] = ans;
    vector<int>& internal = adj_list[curr];
    for (int i = 0; i < internal.size(); i++) {
        int next = internal[i];
        if (next != prev) {
            rerooting(adj_list, dp, res, next, curr, n);
        }
    }
}

void dfs(vector<vector<int>>& adj_list, vector<vector<long long>>& dp, int curr, int prev) {
    long long c = 0, sum = 0;
    vector<int>& internal = adj_list[curr];
    for (int i = 0; i < internal.size(); i++) {
        int next = internal[i];
        if (next != prev) {
            dfs(adj_list, dp, next, curr);
            c += dp[next][1] + 1;
            sum += dp[next][0];
        }
    }
    sum += c;
    dp[curr][0] = sum;
    dp[curr][1] = c;
}

void print(const vector<long long>& res) {
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    cout << endl;
}
