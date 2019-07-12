
#include <stdio.h>
#include "stdafx.h"
//#include "sample3.h"


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

