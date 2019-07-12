#include <stdio.h>
#include "stdafx.h"
#include "sample3.h"
#
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

#define CHARBUFF 124
#define STAGE       2      //�X�e�[�W��
#define MAZE_ROW    5      //���H�̍s��
#define MAZE_COLUMN 5      //���H�̗�

char *kind1 = { "1" };
char *kind2 = { "2" };
char *kind3 = { "3" };
char *kind4 = { "4" };
char *kind5 = { "5" };
char *kind6 = { "6" };
char *title = { "section1" };
char strText[1024];
char *endp;
char keyValue1[1024];
char keyValue2[1024];
char keyValue3[1024];
char keyValue4[1024];
char keyValue5[1024];
char keyValue6[1024];
char *data1;
char *data2;
char *data3;
char *data4;
char *data5;
char *data6;
char section[CHARBUFF];

int cnt = 0;



void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//�v���C���[
typedef struct
{
	int row;        //�v���C���[�ʒu(�s)B
	int column;     //�v���C���[�ʒu(��)
}MazePlayer;


//���H�̈�u���b�N
enum MazeKind { PATH, WALL, START, GOAL };    //�u���b�N�̎��(���A�ǁA�X�^�[�g�A�S�[��)
enum MazeFlag { BATU, MARU };                //�u���b�N���������Ă��邩�ǂ���


typedef struct
{
	enum MazeKind kind;            //���(���A�ǁA�X�^�[�g�A�S�[��)
	enum MazeFlag flag;            //�u���b�N���������Ă��邩�ǂ���
} MazeBlock;


//�v���C���[������
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	int i, j;

	for (i = 0; i < MAZE_ROW; i++) //�s
	{
		for (j = 0; j < MAZE_COLUMN; j++) //��
		{
			if (maze[i][j].kind == START) //�X�^�[�g�n�_�Ȃ�΃v���C���[�̈ʒu�ɐݒ肷��
			{
				*playerRow = i;
				*playerColumn = j;
				return 0; //�֐��I��(�v���C���[��ݒ�ł���Ύc��̏����͕K�v�Ȃ�)
			}
		}
	}

	//�X�^�[�g�n�_���Ȃ���΁A�v���C���[��ݒ�ł��������܂ł���
	printf("�X�^�[�g������܂���\n");
	return -1;
}


//���H�\��
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	int i, j;

	for (i = 0; i < MAZE_ROW; i++) //�s
	{
		for (j = 0; j < MAZE_COLUMN; j++) //��
		{
			if (i == playerRow && j == playerColumn) //�v���C���[�ʒu
			{
				printf("�o");
			}
			else if (maze[i][j].flag == BATU) //�u���b�N���������Ă��Ȃ��ꍇ
			{
				printf("�H");
			}
			else
			{
				switch (maze[i][j].kind)
				{
				case WALL:
					printf("��"); break; //��
				case GOAL:
					printf("�f"); break; //�S�[��
				default:
					printf("�@"); break; //���̑�(���A�X�^�[�g)
				}
			}
		}
		printf("\n");
	}
}


