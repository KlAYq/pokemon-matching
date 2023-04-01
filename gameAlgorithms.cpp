#include "gameAlgorithms.h"

bool isInMap(GameState game, int x, int y)
{
    return x >= 0 && x < game.row  && y >= 0 && y < game.col;
}

void setBoard(GameState game, int gameMode)
{
    if (gameMode == 0) // không thụt
        return;
    if (gameMode == 1) // thụt trái
    {
        for (int i = 0; i < game.row; i++)
        {
            for (int j = 0; j < game.col; j++)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = j+1; k < game.col; k++)
                        if (game.board[i][k] != '\0')
                        {
                            swap(game.board[i][j], game.board[i][k]);
                            break;
                        }
                }
            }
        }          
    }
    if (gameMode == 2) // thụt phải
    {
        for (int i = 0; i < game.row; i++)
        {
            for (int j = game.col - 1; j >= 0; j--)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = j-1; k >= 0; k--)
                        if (game.board[i][k] != '\0')
                        {
                            swap(game.board[i][j], game.board[i][k]);
                            break;
                        }
                }
            }
        }  
    }
    if (gameMode == 3) // thụt trên
    {
        for (int j = 0; j < game.col; j++)
        {
            for (int i = 0; i < game.row; i++)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = i+1; k < game.row; k++)
                        if (game.board[k][j] != '\0')
                        {
                            swap(game.board[i][j], game.board[k][j]);
                            break;
                        }
                }
            }
        }  
    }
    if (gameMode == 4) // thut dưới
    {
        for (int j = 0; j < game.col; j++)
        {
            for (int i =  game.row - 1; i >= 0; i--)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = i-1; k >= 0; k--)
                        if (game.board[k][j] != '\0')
                        {
                            swap(game.board[i][j], game.board[k][j]);
                            break;
                        }
                }
            }
        }  
    }
}

vector<pair<int, int>> findPath(GameState game, int _x, int _y, int x, int y)
{
	//INIT Graph
	vector<vector<int>> e(game.row + 2, vector<int>(game.col+ 2, 0));
	for (int i = 0; i < game.row; ++i)
	{
		for (int j = 0; j < game.col; ++j)
		{
			e[i + 1][j + 1] = game.board[i][j] != '\0';
		}
	}
	pair<int, int> s = { _x + 1, _y + 1 };
	pair<int, int> t = { x + 1, y + 1 };

	//BFS
	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };
	queue<pair<int, int>> q;
	vector<vector<pair<int, int>>> trace(e.size(), vector<pair<int, int>>(e[0].size(), make_pair(-1, -1)));
	q.push(t);
	trace[t.first][t.second] = make_pair(-2, -2);
	e[s.first][s.second] = 0;
	e[t.first][t.second] = 0;
	while (!q.empty()) {
		pair <int, int> u = q.front();
		q.pop();
		if (u == s) break;
		for (int i = 0; i < 4; ++i){
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			while (x >= 0 && x < e.size() && y >= 0 && y < e[0].size() && e[x][y] == 0) {
				if (trace[x][y].first == -1){
					trace[x][y] = u;
					q.push({ x, y });
				}
				x += dx[i];
				y += dy[i];
			}
		}
	}

	//trace back
	vector<pair<int, int>> res;
	if (trace[s.first][s.second].first != -1){
		while (s.first != -2) {
			res.push_back({ s.first - 1, s.second - 1 });
			s = trace[s.first][s.second];
		}
	}
	return res;
}

void drawMatchingLine(vector <pair <int, int> > res, int offset_x, int offset_y, int cellSize)
{
    for (int i = 1; i < res.size(); i++)
    {
        int mode;
        int diff_x = res[i].first - res[i-1].first;
        int diff_y = res[i].second - res[i-1].second;
        string s;
        if (diff_x != 0) // vertical change
            mode = 0;
        else // horizontal change
            mode = 1; 
        drawLine(offset_x + res[i-1].first*(cellSize-1) + (cellSize/2), offset_y + res[i-1].second*(cellSize+3-1) + ((cellSize+2)/2), 
                 offset_x + res[i].first*(cellSize-1) + (cellSize/2) , offset_y + res[i].second*(cellSize+3-1) + ((cellSize+2)/2) , mode);
    }
}

void checkMatching(GameState game, char** background, int bg_row, int bg_column, int offset_x, int offset_y, int cellSize)
{
    if (selectedPoint.size() < Max_NumofSelectedPoint) // not enough point
        return;
    
    Point s = selectedPoint[0];
    Point f = selectedPoint[1];

    if (game.board[s.x][s.y] != game.board[f.x][f.y]) // different character
    {  
        showBoard(game, background, bg_row, bg_column, offset_x, offset_y);
        selectedPoint.clear();
        return;
    }


    vector <pair<int, int>> res;
    res = findPath(game, s.x, s.y, f.x, f.y);

    if (res.size() <= 4 && res.size() >= 2) // valid
    {
        string temp;
        temp = game.board[s.x][s.y];
        drawCell(temp, offset_x + s.x*(game.cellSize-1), offset_y + s.y*(game.cellSize + 2), game.cellSize, game.cellSize + 3); // deselecting start cell
        
        temp = game.board[f.x][f.y];
        drawCell(temp, offset_x + f.x*(game.cellSize  - 1), offset_y + f.y*(game.cellSize + 2), game.cellSize, game.cellSize + 3); // deselecting end cell
        
        drawMatchingLine(res, offset_x, offset_y, cellSize);
        this_thread::sleep_for(200ms);

        game.board[s.x][s.y] = '\0';
        game.board[f.x][f.y] = '\0';
        setBoard(game, 4); // thụt lùi theo gameMode
        printBg(background, bg_row, bg_column);
        //showBoard(game, background, bg_row, bg_column, offset_x, offset_y);
    }
    showBoard(game, background, bg_row, bg_column, offset_x, offset_y);
    selectedPoint.clear();
}

