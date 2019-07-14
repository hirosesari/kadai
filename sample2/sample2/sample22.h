#pragma once

#define MAZE_ROW    5
#define MAZE_COLUMN 5    

typedef struct
{
	enum MazeKind kind;            //���(���A�ǁA�X�^�[�g�A�S�[��)
	enum MazeFlag flag;            //�u���b�N���������Ă��邩�ǂ���
} MazeBlock;


void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
void MazeGame(int stage);
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]);
int MazeTitle();