//����
enum MazeDirection { UP, DOWN, LEFT, RIGHT, Invalid };
/*
//�v���C���[�ړ�
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	char buf[100];
	int  direction = -1;

	printf("%d:��\n", UP);
	printf("%d:��\n", DOWN);
	printf("%d:��\n", LEFT);
	printf("%d:�E\n", RIGHT);
	printf("��������͂��Ă��������B�F");

	fgets(buf, sizeof(buf), stdin);      //������œ��͂�ǂݍ���
	sscanf_s(buf, "%d", &direction);        //�����ɂł���ꍇ�͕ϊ�(�ł��Ȃ���Ή������Ȃ�)

	while (direction < 0 || direction >(Invalid - 1)) //���͂��������ꍇ�܂ŌJ��Ԃ�
	{
		printf("���͂��s���ł��B�ē��͂��Ă�������:");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &direction);
	}


	switch (direction) {
		//��ړ�
	case UP:
	{
		if (*playerRow - 1 >= 0) //���H�͈̔͊O�łȂ����Ƃ��m�F
		{
			maze[*playerRow - 1][*playerColumn].flag = MARU; //�u���b�N�̎�ނ�����

			if (maze[*playerRow - 1][*playerColumn].kind != WALL) //�ǂ��ǂ����m�F
			{
				*playerRow -= 1; //�ړ�
				printf("\n%s\n", data1);
				cnt++;
			}
			else
			{
				printf("\n%s\n", data5);
				cnt++;
			}
		}
		else
		{
			printf("\n%s\n", data6);
			cnt++;

		}
	}
	break;

	//���ړ�
	case DOWN:
	{
		if (*playerRow + 1 < MAZE_ROW)
		{
			maze[*playerRow + 1][*playerColumn].flag = MARU;

			if (maze[*playerRow + 1][*playerColumn].kind != WALL)
			{
				*playerRow += 1;
				printf("\n%s\n", data2);
				cnt++;
			}
			else
			{
				printf("\n%s\n", data5);
				cnt++;
			}
		}
		else
		{
			printf("\n%s\n", data6);
			cnt++;

		}
	}
	break;

	//���ړ�
	case LEFT:
	{
		if (*playerColumn - 1 >= 0)
		{
			maze[*playerRow][*playerColumn - 1].flag = MARU;

			if (maze[*playerRow][*playerColumn - 1].kind != WALL)
			{
				*playerColumn -= 1;
				printf("\n%s\n", data3);
				cnt++;
			}
			else
			{
				printf("\n%s\n", data5);
				cnt++;
			}
		}
		else
		{
			printf("\n%s\n", data6);
			cnt++;

		}
	}
	break;

	//�E�ړ�
	case RIGHT:
	{
		if (*playerColumn + 1 < MAZE_COLUMN)
		{
			maze[*playerRow][*playerColumn + 1].flag = MARU;

			if (maze[*playerRow][*playerColumn + 1].kind != WALL)
			{
				*playerColumn += 1;
				printf("\n%s\n", data4);
				cnt++;
			}
			else
			{
				printf("\n%s\n", data5);
				cnt++;
			}
		}
		else
		{
			printf("\n%s\n", data6);
			cnt++;

		}
	}
	break;
	}
}
*/


//�S�[������
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	if (maze[playerRow][playerColumn].kind == GOAL) //�v���C���[�ʒu���S�[���n�_�ɓ�����
	{
		printf("�S�[��!\n");
		fprintf_s(stdout, "\n%d��ŃS�[�����܂���\n", cnt);
		return 1;
	}
	return 0;
}


