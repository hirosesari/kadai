#include "meiro2.h"
#include "stdafx.h"
#include <stdio.h>


#define MEIRO_LINE    5
#define MEIRO_COLUMN 5    
#define STAGE 3
#define CHARBUFF 124
enum MeiroKind { PATH, WALL, START, GOAL };    //�u���b�N�̎��(���A�ǁA�X�^�[�g�A�S�[��)
enum MeiroFlag { MARU, BATU };                //�u���b�N���������Ă��邩�ǂ���			
enum MeiroDirection { UP, DOWN, LEFT, RIGHT, Invalid };   //����	
enum MeiroMenu { STAGE1, STAGE2, STAGE3, EXIT };  // ���j���[


char *data1;  //ini�t�@�C���̒��g
char *data2;  //ini�t�@�C���̒��g
char *data3;  //ini�t�@�C���̒��g
char *data4;  //ini�t�@�C���̒��g
char *data5;  //ini�t�@�C���̒��g
char *data6;  //ini�t�@�C���̒��g
char section[CHARBUFF];
int cnt = 0;


typedef struct {
	enum MeiroKind kind;            //���(���A�ǁA�X�^�[�g�A�S�[��)
	enum MeiroFlag flag;            //�u���b�N���������Ă��邩�ǂ���
} MeiroTile;



typedef struct {
	int line;        //�v���C���[�ʒu(�s)B
	int column;     //�v���C���[�ʒu(��)
}MeiroPlayer;


//�^�C�g��
int MeiroTitle() {
	char buf[100];
	int menu = -1;

	printf("\n\n���������� ���H ����������\n\n");
	printf("���j���[\n");
	printf("%d : �X�e�[�W1\n", STAGE1);
	printf("%d : �X�e�[�W2\n", STAGE2);
	printf("%d : �X�e�[�W3\n", STAGE3);
	printf("%d : �I��\n\n", EXIT);
	printf("�I�I�X�e�[�W��I��ł��������I�I �� ");

	fgets(buf, sizeof(buf), stdin);
	sscanf_s(buf, "%d", &menu);

	while (menu < 0 || menu > 3)	//�O�����ƂS�ȏ�̏ꍇ��I�񂾂�ē���
	{
		printf("���͂�����������܂���B�ē��͂��Ă������� �� ");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &menu);
	}

	return menu;
}




//�v���C���[�ړ�

void MeiroPlayerMove(int *playerLine, int *playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {
	char buf[100];
	int  direction = -1;

	printf("\n");
	printf("%d : ��Ɉړ�\n", UP);
	printf("%d : ���Ɉړ�\n", DOWN);
	printf("%d : ���Ɉړ�\n", LEFT);
	printf("%d : �E�Ɉړ�\n\n", RIGHT);
	printf("�ړ����������I��ł������� �� ");

	fgets(buf, sizeof(buf), stdin);      //������œ��͂�ǂݍ���
	sscanf_s(buf, "%d", &direction);        //�����ɂł���ꍇ�͕ϊ�(�ł��Ȃ���Ή������Ȃ�)

	while (direction < 0 || direction > 3) //���͂��������ꍇ�܂ŌJ��Ԃ�
	{
		printf("���͂��s���ł��B�ē��͂��Ă������� �� ");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &direction);

	}


	switch (direction) {
		//��ړ�
	case UP: {
		if (*playerLine - 1 >= 0) {//���H�͈̔͊O�łȂ����Ƃ��m�F
			meiro[*playerLine - 1][*playerColumn].flag = MARU; //�u���b�N�̎�ނ�����

			if (meiro[*playerLine - 1][*playerColumn].kind != WALL) {//�ǂ��ǂ����m�F
				*playerLine -= 1; //�ړ�
				printf("\n%s\n\n", data1);
				cnt++;
			}
			else {
				printf("\n%s\n\n", data5);
				cnt++;
			}
		}
		else {
			printf("\n%s\n\n", data6);
			cnt++;
		}
	}
			 break;


			 //���ړ�
	case DOWN: {

		if (*playerLine + 1 < MEIRO_LINE) {
			meiro[*playerLine + 1][*playerColumn].flag = MARU;

			if (meiro[*playerLine + 1][*playerColumn].kind != WALL) {
				*playerLine += 1;
				printf("\n%s\n\n", data2);
				cnt++;
			}
			else {
				printf("\n%s\n\n", data5);
				cnt++;
			}
		}
		else {
			printf("\n%s\n\n", data6);
			cnt++;
		}
	}
		   break;

			   //���ړ�
	case LEFT: {
		if (*playerColumn - 1 >= 0) {
			meiro[*playerLine][*playerColumn - 1].flag = MARU;

			if (meiro[*playerLine][*playerColumn - 1].kind != WALL) {
				*playerColumn -= 1;
				printf("\n%s\n\n", data3);
				cnt++;
			}
			else {
				printf("\n%s\n\n", data5);
				cnt++;
			}
		}
		else {
			printf("\n%s\n\n", data6);
			cnt++;
		}
	}
			   break;

		   //�E�ړ�
	case RIGHT: {
		if (*playerColumn + 1 < MEIRO_COLUMN) {
			meiro[*playerLine][*playerColumn + 1].flag = MARU;

			if (meiro[*playerLine][*playerColumn + 1].kind != WALL) {
				*playerColumn += 1;
				printf("\n%s\n\n", data4);
				cnt++;

			}
			else {
				printf("\n%s\n\n", data5);
				cnt++;
			}
		}
		else {
			printf("\n%s\n\n", data6);
			cnt++;

		}
	}
				break;
	}
}




