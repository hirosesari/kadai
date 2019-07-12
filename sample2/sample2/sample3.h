
#include <stdio.h>
#include "stdafx.h"
//#include "sample3.h"


#define CHARBUFF 124
#define STAGE       2      //ステージ数
#define MAZE_ROW    5      //迷路の行数
#define MAZE_COLUMN 5      //迷路の列数

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


//プレイヤー
typedef struct
{
	int row;        //プレイヤー位置(行)B
	int column;     //プレイヤー位置(列)
}MazePlayer;


//迷路の一ブロック
enum MazeKind { PATH, WALL, START, GOAL };    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag { BATU, MARU };                //ブロックが判明しているかどうか


typedef struct
{
	enum MazeKind kind;            //種類(道、壁、スタート、ゴール)
	enum MazeFlag flag;            //ブロックが判明しているかどうか
} MazeBlock;


//方向
enum MazeDirection { UP, DOWN, LEFT, RIGHT, Invalid };
//プレイヤー移動
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	char buf[100];
	int  direction = -1;

	printf("%d:上\n", UP);
	printf("%d:下\n", DOWN);
	printf("%d:左\n", LEFT);
	printf("%d:右\n", RIGHT);
	printf("数字を入力してください。：");

	fgets(buf, sizeof(buf), stdin);      //文字列で入力を読み込む
	sscanf_s(buf, "%d", &direction);        //数字にできる場合は変換(できなければ何もしない)

	while (direction < 0 || direction >(Invalid - 1)) //入力が正しい場合まで繰り返す
	{
		printf("入力が不正です。再入力してください:");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &direction);
	}


	switch (direction) {
		//上移動
	case UP:
	{
		if (*playerRow - 1 >= 0) //迷路の範囲外でないことを確認
		{
			maze[*playerRow - 1][*playerColumn].flag = MARU; //ブロックの種類が判明

			if (maze[*playerRow - 1][*playerColumn].kind != WALL) //壁かどうか確認
			{
				*playerRow -= 1; //移動
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

	//下移動
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

	//左移動
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

	//右移動
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

