/***********************************************************************
 * File: maze.cpp
 * Author: 劉耀恩 葉祈均
 * Create Date: 2023/06/06
 * Editor: 劉耀恩 葉祈均
 * Update Date: 2023/06/06
 * Description: maze generator
***********************************************************************/
#include "maze.h"
#include <iostream>
#include <vector>
using namespace std;
#define D 1
#define R 2
#define L 4
#define U 8
#define WALL -1
#define NOTHING 2

struct block
{
	int row, column, direction;
	block(int _row, int _column, int _direction)
	{
		row = _row;
		column = _column;
		direction = _direction;
	}
};

struct point
{
	int x;
	int y;
}start, end;

vector<block> myblock;
int x_num = 1, y_num = 1;//礦工位置

//intent: initialize the board
//pre: a 2D array, height and width
//post:
void init(int** board, int height, int width)
{
	//將地圖全部置為牆
	for (int i = 0; i <= height; i++)
		for (int j = 0; j <= width; j++)
			board[i][j] = WALL;
	//定義起始點
	board[1][1] = NOTHING;
	start.x = start.y = 1;
	x_num = y_num = 1;
}

//intent: find the block
//pre: a 2D array, height and width
//post:
void FindBlock(int** board, int height, int width)
{
	//找出與當前位置相鄰的牆
	if (x_num + 1 <= height && board[x_num + 1][y_num] == WALL)
	{//down
		myblock.push_back(block(x_num + 1, y_num, D));
	}
	if (y_num + 1 <= width && board[x_num][y_num + 1] == WALL)
	{//right
		myblock.push_back(block(x_num, y_num + 1, R));
	}
	if (x_num - 1 >= 1 && board[x_num - 1][y_num] == WALL)
	{//up
		myblock.push_back(block(x_num - 1, y_num, U));
	}
	if (y_num - 1 >= 1 && board[x_num][y_num - 1] == WALL)
	{//left
		myblock.push_back(block(x_num, y_num - 1, L));
	}
}

//intent: generate the maze
//pre: a 2D array, height and width
//post:
void  gen(int** board, int height, int width)
{
	init(board, height, width);
	srand((unsigned)time(NULL));//隨機數種子
	FindBlock(board, height, width);
	//第一步壓入兩堵牆（起點右邊和起點下面）進入循環
	while (myblock.size())
	{
		int BlockSize = myblock.size();
		//隨機選擇一堵牆（生成0 ~ BlockSize-1之間的隨機數，同時也是vector裡牆的下標）
		int randnum = rand() % BlockSize;
		block SelectBlock = myblock[randnum];
		x_num = SelectBlock.row;//礦工來到我們“選擇的牆”這裡
		y_num = SelectBlock.column;
		//根據當前選擇的牆的方向進行後續操作
		//此時，起始點 選擇的牆 目標塊 三塊區域在同一直線上
		//我們讓礦工從“選擇的牆”繼續前進到“目標塊”
		//礦工有穿牆能力 ：)
		if (SelectBlock.direction == D)
			x_num++;
		if (SelectBlock.direction == R)
			y_num++;
		if (SelectBlock.direction == L)
			y_num--;
		if (SelectBlock.direction == U)
			x_num--;
		//目標塊如果是牆
		if (board[x_num][y_num] == WALL)
		{
			//打通牆和目標塊
			board[SelectBlock.row][SelectBlock.column] = board[x_num][y_num] = NOTHING;
			//再次找出與礦工當前位置相鄰的牆
			FindBlock(board, height, width);
		}
		//刪除這堵牆(把用不了的牆刪了，對於那些已經施工過了不必再施工了，同時也是確保我們能跳出循環)
		myblock.erase(myblock.begin() + randnum);
	}
}

