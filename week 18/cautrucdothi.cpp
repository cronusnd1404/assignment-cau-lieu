#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100; // Kích thước tối đa của đồ thị

// Hàm duyệt DFS đệ quy
void DFSUtil(int u, int n, int adj[MAX][MAX], bool visited[MAX], string& dfsOrder) {
    visited[u] = true; // Đánh dấu đỉnh đã thăm
    dfsOrder += (char)('a' + u); // Lưu đỉnh đã duyệt (theo ký tự)

    for (int v = 0; v < n; ++v) {
        if (adj[u][v] == 1 && !visited[v]) { // Nếu có cạnh và chưa thăm
            DFSUtil(v, n, adj, visited, dfsOrder);
        }
    }
}

// Hàm duyệt DFS toàn bộ đồ thị (xử lý cả trường hợp đồ thị rời rạc)
string DFS(int n, int adj[MAX][MAX]) {
    bool visited[MAX] = {false}; // Đánh dấu các đỉnh đã thăm
    string dfsOrder = "";

    for (int u = 0; u < n; ++u) {
        if (!visited[u]) {
            DFSUtil(u, n, adj, visited, dfsOrder);
        }
    }
    return dfsOrder;
}

// Hàm duyệt BFS toàn bộ đồ thị
string BFS(int n, int adj[MAX][MAX]) {
    bool visited[MAX] = {false}; // Đánh dấu các đỉnh đã thăm
    string bfsOrder = "";

    for (int start = 0; start < n; ++start) {
        if (!visited[start]) {
            queue<int> q;
            q.push(start);
            visited[start] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                bfsOrder += (char)('a' + u); // Lưu đỉnh đã duyệt

                for (int v = 0; v < n; ++v) {
                    if (adj[u][v] == 1 && !visited[v]) { // Nếu có cạnh và chưa thăm
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
        }
    }
    return bfsOrder;
}

int main() {
    int n = 8; // Số đỉnh (cố định theo ma trận bạn cung cấp)
    int adj[MAX][MAX] = {
        {0, 1, 0, 0, 1, 0, 1, 1}, // a
        {1, 0, 1, 1, 0, 0, 0, 0}, // b
        {0, 1, 0, 1, 0, 1, 0, 0}, // c
        {0, 1, 1, 0, 0, 0, 1, 0}, // d
        {1, 0, 0, 0, 0, 1, 0, 0}, // e
        {0, 0, 1, 0, 1, 0, 0, 1}, // f
        {1, 0, 0, 1, 0, 0, 0, 1}, // g
        {1, 0, 0, 0, 0, 1, 1, 0}  // h
    };

    // Duyệt DFS
    string dfsOrder = DFS(n, adj);
    cout << "Thu tu duyet DFS: " << dfsOrder << endl;

    // Duyệt BFS
    string bfsOrder = BFS(n, adj);
    cout << "Thu tu duyet BFS: " << bfsOrder << endl;

    return 0;
}
