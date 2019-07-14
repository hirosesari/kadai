#pragma once

#define MAZE_ROW    5
#define MAZE_COLUMN 5    

typedef struct
{
	enum MazeKind kind;            //種類(道、壁、スタート、ゴール)
	enum MazeFlag flag;            //ブロックが判明しているかどうか
} MazeBlock;


void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
void MazeGame(int stage);
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
int MazeTitle();