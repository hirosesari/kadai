#include <stdio.h>
#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "sample22.h"



#define CHARBUFF 124
#define MAZE_ROW    5      //迷路の行数
#define MAZE_COLUMN 5      //迷路の列数
#define STAGE 2



char *title[1] = { "section1" };
char *sikibetu[6] = { "1","2","3","4","5","6" };
char strText[1024], *e;
char keyValue1[1024];
char keyValue2[1024];
char keyValue3[1024];
char keyValue4[1024];
char keyValue5[1024];
char keyValue6[1024];


extern char *data1;  //iniファイルの中身
extern char *data2;  //iniファイルの中身
extern char *data3;  //iniファイルの中身
extern char *data4;  //iniファイルの中身
extern char *data5;  //iniファイルの中身
extern char *data6;  //iniファイルの中身



 //プレイヤー
typedef struct
{
	int row;        //プレイヤー位置(行)B
	int column;     //プレイヤー位置(列)
}MazePlayer;



void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}



//迷路の一ブロック
enum MazeKind { PATH, WALL, START, GOAL };    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag { MARU, BATU };                //ブロックが判明しているかどうか


 //メニュー
enum MazeMenu { STAGE0, STAGE1, EXIT };




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
		sprintf_s(File, "%s\\maze.ini", currentDirectory);


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

	/*
	fprintf(stdout, "%s\n", data1);

	fprintf(stdout, "%s\n", data2);

	fprintf(stdout, "%s\n", data3);

	fprintf(stdout, "%s\n", data4);

	fprintf(stdout, "%s\n", data5);

	fprintf(stdout, "%s\n", data6);
	*/

	while (1)

	{

		//メニュー選択      
		menu = MazeTitle();
		printf("\n");

		if (menu == EXIT) //EXITならwhileループを抜けて終了
		{
			break;
		}
		else
		{
			//ステージ設定
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



		//迷路ゲーム
		MazeGame(stage);



		//ゲームが終わるとwhileループの先頭にもどる

	}




	return 0;



}
