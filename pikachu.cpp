#include <iostream>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stack>

#define MAX 100

using namespace std;

void make_board(char board[][MAX], int& m, int& n) {
    srand(time(NULL));
    m = 8;
    n = 8;
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);

    std::vector<std::pair<int, int>> avail_pos;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
                board[i][j] = '#';
            } else {
                avail_pos.push_back(std::make_pair(i, j));
            }
        }
    }
    const int pairs = avail_pos.size() / 2;
    for (int i = 0; i < pairs; i++) {
        char c = alphabet[rand() % alphabet_size];

        int pos1 = rand() % avail_pos.size();
        int pos2 = rand() % avail_pos.size();
        while (pos1 == pos2) { // if same position is selected
            pos2 = rand() % avail_pos.size(); // select next position
        }

        board[avail_pos[pos1].first][avail_pos[pos1].second] = c;
        board[avail_pos[pos2].first][avail_pos[pos2].second] = c;

        avail_pos.erase(avail_pos.begin() + max(pos1, pos2));

        avail_pos.erase(avail_pos.begin() + min(pos1, pos2));
    }
}


void draw_board(char a[][MAX], int m, int n)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0 ; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

bool is_valid_path(char board[][MAX], int m, int n, int r1, int c1, int r2, int c2, int max_turns, int num_turns) {
    if (r1 < 0 || r1 >= m || c1 < 0 || c1 >= n || r2 < 0 || r2 >= m || c2 < 0 || c2 >= n) {
        // Out of bounds
        return false;
    }

    if (num_turns > max_turns) {
        // Too many turns
        return false;
    }

    if (board[r1][c1] != board[r2][c2]) {
        // Different letters
        return false;
        cout << "abc" << endl;
    }

    if (r1 == r2 && c1 == c2) {
        // Same cell
        return true;
    }

    // Check L path
    if ((r1 == r2 && abs(c1 - c2) == 1) || (c1 == c2 && abs(r1 - r2) == 1)) {
        return true;
    }

    // Check U path using DFS
    bool visited[MAX][MAX] = {false};
    stack<pair<int, int>> s;

    s.push(make_pair(r1, c1));

    while (!s.empty()) {
        pair<int, int> p = s.top();
        s.pop();

        int r = p.first;
        int c = p.second;

        if (r == r2 && c == c2) {
            return true;
        }

        // Visit adjacent cells
        if (r > 0 && !visited[r-1][c] && board[r-1][c] == ' ') {
            visited[r-1][c] = true;
            s.push(make_pair(r-1, c));
        }
        if (r < m-1 && !visited[r+1][c] && board[r+1][c] == ' ') {
            visited[r+1][c] = true;
            s.push(make_pair(r+1, c));
        }
        if (c > 0 && !visited[r][c-1] && board[r][c-1] == ' ') {
            visited[r][c-1] = true;
            s.push(make_pair(r, c-1));
        }
        if (c < n-1 && !visited[r][c+1] && board[r][c+1] == ' ') {
            visited[r][c+1] = true;
            s.push(make_pair(r, c+1));
        }
    }

    return false;
}


void play_game(char board[][MAX], int m, int n)
{
    int num_turns = 0;
    int max_turns = 3;
    while (num_turns < max_turns) {
        // Draw the updated board
        draw_board(board, m, n);

        // Get the user's input for the first tile
        pair<int, int> tile1_pos;
        cout << "Enter the row and column of the first tile: ";
        cin >> tile1_pos.first >> tile1_pos.second;

        // Get the user's input for the second tile
        pair<int, int> tile2_pos;
        cout << "Enter the row and column of the second tile: ";
        cin >> tile2_pos.first >> tile2_pos.second;

        // Check if the tiles match and remove them if they do
        if (is_valid_path(board, m, n, tile1_pos.first, tile1_pos.second, tile2_pos.first, tile2_pos.second, max_turns, num_turns )) {
            cout << "Tiles match!" << endl;
            board[tile1_pos.first][tile1_pos.second] = ' ';
            board[tile2_pos.first][tile2_pos.second] = ' ';
        }
        else {
            cout << "Tiles do not match." << endl;
        }

        // Increment the number of turns
        num_turns++;
    }
}

int main()
{
    char board[MAX][MAX];
    int row, column;
    make_board(board, row, column);
    play_game(board, row, column);

    return 0;
}