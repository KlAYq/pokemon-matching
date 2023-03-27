#pragma once
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

void make_board(char** &board, int m, int n);
void showBoard(char** board, int row, int column, int cellSize, char** background, int bg_row, int bg_column);
void deleteMemBoard(char** &board, int m, int n);