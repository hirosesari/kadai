#include "meiro2.h"
#include "stdafx.h"
#include <stdio.h>


#define MEIRO_LINE    5
#define MEIRO_COLUMN 5    
#define STAGE 3
#define CHARBUFF 124
enum MeiroKind { PATH, WALL, START, GOAL };    //ブロックの種類(道、壁、スタート、ゴール)
enum MeiroFlag { MARU, BATU };                //ブロックが判明しているかどうか			
enum MeiroDirection { UP, DOWN, LEFT, RIGHT, Invalid };   //方向	
enum MeiroMenu { STAGE1, STAGE2, STAGE3, EXIT };  // メニュー


char *data1;  //iniファイルの中身
char *data2;  //iniファイルの中身
char *data3;  //iniファイルの中身
char *data4;  //iniファイルの中身
char *data5;  //iniファイルの中身
char *data6;  //iniファイルの中身
char section[CHARBUFF];
int cnt = 0;


typedef struct {
	enum MeiroKind kind;            //種類(道、壁、スタート、ゴール)
	enum MeiroFlag flag;            //ブロックが判明しているかどうか
} MeiroTile;



typedef struct {
	int line;        //プレイヤー位置(行)B
	int column;     //プレイヤー位置(列)
}MeiroPlayer;


//タイトル
int MeiroTitle() {
	char buf[100];
	int menu = -1;

	printf("\n\n☆☆☆☆☆ 迷路 ☆☆☆☆☆\n\n");
	printf("メニュー\n");
	printf("%d : ステージ1\n", STAGE1);
	printf("%d : ステージ2\n", STAGE2);
	printf("%d : ステージ3\n", STAGE3);
	printf("%d : 終了\n\n", EXIT);
	printf("！！ステージを選んでください！！ ⇒ ");

	fgets(buf, sizeof(buf), stdin);
	sscanf_s(buf, "%d", &menu);

	while (menu < 0 || menu > 3)	//０未満と４以上の場合を選んだら再入力
	{
		printf("入力が正しくありません。再入力してください ⇒ ");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &menu);
	}

	return menu;
}




//プレイヤー移動

void MeiroPlayerMove(int *playerLine, int *playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {
	char buf[100];
	int  direction = -1;

	printf("\n");
	printf("%d : 上に移動\n", UP);
	printf("%d : 下に移動\n", DOWN);
	printf("%d : 左に移動\n", LEFT);
	printf("%d : 右に移動\n\n", RIGHT);
	printf("移動する方向を選んでください ⇒ ");

	fgets(buf, sizeof(buf), stdin);      //文字列で入力を読み込む
	sscanf_s(buf, "%d", &direction);        //数字にできる場合は変換(できなければ何もしない)

	while (direction < 0 || direction > 3) //入力が正しい場合まで繰り返す
	{
		printf("入力が不正です。再入力してください ⇒ ");
		fgets(buf, sizeof(buf), stdin);
		sscanf_s(buf, "%d", &direction);

	}


	switch (direction) {
		//上移動
	case UP: {
		if (*playerLine - 1 >= 0) {//迷路の範囲外でないことを確認
			meiro[*playerLine - 1][*playerColumn].flag = MARU; //ブロックの種類が判明

			if (meiro[*playerLine - 1][*playerColumn].kind != WALL) {//壁かどうか確認
				*playerLine -= 1; //移動
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


			 //下移動
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

			   //左移動
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

		   //右移動
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




//プレイヤー初期化
int MeiroPlayerInit(int *playerLine, int *playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {

	int i, j;

	for (i = 0; i < MEIRO_LINE; i++) { //行

		for (j = 0; j < MEIRO_COLUMN; j++) { //列

			if (meiro[i][j].kind == START) {//スタート地点ならばプレイヤーの位置に設定する

				*playerLine = i;
				*playerColumn = j;
				return 0; //関数終了(プレイヤーを設定できれば残りの処理は必要ない)
			}
		}
	}
}



//ゴール判定
int MeiroGoalCheck(int playerLine, int playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {

	if (meiro[playerLine][playerColumn].kind == GOAL) { //プレイヤー位置がゴール地点に等しい

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
			fprintf_s(fp, "お疲れ様でした");
		}
		fclose(fp);

		return 1;
	}
	return 0;
}

//迷路表示
void MeiroDraw(int playerLine, int playerColumn, MeiroTile meiro[MEIRO_LINE][MEIRO_COLUMN]) {
	int i, j;

	for (i = 0; i < MEIRO_LINE; i++) { //行

		for (j = 0; j < MEIRO_COLUMN; j++) { //列

			if (i == playerLine && j == playerColumn) { //プレイヤー位置

				printf("★");

			}
			else if (meiro[i][j].flag == BATU) { //ブロックが判明していない場合

				printf("？");

			}
			else {

				switch (meiro[i][j].kind) {

				case WALL:
					printf("×");
					break; //壁

				case GOAL:
					printf("Ｇ");
					break; //ゴール

				default:
					printf("　");
					break; //その他(道、スタート)
				}
			}
		}
		printf("\n");

	}
}


//迷路ゲーム
void MeiroGame(int stage) {

	//プレイヤー
	MeiroPlayer player;

	//迷路
	MeiroTile meiro[STAGE][MEIRO_LINE][MEIRO_COLUMN] =  //MEIRO_LINE:行 MEIRO_COLUMN: 列
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

	//プレイヤー初期化
	if (MeiroPlayerInit(&player.line, &player.column, meiro[stage]) == -1)
	{
		//関数MeiroPlayerInitが-1を返すとき初期化に失敗している
		//よって、この時点でプログラムを終了し、迷路の表示は行わない
		return;
	}


	while (MeiroGoalCheck(player.line, player.column, meiro[stage]) != 1) //ゴールするまで移動を繰り返す
	{
		//迷路表示
		MeiroDraw(player.line, player.column, meiro[stage]);
		//プレイヤー移動
		MeiroPlayerMove(&player.line, &player.column, meiro[stage]);
	}

	//迷路最終結果表示
	MeiroDraw(player.line, player.column, meiro[stage]);
}