//���H�Q�[��
void MazeGame(int stage)
{
	//�v���C���[
	MazePlayer player;

	//���H
	MazeBlock maze[STAGE][MAZE_ROW][MAZE_COLUMN] =
	{
		{ //STAGE0
			{ { START, MARU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { WALL , BATU } ,{ WALL , BATU },{ PATH , BATU },{ WALL , BATU },{ WALL , BATU } },
			{ { WALL , BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ WALL , BATU },{ WALL , BATU },{ WALL , BATU } },
			{ { WALL , BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ GOAL , MARU } },
		},

		{ //STAGE1
			{ { PATH , BATU } ,{ WALL , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ WALL , BATU },{ PATH , BATU },{ WALL , BATU },{ PATH , BATU } },
			{ { START, MARU } ,{ PATH , BATU },{ PATH , BATU },{ WALL , BATU },{ GOAL , MARU } },
			{ { PATH , BATU } ,{ WALL , BATU },{ WALL , BATU },{ WALL , BATU },{ WALL , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
		}
	};

	//�v���C���[������
	if (MazePlayerInit(&player.row, &player.column, maze[stage]) == -1)
	{
		//�֐�MazePlayerInit��-1��Ԃ��Ƃ��������Ɏ��s���Ă���
		//����āA���̎��_�Ńv���O�������I�����A���H�̕\���͍s��Ȃ�
		return;
	}

	while (MazeGoalCheck(player.row, player.column, maze[stage]) != 1) //�S�[������܂ňړ����J��Ԃ�
	{
		//���H�\��
		MazeDraw(player.row, player.column, maze[stage]);
		//�v���C���[�ړ�
		MazePlayerMove(&player.row, &player.column, maze[stage]);
	}

	//���H�ŏI���ʕ\��
	MazeDraw(player.row, player.column, maze[stage]);
}


//���j���[
enum MazeMenu { STAGE0, STAGE1, EXIT };

//�^�C�g��
int MazeTitle()
{
	char buf[100];
	int menu = -1;

	printf("\n\n���������H�Q�[��������\n\n");

	printf("���j���[\n");
	printf("%d:�X�e�[�W0\n", STAGE0);
	printf("%d:�X�e�[�W1\n", STAGE1);
	printf("%d:�I��\n", EXIT);

	printf("���j���[��I��ł��������B�F");

	fgets(buf, sizeof(buf), stdin);
	sscanf_s(buf, "%d", &menu);

	while (menu < 0 || menu > EXIT)
	{
		printf("���͂��s���ł��B�ē��͂��Ă�������:");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &menu);
	}

	return menu;
}


int main(void)
{
	int menu;
	int stage;

	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);


	char section[CHARBUFF];
	sprintf_s(section, title);

	char keyWord1[CHARBUFF];
	sprintf_s(keyWord1, kind1);

	char keyWord2[CHARBUFF];
	sprintf_s(keyWord2, kind2);

	char keyWord3[CHARBUFF];
	sprintf_s(keyWord3, kind3);

	char keyWord4[CHARBUFF];
	sprintf_s(keyWord4, kind4);

	char keyWord5[CHARBUFF];
	sprintf_s(keyWord5, kind5);

	char keyWord6[CHARBUFF];
	sprintf_s(keyWord6, kind6);

	char File[CHARBUFF];
	sprintf_s(File, "%s\\maze.ini", currentDirectory);


	if (GetPrivateProfileString(section, keyWord1, "none", keyValue1, CHARBUFF, File) != 0) {
		data1 = keyValue1;
		fprintf(stdout, "%s\n", data1);

	}

	if (GetPrivateProfileString(section, keyWord2, "none", keyValue2, CHARBUFF, File) != 0) {
		data2 = keyValue2;
		fprintf(stdout, "%s\n", data2);

	}

	if (GetPrivateProfileString(section, keyWord3, "none", keyValue3, CHARBUFF, File) != 0) {
		data3 = keyValue3;
		fprintf(stdout, "%s\n", data3);

	}

	if (GetPrivateProfileString(section, keyWord4, "none", keyValue4, CHARBUFF, File) != 0) {
		data4 = keyValue4;
		fprintf(stdout, "%s\n", data4);

	}

	if (GetPrivateProfileString(section, keyWord5, "none", keyValue5, CHARBUFF, File) != 0) {
		data5 = keyValue5;
		fprintf(stdout, "%s\n", data5);
	}

	if (GetPrivateProfileString(section, keyWord6, "none", keyValue6, CHARBUFF, File) != 0) {
		data6 = keyValue6;
		fprintf(stdout, "%s\n", data6);

	}

	//data[i] = keyValue;
	//fprintf(stdout, "%s\n", data[i]);


	while (1)
	{
		//���j���[�I��      
		menu = MazeTitle();
		printf("\n");

		if (menu == EXIT) //EXIT�Ȃ�while���[�v�𔲂��ďI��
		{
			break;
		}
		else
		{
			//�X�e�[�W�ݒ�
			switch (menu)
			{
			case STAGE0:
				stage = 0;
				break;

			case STAGE1:
				stage = 1;
				break;
			}
		}

		//���H�Q�[��
		MazeGame(stage);

		//�Q�[�����I����while���[�v�̐擪�ɂ��ǂ�
	}



	return 0;
}