bool findPoint(vector <Point> v, Point a)
{
    for (int i = 0; i < v.size(); i++)
        if (v[i].x == a.x && v[i].y == a.y)
            return true;
    return false;
}

void drawSelectedPoint(GameState game, vector <Point> selectedPoint, int offset_x, int offset_y)
{
    string temp; // to convert char to string for drawCell function
    for (int i = 0; i < selectedPoint.size(); i++)
    {
        int x = selectedPoint[i].x;
        int y = selectedPoint[i].y;
        temp = game.board[x][y];
        drawCell(temp, offset_x + x*game.cellSize-x, offset_y + y*(game.cellSize+3)-y, game.cellSize, game.cellSize + 3, 7, 0);
    }
}

void drawSelectingPoint(GameState game, int x, int y, int offset_x, int offset_y)
{
    string temp;
    int mode;
    temp = game.board[cur.x][cur.y];
    if (game.board[cur.x][cur.y] == '\0')
        mode = 1;
    else
        mode = 0;
    // deselecting the old cell
    drawCell(temp, offset_x + cur.x*game.cellSize - cur.x, offset_y + cur.y*(game.cellSize + 3) - cur.y, game.cellSize, game.cellSize + 3, 0, 7, mode);
    if (isInMap(game, cur.x + x, cur.y + y)) 
    {
        cur.x += x;
        cur.y += y;
    } 
    else
    {
        if (cur.x + x >= game.row)
            cur.x = 0;
        else if (cur.x + x < 0)
            cur.x = game.row - 1;
        else if (cur.y + y >= game.col)
            cur.y = 0;
        else if (cur.y + y < 0)
            cur.y = game.col - 1;
    }
    
    temp = game.board[cur.x][cur.y];
    if (game.board[cur.x][cur.y] == '\0')
        mode = 1;
    else
        mode = 0;
    // selecting the new cell
    drawCell(temp, offset_x + cur.x*game.cellSize - cur.x, offset_y + cur.y*(game.cellSize + 3) - cur.y, game.cellSize, game.cellSize + 3, 7, 0, mode); // select the new one
}

void moveSuggestion(GameState game, int offset_x, int offset_y)
{
    for (int i = 0; i < game.row; i++)
    {
        for (int j = 0; j < game.col; j++)
        {
            int startX = i, startY = j;
            for (int i = 0; i < game.row; i++)
            {
                for (int j = 0; j < game.col; j++)
                {
                    if (i == startX && j == startY)
                        continue;
                    if (game.board[startX][startY] != game.board[i][j])
                        continue;
                    if (game.board[i][j] == '\0')
                        continue;

                    vector <pair <int, int> > res;
                    res = findPath(game, startX, startY, i, j);

                    if (res.size() <= 4 && res.size() >= 2) // valid path
                    {
                        string temp;
                        temp = game.board[startX][startY];
                        drawCell(temp, offset_x + startX*game.cellSize - startX, offset_y + startY*(game.cellSize + 3) - startY, game.cellSize, game.cellSize + 3, 10, 0);
                        return;
                    }

                }
            }
        }
    }
    
    // If there is no possible move
    // do something...
}

void playerAction(GameState game, int  offset_x, int offset_y, int &page) 
{
    char c = getch(); // get direct input
    int x = 0, y = 0;
    switch (c){ 
    case 's':
        x = 1;
        break;
    case 'd':
        y = 1;
        break;
    case 'a':
        y = -1;
        break;
    case 'w':
        x = -1;
        break;
    case ' ':
        {
            if (game.board[cur.x][cur.y] != '\0') // if the cur cell has block
            {
                if (findPoint(selectedPoint, cur) == true) // if already selected
                {
                    // Deselect point
                    for (int i = 0; i < selectedPoint.size(); i++)
                        if (selectedPoint[i].x == cur.x && selectedPoint[i].y == cur.y)
                            selectedPoint.erase(selectedPoint.begin() + i);
                }
                else // if not, select that point
                {
                    if (selectedPoint.size() < Max_NumofSelectedPoint) // check if number of selected point exceed the limit
                    {
                        selectedPoint.push_back({cur.x, cur.y});
                    }
                }
            }
        }
        break;
    case 27: //Esc = 27
        page = 1;
        break;
    case 'h':
        moveSuggestion(game, offset_x, offset_y);
        break;
    }
    if (x != 0 || y != 0) // there is a movement input
        drawSelectingPoint(game, x, y, offset_x, offset_y);
}