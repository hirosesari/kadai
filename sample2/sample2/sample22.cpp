#include "sample22.h"
#include "stdafx.h"
#include <stdio.h>


#define MAZE_ROW    5
#define MAZE_COLUMN 5    
#define STAGE 2
#define CHARBUFF 124
enum MazeKind { PATH, WALL, START, GOAL };    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag { MARU, BATU };                //ブロックが判明しているかどうか			
enum MazeDirection { UP, DOWN, LEFT, RIGHT, Invalid };   //方向	
enum MazeMenu { STAGE0, STAGE1, EXIT };  // メニュー


char *data1;  //iniファイルの中身
char *data2;  //iniファイルの中身
char *data3;  //iniファイルの中身
char *data4;  //iniファイルの中身
char *data5;  //iniファイルの中身
char *data6;  //iniファイルの中身
char section[CHARBUFF];
int cnt = 0;





typedef struct
{
	enum MazeKind kind;            //種類(道、壁、スタート、ゴール)
	enum MazeFlag flag;            //ブロックが判明しているかどうか
} MazeBlock;



typedef struct
{
	int row;        //プレイヤー位置(行)B
	int column;     //プレイヤー位置(列)
}MazePlayer;


//タイトル
int MazeTitle()
{
	char buf[100];
	int menu = -1;

	printf("\n\n＊＊＊迷路ゲーム＊＊＊\n\n");

	printf("メニュー\n");
	printf("%d:ステージ0\n", STAGE0);
	printf("%d:ステージ1\n", STAGE1);
	printf("%d:終了\n", EXIT);


	printf("メニューを選んでください。：");

	fgets(buf, sizeof(buf), stdin);
	sscanf_s(buf, "%d", &menu);


	while (menu < 0 || menu > EXIT)
	{
		printf("入力が不正です。再入力してください:");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &menu);
	}

	return menu;
}



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


//プレイヤー初期化
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	int i, j;

	for (i = 0; i < MAZE_ROW; i++) //行
	{
		for (j = 0; j < MAZE_COLUMN; j++) //列
		{
			if (maze[i][j].kind == START) //スタート地点ならばプレイヤーの位置に設定する
			{
				*playerRow = i;
				*playerColumn = j;
				return 0; //関数終了(プレイヤーを設定できれば残りの処理は必要ない)
			}
		}
	}


	//スタート地点がなければ、プレイヤーを設定できずここまでくる
	printf("スタートがありません\n");
	return -1;
}




//ゴール判定
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	if (maze[playerRow][playerColumn].kind == GOAL) //プレイヤー位置がゴール地点に等しい
	{
		printf("ゴール!\n");
		printf("カウント回数は%dです\n", cnt);

		FILE *fp;
		errno_t error;
		error = fopen_s(&fp, "textOut.csv", "w");
		if (error != 0) {
			fprintf_s(stderr, "failed to open(w)");
			return(9);
		}
		else {
			fprintf_s(fp, "全体の操作回数は%dです。\n", cnt);


			if (cnt == 10) {
				fprintf_s(fp, "最短ルートです。おめでとうございます。\n");
			}
			fprintf_s(fp, "お疲れ様でした");
		}
		fclose(fp);

		return 1;
	}
	return 0;
}


//迷路表示
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
	int i, j;

	for (i = 0; i < MAZE_ROW; i++) //行
	{
		for (j = 0; j < MAZE_COLUMN; j++) //列
		{
			if (i == playerRow && j == playerColumn) //プレイヤー位置
			{
				printf("Ｐ");
			}
			else if (maze[i][j].flag == BATU) //ブロックが判明していない場合
			{
				printf("？");
			}
			else
			{
				switch (maze[i][j].kind)
				{
				case WALL:
					printf("口"); break; //壁
				case GOAL:
					printf("Ｇ"); break; //ゴール
				default:
					printf("　"); break; //その他(道、スタート)
				}
			}
		}
		printf("\n");


	}
}



//迷路ゲーム
void MazeGame(int stage)
{
	//プレイヤー
	MazePlayer player;

	//迷路
	MazeBlock maze[STAGE][MAZE_ROW][MAZE_COLUMN] =  //MAZE_ROW:行 MAZE_COLUMN: 列
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


	//プレイヤー初期化
	if (MazePlayerInit(&player.row, &player.column, maze[stage]) == -1)
	{
		//関数MazePlayerInitが-1を返すとき初期化に失敗している
		//よって、この時点でプログラムを終了し、迷路の表示は行わない
		return;
	}

	while (MazeGoalCheck(player.row, player.column, maze[stage]) != 1) //ゴールするまで移動を繰り返す
	{
		//迷路表示
		MazeDraw(player.row, player.column, maze[stage]);

		//プレイヤー移動
		MazePlayerMove(&player.row, &player.column, maze[stage]);
	}



	//迷路最終結果表示
	MazeDraw(player.row, player.column, maze[stage]);

}




