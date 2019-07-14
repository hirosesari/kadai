#include "sample22.h"
#include "stdafx.h"
#include <stdio.h>


#define MAZE_ROW    5
#define MAZE_COLUMN 5    
#define STAGE 2
#define CHARBUFF 124
enum MazeKind { PATH, WALL, START, GOAL };    //�u���b�N�̎��(���A�ǁA�X�^�[�g�A�S�[��)
enum MazeFlag { MARU, BATU };                //�u���b�N���������Ă��邩�ǂ���			
enum MazeDirection { UP, DOWN, LEFT, RIGHT, Invalid };   //����	
enum MazeMenu { STAGE0, STAGE1, EXIT };  // ���j���[


char *data1;  //ini�t�@�C���̒��g
char *data2;  //ini�t�@�C���̒��g
char *data3;  //ini�t�@�C���̒��g
char *data4;  //ini�t�@�C���̒��g
char *data5;  //ini�t�@�C���̒��g
char *data6;  //ini�t�@�C���̒��g
char section[CHARBUFF];
int cnt = 0;





typedef struct
{
	enum MazeKind kind;            //���(���A�ǁA�X�^�[�g�A�S�[��)
	enum MazeFlag flag;            //�u���b�N���������Ă��邩�ǂ���
} MazeBlock;



typedef struct
{
	int row;        //�v���C���[�ʒu(�s)B
	int column;     //�v���C���[�ʒu(��)
}MazePlayer;


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




//�S�[������
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	if (maze[playerRow][playerColumn].kind == GOAL) //�v���C���[�ʒu���S�[���n�_�ɓ�����
	{
		printf("�S�[��!\n");
		printf("�J�E���g�񐔂�%d�ł�\n", cnt);

		FILE *fp;
		errno_t error;
		error = fopen_s(&fp, "textOut.csv", "w");
		if (error != 0) {
			fprintf_s(stderr, "failed to open(w)");
			return(9);
		}
		else {
			fprintf_s(fp, "�S�̂̑���񐔂�%d�ł��B\n", cnt);


			if (cnt == 10) {
				fprintf_s(fp, "�ŒZ���[�g�ł��B���߂łƂ��������܂��B\n");
			}
			fprintf_s(fp, "�����l�ł���");
		}
		fclose(fp);

		return 1;
	}
	return 0;
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



//���H�Q�[��
void MazeGame(int stage)
{
	//�v���C���[
	MazePlayer player;

	//���H
	MazeBlock maze[STAGE][MAZE_ROW][MAZE_COLUMN] =  //MAZE_ROW:�s MAZE_COLUMN: ��
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




