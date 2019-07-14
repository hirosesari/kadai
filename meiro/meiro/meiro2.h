#pragma once

#define MEIRO_LINE    5
#define MEIRO_COLUMN 5    

typedef struct
{
	enum MeiroKind kind;            //���(���A�ǁA�X�^�[�g�A�S�[��)
	enum MeiroFlag flag;            //�u���b�N���������Ă��邩�ǂ���
} MeiroTile;

void MeiroDraw(int playerLine, int playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]);
void MeiroGame(int stage);
int MeiroPlayerInit(int *playerLine, int *playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]);
void MeiroPlayerMove(int *playerLine, int *playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]);
int MeiroGoalCheck(int playerLine, int playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]);
int MeiroTitle();