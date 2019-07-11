// kadai.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include <stdio.h>
#include "stdafx.h"
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#define CHARBUFF 124

char *kind[25] = { "1", "2", "3", "4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25" };
char *title[2] = { "kind", "flag" };
char strText[1024], *e;
char *endp;
char keyValue[1024];
const char *data[2][25];
char section[CHARBUFF];

void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}
int main()
{
	int a, b, c;

	int menu;
	int stage;

	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);



	for (int i = 0; i <2; i++) {
		for (int j = 0; j < 25; j++) {
			char section[CHARBUFF];
			sprintf_s(section, title[i]);

			char keyWord[CHARBUFF];
			sprintf_s(keyWord, kind[j]);


			char File[CHARBUFF];
			sprintf_s(File, "%s\\maze.ini", currentDirectory);


			//stringとして文字を出力

			if (GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, File) != 0) {
			//	fprintf(stdout, "data= %s\n", keyValue);

				data[i][j] = keyValue;
				fprintf(stdout, "%s\n", data[i][j]);
				//	fprintf(stdout, "data= %s\n", data[i][j]);
				//	fprintf(stdout,"%s", File, section, keyWord);

			}
			
		}
	}


	/*
	for(int a=0; a<25; a++){
	for (int b = 0; b < 25; b++) {
	for (int c = 0; c < 25; c++) {


	data[a][b][c] =
	}
	}

	}
	*/
	return 0;
}