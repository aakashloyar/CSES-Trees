#include <iostream>
#include <vector>

using namespace std;

vector<int> dfs(vector<vector<int>>& adj_list, int curr, int prev) {
    vector<int>& internal = adj_list[curr];
    int sum = 1;
    int c = 0;
    for (int i = 0; i < internal.size(); i++) {
        int next = internal[i];
        if (next != prev) {
            vector<int> x = dfs(adj_list, next, curr);
            if (x[0] == 1) sum++;
            else c++;
            c += x[1];
        }
    }
    return {sum, c};
}

int solve(vector<vector<int>>& adj_list, int n) {
    vector<int> res = dfs(adj_list, 0, -1);
    if (res[0] != 1) res[1]++;
    return res[1];
}

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

    int ans = solve(adj_list, n);
    cout << ans << endl;

    return 0;
}
