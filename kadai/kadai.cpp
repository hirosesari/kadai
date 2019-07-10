#include <stdio.h>
#include "stdafx.h"
#define STAGE       2      //�X�e�[�W��
#define MAZE_ROW    5      //���H�̍s��
#define MAZE_COLUMN 5      //���H�̗�


//�v���C���[
typedef struct
{
	int row;        //�v���C���[�ʒu(�s)B
	int column;     //�v���C���[�ʒu(��)
}MazePlayer;


//���H�̈�u���b�N
enum MazeKind { PATH, WALL, START, GOAL };    //�u���b�N�̎��(���A�ǁA�X�^�[�g�A�S�[��)
enum MazeFlag { FALSE, TRUE };                //�u���b�N���������Ă��邩�ǂ���

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
			else if (maze[i][j].flag == FALSE) //�u���b�N���������Ă��Ȃ��ꍇ
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
			maze[*playerRow - 1][*playerColumn].flag = TRUE; //�u���b�N�̎�ނ�����

			if (maze[*playerRow - 1][*playerColumn].kind != WALL) //�ǂ��ǂ����m�F
			{
				*playerRow -= 1; //�ړ�
				printf("\n��Ɉړ����܂����B\n");
			}
			else
			{
				printf("\n�ǂł��B\n");
			}
		}
		else
		{
			printf("\n�͈͊O�ł�\n");

		}
	}
	break;

	//���ړ�
	case DOWN:
	{
		if (*playerRow + 1 < MAZE_ROW)
		{
			maze[*playerRow + 1][*playerColumn].flag = TRUE;

			if (maze[*playerRow + 1][*playerColumn].kind != WALL)
			{
				*playerRow += 1;
				printf("\n���Ɉړ����܂����B\n");
			}
			else
			{
				printf("\n�ǂł��B\n");
			}
		}
		else
		{
			printf("\n�͈͊O�ł�\n");

		}
	}
	break;

	//���ړ�
	case LEFT:
	{
		if (*playerColumn - 1 >= 0)
		{
			maze[*playerRow][*playerColumn - 1].flag = TRUE;

			if (maze[*playerRow][*playerColumn - 1].kind != WALL)
			{
				*playerColumn -= 1;
				printf("\n���Ɉړ����܂����B\n");
			}
			else
			{
				printf("\n�ǂł��B\n");
			}
		}
		else
		{
			printf("\n�͈͊O�ł�\n");

		}
	}
	break;

	//�E�ړ�
	case RIGHT:
	{
		if (*playerColumn + 1 < MAZE_COLUMN)
		{
			maze[*playerRow][*playerColumn + 1].flag = TRUE;

			if (maze[*playerRow][*playerColumn + 1].kind != WALL)
			{
				*playerColumn += 1;
				printf("\n�E�Ɉړ����܂����B\n");
			}
			else
			{
				printf("\n�ǂł��B\n");
			}
		}
		else
		{
			printf("\n�͈͊O�ł�\n");

		}
	}
	break;
	}
}


//�S�[������
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	if (maze[playerRow][playerColumn].kind == GOAL) //�v���C���[�ʒu���S�[���n�_�ɓ�����
	{
		printf("�S�[��!\n");
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
			{ { START, TRUE } ,{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE } },
			{ { WALL , FALSE } ,{ WALL , FALSE },{ PATH , FALSE },{ WALL , FALSE },{ WALL , FALSE } },
			{ { WALL , FALSE } ,{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE } },
			{ { PATH , FALSE } ,{ PATH , FALSE },{ WALL , FALSE },{ WALL , FALSE },{ WALL , FALSE } },
			{ { WALL , FALSE } ,{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE },{ GOAL , TRUE } },
		},

		{ //STAGE1
			{ { PATH , FALSE } ,{ WALL , FALSE },{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE } },
			{ { PATH , FALSE } ,{ WALL , FALSE },{ PATH , FALSE },{ WALL , FALSE },{ PATH , FALSE } },
			{ { START, TRUE } ,{ PATH , FALSE },{ PATH , FALSE },{ WALL , FALSE },{ GOAL , TRUE } },
			{ { PATH , FALSE } ,{ WALL , FALSE },{ WALL , FALSE },{ WALL , FALSE },{ WALL , FALSE } },
			{ { PATH , FALSE } ,{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE },{ PATH , FALSE } },
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