//�v���C���[������
int MeiroPlayerInit(int *playerLine, int *playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {

	int i, j;

	for (i = 0; i < MEIRO_LINE; i++) { //�s

		for (j = 0; j < MEIRO_COLUMN; j++) { //��

			if (meiro[i][j].kind == START) {//�X�^�[�g�n�_�Ȃ�΃v���C���[�̈ʒu�ɐݒ肷��

				*playerLine = i;
				*playerColumn = j;
				return 0; //�֐��I��(�v���C���[��ݒ�ł���Ύc��̏����͕K�v�Ȃ�)
			}
		}
	}
}



//�S�[������
int MeiroGoalCheck(int playerLine, int playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {

	if (meiro[playerLine][playerColumn].kind == GOAL) { //�v���C���[�ʒu���S�[���n�_�ɓ�����

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
			fprintf_s(fp, "�����l�ł���");
		}
		fclose(fp);

		return 1;
	}
	return 0;
}

//���H�\��
void MeiroDraw(int playerLine, int playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {
	int i, j;

	for (i = 0; i < MEIRO_LINE; i++) { //�s

		for (j = 0; j < MEIRO_COLUMN; j++) { //��

			if (i == playerLine && j == playerColumn) { //�v���C���[�ʒu

				printf("��");

			}
			else if (meiro[i][j].flag == BATU) { //�u���b�N���������Ă��Ȃ��ꍇ

				printf("�H");

			}
			else {

				switch (meiro[i][j].kind) {

				case WALL:
					printf("�~");
					break; //��

				case GOAL:
					printf("�f");
					break; //�S�[��

				default:
					printf("�@");
					break; //���̑�(���A�X�^�[�g)
				}
			}
		}
		printf("\n");

	}
}


//���H�Q�[��
void MeiroGame(int stage) {

	//�v���C���[
	MeiroPlayer player;

	//���H
	MeiroTile meiro[STAGE][MEIRO_LINE][MEIRO_COLUMN] =  //MEIRO_LINE:�s MEIRO_COLUMN: ��
	{
		{ //STAGE1
			{ { START, MARU } ,{ WALL , BATU },{ WALL , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { WALL , BATU } ,{ WALL , BATU },{ PATH , BATU },{ WALL , BATU },{ WALL , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ WALL , BATU },{ WALL , BATU },{ GOAL , MARU } },
		},

		{ //STAGE2
			{ { PATH , BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ GOAL , MARU } },
			{ { PATH , BATU } ,{ WALL , BATU },{ WALL , BATU },{ WALL , BATU },{ WALL , BATU } },
			{ { PATH, BATU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
			{ { WALL , BATU } ,{ WALL , BATU },{ WALL , BATU },{ WALL , BATU },{ PATH , BATU } },
			{ { START , MARU } ,{ PATH , BATU },{ PATH , BATU },{ PATH , BATU },{ PATH , BATU } },
		},

		{ //STAGE3
			{ { PATH, BATU } ,{ PATH , BATU },{ PATH , BATU },{ WALL , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ START , MARU },{ PATH , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ WALL , BATU },{ PATH , BATU },{ WALL , BATU } },
			{ { PATH , BATU } ,{ WALL , BATU },{ GOAL , MARU },{ PATH , BATU },{ PATH , BATU } },
			{ { PATH , BATU } ,{ PATH , BATU },{ WALL , BATU },{ WALL , BATU },{ PATH , BATU } },
		},
	};

	//�v���C���[������
	if (MeiroPlayerInit(&player.line, &player.column, meiro[stage]) == -1)
	{
		//�֐�MeiroPlayerInit��-1��Ԃ��Ƃ��������Ɏ��s���Ă���
		//����āA���̎��_�Ńv���O�������I�����A���H�̕\���͍s��Ȃ�
		return;
	}


	while (MeiroGoalCheck(player.line, player.column, meiro[stage]) != 1) //�S�[������܂ňړ����J��Ԃ�
	{
		//���H�\��
		MeiroDraw(player.line, player.column, meiro[stage]);
		//�v���C���[�ړ�
		MeiroPlayerMove(&player.line, &player.column, meiro[stage]);
	}

	//���H�ŏI���ʕ\��
	MeiroDraw(player.line, player.column, meiro[stage]);
}



