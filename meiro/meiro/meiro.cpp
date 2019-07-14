#include <stdio.h>
#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "meiro2.h"


#define CHARBUFF 124
#define MEIRO_LINE    5      //���H�̍s��
#define MEIRO_COLUMN 5      //���H�̗�
#define STAGE 3

char *title[1] = { "section1" };
char *sikibetu[6] = { "1","2","3","4","5","6" };
char strText[1024], *e;
char keyValue1[1024];
char keyValue2[1024];
char keyValue3[1024];
char keyValue4[1024];
char keyValue5[1024];
char keyValue6[1024];


extern char *data1;  //ini�t�@�C���̒��g
extern char *data2;  //ini�t�@�C���̒��g
extern char *data3;  //ini�t�@�C���̒��g
extern char *data4;  //ini�t�@�C���̒��g
extern char *data5;  //ini�t�@�C���̒��g
extern char *data6;  //ini�t�@�C���̒��g
		

//�v���C���[
typedef struct
{
	int line;        //�v���C���[�ʒu(�s)B
	int column;     //�v���C���[�ʒu(��)
}MeiroPlayer;


void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}



//���H�̈�u���b�N
enum MeiroKind { PATH, WALL, START, GOAL };    //�u���b�N�̎��(���A�ǁA�X�^�[�g�A�S�[��)
enum MeiroFlag { MARU, BATU };                //�u���b�N���������Ă��邩�ǂ���



//���j���[
enum MeiroMenu { STAGE1, STAGE2, STAGE3, EXIT };



int main(void)
{
	int menu;
	int stage;

	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);


	for (int j = 0; j < 6; j++) {
		char section[CHARBUFF];
		sprintf_s(section, "section1");


		char keyWord[CHARBUFF];
		sprintf_s(keyWord, sikibetu[j]);


		char File[CHARBUFF];
		sprintf_s(File, "%s\\meiro.ini", currentDirectory);


		if (j == 0) {
			if (GetPrivateProfileString(section, keyWord, "none", keyValue1, CHARBUFF, File) != 0) {
				data1 = keyValue1;
			}
		}


		if (j == 1) {
			if (GetPrivateProfileString(section, keyWord, "none", keyValue2, CHARBUFF, File) != 0) {
				data2 = keyValue2;
			}
		}


		if (j == 2) {
			if (GetPrivateProfileString(section, keyWord, "none", keyValue3, CHARBUFF, File) != 0) {
				data3 = keyValue3;
			}
		}


		if (j == 3) {
			if (GetPrivateProfileString(section, keyWord, "none", keyValue4, CHARBUFF, File) != 0) {
				data4 = keyValue4;
			}
		}


		if (j == 4) {
			if (GetPrivateProfileString(section, keyWord, "none", keyValue5, CHARBUFF, File) != 0) {
				data5 = keyValue5;
			}
		}


		if (j == 5) {
			if (GetPrivateProfileString(section, keyWord, "none", keyValue6, CHARBUFF, File) != 0) {
				data6 = keyValue6;
			}
		}

	}


	while (1)
	{
		//���j���[�I��      
		menu = MeiroTitle();
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
			case STAGE1:
				stage = 0;
				break;

			case STAGE2:
				stage = 1;
				break;

			case STAGE3:
				stage = 2;
				break;
			}
		}



		//���H�Q�[��
		MeiroGame(stage);


		//�Q�[�����I����while���[�v�̐擪�ɂ��ǂ�

	}

	return 0;

}
