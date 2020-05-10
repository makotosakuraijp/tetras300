//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit4.h"
#include <deque>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
int music = 0;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent*
 Owner)
	: TForm(Owner)
{
}
// 横一列のデータ
class Block
{
	public:
	int                     t [10]; //ブロックの属性。番兵は作らない
	int                     bfnt [10]; //色や種類
	int                     all (void);
							Block (void);
	void                    operator =(int a);
};
Block::Block (void)
{
	for (int i = 0; i < 10; i++) {
		t [i] = 0;
		bfnt [i] = 0;
	}
}
//プレイ画面全体のブロック38列
class BlockList
{
public:
	//Block                   blist [39]; //見えている部分１９＋予備１９＋１
	std::deque<Block> blist;
	BlockList (void);
};

BlockList::BlockList (void)
{
	blist.resize (39);
}
class XY
{
public:
	int                     x;
	int                     y;
							XY (void);
							XY (int a, int b);
	void                    operator =(XY a);
};
XY::XY (void)
{
	x = 0;
	y = 0;
}

XY::XY (int a, int b)
{
	x = a;
	y = b;
}

void XY::operator =(XY a)
{
	x = a.x;
	y = a.y;
}



class Mover //動くブロック
{
//	DRAW                    it;
public:
	static TCanvas *canvas;
	XY                      offset; //左上の理論座標
	XY                      r [4];
	int                     bfnt; //ブロックのタイプと色を司る
	int                     type; //何番目のブロックか
	int                     player; //何番目のプレーヤーか
	int                     mode; //プレイヤーのモード。一人、二人対戦、三人対戦。
//							MOVER (void);
//	void                    enter (void);
//	void                    in (void); //キャンバスに描く
//	void                    out (void);
//	void                    change (int _x, int _y, int _bfnt, int _player, int _mode);
//	int                     can_put (BLOCK_LIST a, MOVER b);
//	int                     turn_enable (BLOCK_LIST a);
//	void                    turn (int errlv);
//	int                     move_enable (BLOCK_LIST a, XY b);
//	void                    move (XY a, int errlv);
};
//---------------------------------------------------------------------------
int wait = 0;
int MaxWait = 100;
BlockList player1;
Mover mv, mv2;
static int ReservedX = 0, ReservedReturn = 0, ReservedDown = 0, ChangeBlock = -1;
static int initial = 1;

//TCanvas *Mover::canvas = TForm28::Canvas;

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
	if (music != 2) {
        return;
	}
	Label1->Visible = True;

	TColor colorSelect [7] = {clBlue, clLime, clFuchsia, clRed, clAqua, clYellow, clGray};
	//randomize ();
	srand ((unsigned int)time( 0 ));

	char tmpStr [100];
	sprintf (tmpStr, "%d\n", wait);
	Label1->Caption = tmpStr;

	int totalK = 0, RememberingPosition [4];
	for (int i = 0; i < 38; i++) {
		int k = 0;
		for (int j = 0; j < 10; j++) {
			if (player1.blist [i].t [j] != 0)
				k++;
		}
		if (k == 10) {
			RememberingPosition [totalK] = i;
			totalK++;
		}
	}
	if (totalK != 0) {
		//ブロック消去を始める
		//Graphics::TBitmap* Bitmap = new Graphics::TBitmap();
		//Bitmap->Canvas->CopyMode = cmSrcCopy;
		//Bitmap->Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));

		//Canvas->CopyMode = cmSrcCopy;
		//Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Bitmap->Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));
		for (int k = 0; k < 10; k++) {
		for (int i = 0; i < totalK; i++) {
		for (int j = 0; j < 10; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player1.blist [RememberingPosition [i]].t[j] - 1];

			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (40 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->MoveTo (40 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (55 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*j, 17 + 16*(RememberingPosition [i]-19), 54 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->FillRect (Rect (41 + 16*j, 17 + 16*(RememberingPosition [i]-19), 54 + 16*j, 30 + 16*(RememberingPosition [i]-19)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*j, 17 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (54 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (40 + 16*j, 30 + 16*(RememberingPosition [i]-19));

		}
		}

			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;

		for (int i = 0; i < totalK; i++) {
		Canvas->Rectangle (40, 16 + 16*(RememberingPosition [i]-19), 55 + 16*9, 31 + 16*(RememberingPosition [i]-19));
		Canvas->FillRect (Rect (40, 16 + 16*(RememberingPosition [i]-19), 55 + 16*9, 31 + 16*(RememberingPosition [i]-19)));
		}
		}


		for (int k = 0; k < 4; k++)
			RememberingPosition [k] = 0;

		for (int j = 0; j < 10; j++)
			player1.blist [38].t[j] = 0;

		std::reverse (player1.blist.begin (), player1.blist.end ());
		for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}
		std::reverse (player1.blist.begin (), player1.blist.end ());
		totalK = 0;

		for (int i = 19; i < 39; i++) {
		for (int j= 0; j < 10; j++) {
			if (player1.blist [i].t [j] != 0)
			{

			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player1.blist [i].t[j] - 1];

			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*j, 16 + 16*(i-19));
			Canvas->LineTo (40 + 16*j, 30 + 16*(i-19));
			Canvas->MoveTo (40 + 16*j, 16 + 16*(i-19));
			Canvas->LineTo (55 + 16*j, 16 + 16*(i-19));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*j, 17 + 16*(i-19), 54 + 16*j, 30 + 16*(i-19));
			Canvas->FillRect (Rect (41 + 16*j, 17 + 16*(i-19), 54 + 16*j, 30 + 16*(i-19)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*j, 17 + 16*(i-19));
			Canvas->LineTo (54 + 16*j, 30 + 16*(i-19));
			Canvas->LineTo (40 + 16*j, 30 + 16*(i-19));
			}
			else
			{
			//Canvas->Pen->Color = clBlack;
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*j, 16 + 16*(i-19), 55 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (40 + 16*j, 16 + 16*(i-19), 55 + 16*j, 31 + 16*(i-19)));
			}

		}
		}


		for (int i = 0; i < 10; i++) {
			player1.blist [38].t [i] = 8;
		}
	}
	if (ReservedDown == 1) {
		wait = MaxWait + 1;
	}
	int BFT1 [4][4][2]={{{2,0}, {2,1}, {2,2}, {2,3}}, {{0,2},{1,2},{2,2},{3,2}}, {{1,0}, {1,1}, {1,2}, {1,3}}, {{0,1}, {1,1}, {2,1}, {3,1}}};
	int BFT2 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,0}}, {{1,1},{2,1},{3,1},{3,2}}, {{1,2}, {2,0}, {2,1}, {2,2}}, {{1,0}, {1,1}, {2,1}, {3,1}}};
	int BFT3 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,1}}, {{1,1},{2,1},{3,1},{2,2}}, {{1,1}, {2,0}, {2,1}, {2,2}}, {{1,1}, {2,0}, {2,1}, {3,1}}};
	int BFT4 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,2}}, {{1,1},{1,2},{2,1},{3,1}}, {{1,0}, {2,0}, {2,1}, {2,2}}, {{1,1}, {2,1}, {3,1}, {3,0}}};
	int BFT5 [4][4][2]={{{1,0}, {1,1}, {2,1}, {2,2}}, {{1,2},{2,1},{2,2},{3,1}}, {{1,0}, {1,1}, {2,1}, {2,2}}, {{1,2},{2,1},{2,2},{3,1}}};
	int BFT6 [4][4][2]={{{1,2}, {1,3}, {2,1}, {2,2}}, {{0,2},{1,2},{1,3},{2,3}}, {{1,2}, {1,3}, {2,1}, {2,2}}, {{0,2},{1,2},{1,3},{2,3}}};
	int BFT7 [4][4][2]={{{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}};

	for (int i = 0; i < 10; i++) {
		player1.blist [38].t [i] = 8;
	}
	//Canvas->Pen->Color = clBlue;
	//Canvas->Pen->Style = psSolid;
	//Canvas->Pen->Width = 1;
	//Canvas->Brush->Color = clBlue;
	//Canvas->Rectangle (39, 15, 200, 320);
	//Canvas->Rectangle (239, 15, 400, 320);
	//Canvas->Rectangle (439, 15, 600, 320);

	if (ChangeBlock == 1 || initial == 1){
		mv2.bfnt = std::rand () % 28; //新しいブロックに変える
		mv2.type = mv2.bfnt % 4;
		mv2.player = 1;
		mv2.mode = 1;
		switch (mv2.bfnt / 4) {
			case 0:
			mv2.r[0].x = BFT1 [mv2.type][0][0]; mv2.r[0].y = BFT1 [mv2.type][0][1];
			mv2.r[1].x = BFT1 [mv2.type][1][0]; mv2.r[1].y = BFT1 [mv2.type][1][1];
			mv2.r[2].x = BFT1 [mv2.type][2][0]; mv2.r[2].y = BFT1 [mv2.type][2][1];
			mv2.r[3].x = BFT1 [mv2.type][3][0]; mv2.r[3].y = BFT1 [mv2.type][3][1];
			break;

			case 1:
			mv2.r[0].x = BFT2 [mv2.type][0][0]; mv2.r[0].y = BFT2 [mv2.type][0][1];
			mv2.r[1].x = BFT2 [mv2.type][1][0]; mv2.r[1].y = BFT2 [mv2.type][1][1];
			mv2.r[2].x = BFT2 [mv2.type][2][0]; mv2.r[2].y = BFT2 [mv2.type][2][1];
			mv2.r[3].x = BFT2 [mv2.type][3][0]; mv2.r[3].y = BFT2 [mv2.type][3][1];
			break;
			case 2:
			mv2.r[0].x = BFT3 [mv2.type][0][0]; mv2.r[0].y = BFT3 [mv2.type][0][1];
			mv2.r[1].x = BFT3 [mv2.type][1][0]; mv2.r[1].y = BFT3 [mv2.type][1][1];
			mv2.r[2].x = BFT3 [mv2.type][2][0]; mv2.r[2].y = BFT3 [mv2.type][2][1];
			mv2.r[3].x = BFT3 [mv2.type][3][0]; mv2.r[3].y = BFT3 [mv2.type][3][1];
			break;
			case 3:
			mv2.r[0].x = BFT4 [mv2.type][0][0]; mv2.r[0].y = BFT4 [mv2.type][0][1];
			mv2.r[1].x = BFT4 [mv2.type][1][0]; mv2.r[1].y = BFT4 [mv2.type][1][1];
			mv2.r[2].x = BFT4 [mv2.type][2][0]; mv2.r[2].y = BFT4 [mv2.type][2][1];
			mv2.r[3].x = BFT4 [mv2.type][3][0]; mv2.r[3].y = BFT4 [mv2.type][3][1];
			break;
			case 4:
			mv2.r[0].x = BFT5 [mv2.type][0][0]; mv2.r[0].y = BFT5 [mv2.type][0][1];
			mv2.r[1].x = BFT5 [mv2.type][1][0]; mv2.r[1].y = BFT5 [mv2.type][1][1];
			mv2.r[2].x = BFT5 [mv2.type][2][0]; mv2.r[2].y = BFT5 [mv2.type][2][1];
			mv2.r[3].x = BFT5 [mv2.type][3][0]; mv2.r[3].y = BFT5 [mv2.type][3][1];
			break;
			case 5:
			mv2.r[0].x = BFT6 [mv2.type][0][0]; mv2.r[0].y = BFT6 [mv2.type][0][1];
			mv2.r[1].x = BFT6 [mv2.type][1][0]; mv2.r[1].y = BFT6 [mv2.type][1][1];
			mv2.r[2].x = BFT6 [mv2.type][2][0]; mv2.r[2].y = BFT6 [mv2.type][2][1];
			mv2.r[3].x = BFT6 [mv2.type][3][0]; mv2.r[3].y = BFT6 [mv2.type][3][1];
			break;
			case 6:
			mv2.r[0].x = BFT7 [mv2.type][0][0]; mv2.r[0].y = BFT7 [mv2.type][0][1];
			mv2.r[1].x = BFT7 [mv2.type][1][0]; mv2.r[1].y = BFT7 [mv2.type][1][1];
			mv2.r[2].x = BFT7 [mv2.type][2][0]; mv2.r[2].y = BFT7 [mv2.type][2][1];
			mv2.r[3].x = BFT7 [mv2.type][3][0]; mv2.r[3].y = BFT7 [mv2.type][3][1];
			break;
		}
		if (ChangeBlock == 1)
		{
			mv.bfnt = mv2.bfnt;
			mv.type = mv2.type;
			mv.r[0].x = mv2.r[0].x;
			mv.r[1].x = mv2.r[1].x;
			mv.r[2].x = mv2.r[2].x;
			mv.r[3].x = mv2.r[3].x;
			mv.r[0].y = mv2.r[0].y;
			mv.r[1].y = mv2.r[1].y;
			mv.r[2].y = mv2.r[2].y;
			mv.r[3].y = mv2.r[3].y;

			ChangeBlock = -1;
		}
		if (initial == 1)
			initial = -1;
		return;
	}
	else
	{
		wait++;
	}

	if (initial == -1)
	{
		mv.bfnt = mv2.bfnt;
		mv.type = mv2.type;
		mv.player = 1;
		mv.mode = 1;
		mv.r[0].x = mv2.r[0].x;
		mv.r[1].x = mv2.r[1].x;
		mv.r[2].x = mv2.r[2].x;
		mv.r[3].x = mv2.r[3].x;
		mv.r[0].y = mv2.r[0].y;
		mv.r[1].y = mv2.r[1].y;
		mv.r[2].y = mv2.r[2].y;
		mv.r[3].y = mv2.r[3].y;
	}

	static int i = 3;

	if (ReservedDown == 1 && ChangeBlock == 0)
	{
			mv2.bfnt = mv.bfnt; //新しいブロックに変えない
			mv2.type = mv.type;
			mv2.player = mv.player;
			mv2.mode = mv.mode;
			mv2.r[0].x = mv.r[0].x;
			mv2.r[1].x = mv.r[1].x;
			mv2.r[2].x = mv.r[2].x;
			mv2.r[3].x = mv.r[3].x;
			mv2.r[0].y = mv.r[0].y;
			mv2.r[1].y = mv.r[1].y;
			mv2.r[2].y = mv.r[2].y;
			mv2.r[3].y = mv.r[3].y;

		ReservedDown = 0;
	}

	if (ReservedReturn == 1)
	{
			mv2.type = (mv.bfnt + 1) % 4;
			mv2.bfnt = mv.bfnt - mv.type + mv2.type; //新しいブロックに変える
			switch (mv2.bfnt / 4) {
			case 0:
			mv2.r[0].x = BFT1 [mv2.type][0][0]; mv2.r[0].y = BFT1 [mv2.type][0][1];
			mv2.r[1].x = BFT1 [mv2.type][1][0]; mv2.r[1].y = BFT1 [mv2.type][1][1];
			mv2.r[2].x = BFT1 [mv2.type][2][0]; mv2.r[2].y = BFT1 [mv2.type][2][1];
			mv2.r[3].x = BFT1 [mv2.type][3][0]; mv2.r[3].y = BFT1 [mv2.type][3][1];
			break;

			case 1:
			mv2.r[0].x = BFT2 [mv2.type][0][0]; mv2.r[0].y = BFT2 [mv2.type][0][1];
			mv2.r[1].x = BFT2 [mv2.type][1][0]; mv2.r[1].y = BFT2 [mv2.type][1][1];
			mv2.r[2].x = BFT2 [mv2.type][2][0]; mv2.r[2].y = BFT2 [mv2.type][2][1];
			mv2.r[3].x = BFT2 [mv2.type][3][0]; mv2.r[3].y = BFT2 [mv2.type][3][1];
			break;
			case 2:
			mv2.r[0].x = BFT3 [mv2.type][0][0]; mv2.r[0].y = BFT3 [mv2.type][0][1];
			mv2.r[1].x = BFT3 [mv2.type][1][0]; mv2.r[1].y = BFT3 [mv2.type][1][1];
			mv2.r[2].x = BFT3 [mv2.type][2][0]; mv2.r[2].y = BFT3 [mv2.type][2][1];
			mv2.r[3].x = BFT3 [mv2.type][3][0]; mv2.r[3].y = BFT3 [mv2.type][3][1];
			break;
			case 3:
			mv2.r[0].x = BFT4 [mv2.type][0][0]; mv2.r[0].y = BFT4 [mv2.type][0][1];
			mv2.r[1].x = BFT4 [mv2.type][1][0]; mv2.r[1].y = BFT4 [mv2.type][1][1];
			mv2.r[2].x = BFT4 [mv2.type][2][0]; mv2.r[2].y = BFT4 [mv2.type][2][1];
			mv2.r[3].x = BFT4 [mv2.type][3][0]; mv2.r[3].y = BFT4 [mv2.type][3][1];
			break;
			case 4:
			mv2.r[0].x = BFT5 [mv2.type][0][0]; mv2.r[0].y = BFT5 [mv2.type][0][1];
			mv2.r[1].x = BFT5 [mv2.type][1][0]; mv2.r[1].y = BFT5 [mv2.type][1][1];
			mv2.r[2].x = BFT5 [mv2.type][2][0]; mv2.r[2].y = BFT5 [mv2.type][2][1];
			mv2.r[3].x = BFT5 [mv2.type][3][0]; mv2.r[3].y = BFT5 [mv2.type][3][1];
			break;
			case 5:
			mv2.r[0].x = BFT6 [mv2.type][0][0]; mv2.r[0].y = BFT6 [mv2.type][0][1];
			mv2.r[1].x = BFT6 [mv2.type][1][0]; mv2.r[1].y = BFT6 [mv2.type][1][1];
			mv2.r[2].x = BFT6 [mv2.type][2][0]; mv2.r[2].y = BFT6 [mv2.type][2][1];
			mv2.r[3].x = BFT6 [mv2.type][3][0]; mv2.r[3].y = BFT6 [mv2.type][3][1];
			break;
			case 6:
			mv2.r[0].x = BFT7 [mv2.type][0][0]; mv2.r[0].y = BFT7 [mv2.type][0][1];
			mv2.r[1].x = BFT7 [mv2.type][1][0]; mv2.r[1].y = BFT7 [mv2.type][1][1];
			mv2.r[2].x = BFT7 [mv2.type][2][0]; mv2.r[2].y = BFT7 [mv2.type][2][1];
			mv2.r[3].x = BFT7 [mv2.type][3][0]; mv2.r[3].y = BFT7 [mv2.type][3][1];
			break;
		}

		if (player1.blist [19 + mv.offset.y + mv2.r[0].y + 1].t [mv2.r[0].x + mv.offset.x]
														   + player1.blist [19 + mv.offset.y + mv2.r[1].y + 1].t [mv2.r[1].x + mv.offset.x]
														   + player1.blist [19 + mv.offset.y + mv2.r[2].y + 1].t [mv2.r[2].x + mv.offset.x]
														   + player1.blist [19 + mv.offset.y + mv2.r[3].y + 1].t [mv2.r[3].x + mv.offset.x] == 0
		 && mv2.r[0].x + mv.offset.x >= 0 && mv2.r[0].x + mv.offset.x <= 9
		 && mv2.r[1].x + mv.offset.x >= 0 && mv2.r[1].x + mv.offset.x <= 9
		 && mv2.r[2].x + mv.offset.x >= 0 && mv2.r[2].x + mv.offset.x <= 9
		 && mv2.r[3].x + mv.offset.x >= 0 && mv2.r[3].x + mv.offset.x <= 9)
		 {
		 //回転後のブロックが出現可能な場合
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv2.bfnt / 4];

			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*(mv2.r[j].x + mv.offset.x), 16 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*(mv2.r[j].x + mv.offset.x), 16 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*(mv2.r[j].x + mv.offset.x), 16 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv2.r[j].x + mv.offset.x), 17 + 16*(mv2.r[j].y + mv.offset.y), 54 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv2.r[j].x + mv.offset.x), 17 + 16*(mv2.r[j].y + mv.offset.y), 54 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv2.r[j].x + mv.offset.x), 17 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y));

			}
			ReservedReturn = 0;

			mv.bfnt = mv2.bfnt; //新しいブロックに変える
			mv.type = mv2.type;
			mv.player = mv2.player;
			mv.mode = mv2.mode;
			mv.r[0].x = mv2.r[0].x;
			mv.r[1].x = mv2.r[1].x;
			mv.r[2].x = mv2.r[2].x;
			mv.r[3].x = mv2.r[3].x;
			mv.r[0].y = mv2.r[0].y;
			mv.r[1].y = mv2.r[1].y;
			mv.r[2].y = mv2.r[2].y;
			mv.r[3].y = mv2.r[3].y;
			return;
		 }
		 else
		 {
			ReservedReturn = 0;
			return;
		 }
	}

	if (ReservedX != 0)
	{
			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));

			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}

		mv.offset.x += ReservedX;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];

			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			}
		ReservedX = 0;
		return;
	}
	//wait = 0;

	if (wait + 1 >= MaxWait)
	{
	wait = 0;
	//ブロックが出現できるかどうかテスト
	if ((player1.blist [19 + mv.offset.y + mv2.r[0].y].t [mv2.r[0].x + mv.offset.x]
												   + player1.blist [19 + mv.offset.y + mv2.r[1].y].t [mv2.r[1].x + mv.offset.x]
												   + player1.blist [19 + mv.offset.y + mv2.r[2].y].t [mv2.r[2].x + mv.offset.x]
												   + player1.blist [19 + mv.offset.y + mv2.r[3].y].t [mv2.r[3].x + mv.offset.x] == 0
	 && mv2.r[0].x + mv.offset.x >= 0 && mv2.r[0].x + mv.offset.x <= 9
	 && mv2.r[1].x + mv.offset.x >= 0 && mv2.r[1].x + mv.offset.x <= 9
	 && mv2.r[2].x + mv.offset.x >= 0 && mv2.r[2].x + mv.offset.x <= 9
	 && mv2.r[3].x + mv.offset.x >= 0 && mv2.r[3].x + mv.offset.x <= 9) || initial == -1)
	{
	//次のブロックが出現可能な場合
		if ((player1.blist [19 + mv.offset.y + mv2.r[0].y + 1].t [mv2.r[0].x + mv.offset.x]
														   + player1.blist [19 + mv.offset.y + mv2.r[1].y + 1].t [mv2.r[1].x + mv.offset.x]
														   + player1.blist [19 + mv.offset.y + mv2.r[2].y + 1].t [mv2.r[2].x + mv.offset.x]
														   + player1.blist [19 + mv.offset.y + mv2.r[3].y + 1].t [mv2.r[3].x + mv.offset.x] == 0
		 && mv2.r[0].x + mv.offset.x >= 0 && mv2.r[0].x + mv.offset.x <= 9
		 && mv2.r[1].x + mv.offset.x >= 0 && mv2.r[1].x + mv.offset.x <= 9
		 && mv2.r[2].x + mv.offset.x >= 0 && mv2.r[2].x + mv.offset.x <= 9
		 && mv2.r[3].x + mv.offset.x >= 0 && mv2.r[3].x + mv.offset.x <= 9) || initial == -1)

		{
		//次のブロックで、一段下に落ちることが可能な場合
		//if ((mv.offset.y + mv.r[0].y) < 33 && (mv.offset.y + mv.r[1].y) < 33
		//								 && (mv.offset.y + mv.r[2].y) < 33
		//								 && (mv.offset.y + mv.r[3].y) < 33) {
			//i = (i + 1) % 4;
			//Canvas->Pen->Color = clBtnFace;
			//Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			//Canvas->Pen->Color = clBtnFace;
			//Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));


			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}

			mv.offset.y++; //１足して、次の描画の処理に移る。
			ChangeBlock = 0;
			initial = 0;
		}
		else
		{
		//次のブロックで、一つ下に落ちることが不可能な場合。
		//mv.bfnt = mv2.bfnt; //新しいブロックに変える
		//mv.type = mv2.type;
		//mv.player = mv2.player;
		//mv.mode = mv2.mode;
		//mv.r[0].x = mv2.r[0].x;
		//mv.r[1].x = mv2.r[1].x;
		//mv.r[2].x = mv2.r[2].x;
		//mv.r[3].x = mv2.r[3].x;
		//mv.r[0].y = mv2.r[0].y;
		//mv.r[1].y = mv2.r[1].y;
		//mv.r[2].y = mv2.r[2].y;
		//mv.r[3].y = mv2.r[3].y;
		//mv.offset.y++;



		//一つ下に落ちることが可能な場合。
		//if (player1.blist [20 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] +
		//player1.blist [20 + mv.offset.y + mv.r[1].y].t [mv.r[1].x] +
		//player1.blist [20 + mv.offset.y + mv.r[2].y].t [mv.r[2].x] +
		//player1.blist [20 + mv.offset.y + mv.r[3].y].t [mv.r[3].x]== 0)
		//{
		//mv.offset.y--;

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));

			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];

			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv2.r[j].x + mv.offset.x), 30 + 16*(mv2.r[j].y + mv.offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));

			}

		//mv.offset.y--;
		player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x + mv.offset.x] = mv.bfnt / 4 + 1;
		mv.offset.x = 0;
		mv.offset.y = 0;
		ChangeBlock = 1;
		initial = 0;
		wait = 0;
		return;
		//}
		//player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] = mv.bfnt / 4 + 1;
		//player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x] = mv.bfnt / 4 + 1;
		//player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x] = mv.bfnt / 4 + 1;
		//player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x] = mv.bfnt / 4 + 1;
		//mv.offset.y = 0;
		//return;
		}

		//if (ChangeBlock == 1)
		//{
		mv.bfnt = mv2.bfnt; //新しいブロックに変える
		mv.type = mv2.type;
		mv.player = mv2.player;
		mv.mode = mv2.mode;
		mv.r[0].x = mv2.r[0].x;
		mv.r[1].x = mv2.r[1].x;
		mv.r[2].x = mv2.r[2].x;
		mv.r[3].x = mv2.r[3].x;
		mv.r[0].y = mv2.r[0].y;
		mv.r[1].y = mv2.r[1].y;
		mv.r[2].y = mv2.r[2].y;
		mv.r[3].y = mv2.r[3].y;
		initial = 0;
		//ChangeBlock = 0;
		//}
		//if ((mv.offset.y + mv.r[0].y) < 33 && (mv.offset.y + mv.r[1].y) < 33
		//								 && (mv.offset.y + mv.r[2].y) < 33
		//								 && (mv.offset.y + mv.r[3].y) < 33) {
			//i = (i + 1) % 4;
			//Canvas->Pen->Color = clBtnFace;
			//Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			//mv.offset.y++;
		//}
		//else
		//{
		//	return;
		//}
	}
	else
	{
	//次のブロックが出現不能な場合
		if (player1.blist [19 + mv.offset.y + mv.r[0].y + 1].t [mv.r[0].x + mv.offset.x]
													   + player1.blist [19 + mv.offset.y + mv.r[1].y + 1].t [mv.r[1].x + mv.offset.x]
													   + player1.blist [19 + mv.offset.y + mv.r[2].y + 1].t [mv.r[2].x + mv.offset.x]
													   + player1.blist [19 + mv.offset.y + mv.r[3].y + 1].t [mv.r[3].x + mv.offset.x] == 0
		 && mv.r[0].x + mv.offset.x >= 0 && mv.r[0].x + mv.offset.x <= 9
		 && mv.r[1].x + mv.offset.x >= 0 && mv.r[1].x + mv.offset.x <= 9
		 && mv.r[2].x + mv.offset.x >= 0 && mv.r[2].x + mv.offset.x <= 9
		 && mv.r[3].x + mv.offset.x >= 0 && mv.r[3].x + mv.offset.x <= 9)
		{
		//ブロックが下に自然落下可能な場合
		//mv.offset.y--;

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));

			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}

		mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];

			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));

			}

		//mv.offset.y--;
		player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x + mv.offset.x] = mv.bfnt / 4 + 1;
		mv.offset.x = 0;
		mv.offset.y = 0;
		initial = 0;
		//ChangeBlock = 1;
		ChangeBlock = 1;
		wait = 0;
		return;
		}
		else
		{
		//ブロックが下に自然落下不可能な場合
		//mv.offset.y--;

			/*Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*mv.r[j].x, 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*mv.r[j].x, 31 + 16*(mv.r[j].y + mv.offset.y)));
			}
		//mv.offset.y++;
			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];
			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*mv.r[j].x, 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*mv.r[j].x, 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y)));
			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*mv.r[j].x, 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			}*/

		//mv.offset.y--;
		/*if (player1.blist [20 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] +
		player1.blist [20 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] +
		player1.blist [20 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] +
		player1.blist [20 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] == 0)
		{
		//ブロックが下に自然落下可能な場合
		//mv.offset.y--;
			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*mv.r[j].x, 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*mv.r[j].x, 31 + 16*(mv.r[j].y + mv.offset.y)));
			}
		mv.offset.y++;
			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];
			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*mv.r[j].x, 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*mv.r[j].x, 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*mv.r[j].x, 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y)));
			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*mv.r[j].x, 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*mv.r[j].x, 30 + 16*(mv.r[j].y + mv.offset.y));
			}
		mv.offset.y--;
		player1.blist [20 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] = mv.bfnt / 4 + 1;
		player1.blist [20 + mv.offset.y + mv.r[1].y].t [mv.r[1].x] = mv.bfnt / 4 + 1;
		player1.blist [20 + mv.offset.y + mv.r[2].y].t [mv.r[2].x] = mv.bfnt / 4 + 1;
		player1.blist [20 + mv.offset.y + mv.r[3].y].t [mv.r[3].x] = mv.bfnt / 4 + 1;
		mv.offset.y = 0;
		return;
		}*/
		player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x + mv.offset.x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x + mv.offset.x] = mv.bfnt / 4 + 1;
		mv.offset.x = 0;
		mv.offset.y = 0;
		//ChangeBlock = 1;
		ChangeBlock = 1;
		initial = 0;
		wait = 0;
		return;
		}
	}
	}
	else
	{
		wait++;
	}


	//下に下げられるかカウント。
	/*if (player1.blist [19 + mv.offset.y + mv.r[0].y + 1].t [mv.r[0].x] + player1.blist [19 + mv.offset.y + mv.r[1].y + 1].t [mv.r[1].x]
													   + player1.blist [19 + mv.offset.y + mv.r[2].y + 1].t [mv.r[2].x]
													   + player1.blist [19 + mv.offset.y + mv.r[3].y + 1].t [mv.r[3].x] == 0)
	{
		//if ((mv.offset.y + mv.r[0].y) < 33 && (mv.offset.y + mv.r[1].y) < 33
		//								 && (mv.offset.y + mv.r[2].y) < 33
		//								 && (mv.offset.y + mv.r[3].y) < 33) {
			//i = (i + 1) % 4;
			//Canvas->Pen->Color = clBtnFace;
			//Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			//Canvas->Pen->Color = clBtnFace;
			//Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			mv.offset.y++;
		//}
		//else
		//{
		//	return;
		//}
	}
	else
	{
		player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x] = mv.bfnt / 4 + 1;
		player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x] = mv.bfnt / 4 + 1;
		mv.offset.y = 0;
		return;
	}*/

	for (int j = 0; j < 4; j++) {
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Style = psSolid;
	Canvas->Pen->Width = 1;
	Canvas->Brush->Color = colorSelect [mv.bfnt / 4];

	//一ブロックのひな形
	Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->LineTo (55 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->Pen->Color = clBlue;
	Canvas->Rectangle (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->FillRect (Rect (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y)));

	Canvas->Pen->Color = clBlack;
	Canvas->MoveTo (54 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->LineTo (54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
	Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));

	}

	Canvas->Pen->Color = clBlue;
	Canvas->MoveTo (39, 15);
	Canvas->LineTo (200, 15);
	Canvas->MoveTo (200, 15);
	Canvas->LineTo (200, 320);
	Canvas->MoveTo (200, 320);
	Canvas->LineTo (39, 320);
	Canvas->MoveTo (39, 320);
	Canvas->LineTo (39, 15);
	//Canvas->Rectangle (39, 15, 200, 320);

	initial = 0;
}

//---------------------------------------------------------------------------
/*void __fastcall TForm17::Button1Click(TObject *Sender)
{
	int BFT1 [4][4][2]={{{2,0}, {2,1}, {2,2}, {2,3}}, {{0,2},{1,2},{2,2},{3,2}}, {{1,0}, {1,1}, {1,2}, {1,3}}, {{0,1}, {1,1}, {2,1}, {3,1}}};
	int BFT2 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,0}}, {{1,1},{2,1},{3,1},{3,2}}, {{1,2}, {2,0}, {2,1}, {2,2}}, {{1,0}, {1,1}, {2,1}, {3,1}}};
	int BFT3 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,1}}, {{1,1},{2,1},{3,1},{2,2}}, {{1,1}, {2,0}, {2,1}, {2,2}}, {{1,1}, {2,0}, {2,1}, {3,1}}};
	int BFT4 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,2}}, {{1,1},{1,2},{2,1},{3,1}}, {{1,0}, {2,0}, {2,1}, {2,2}}, {{1,1}, {2,1}, {3,1}, {3,0}}};
	int BFT5 [4][4][2]={{{1,0}, {1,1}, {2,1}, {2,2}}, {{1,2},{2,1},{2,2},{3,1}}, {{1,0}, {1,1}, {2,1}, {2,2}}, {{1,2},{2,1},{2,2},{3,1}}};
	int BFT6 [4][4][2]={{{1,2}, {1,3}, {2,1}, {2,2}}, {{0,2},{1,2},{1,3},{2,3}}, {{1,2}, {1,3}, {2,1}, {2,2}}, {{0,2},{1,2},{1,3},{2,3}}};
	int BFT7 [4][4][2]={{{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}};
	//for (int i = 0; i < 4; i++)
	static int i = 3;
	i = (i + 1) % 4;
	Canvas->Pen->Color = clBtnFace;
	Canvas->Brush->Color = clBtnFace;
	Canvas->Rectangle (100, 100, 160, 160);
	Canvas->FillRect (Rect(100, 100, 160, 160));
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clBlue;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT1[i][j][0], 100 + 15*BFT1[i][j][1]);
		Canvas->LineTo (100 + 15*BFT1[i][j][0], 114 + 15*BFT1[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT1[i][j][0], 100 + 15*BFT1[i][j][1]);
		Canvas->LineTo (115 + 15*BFT1[i][j][0], 100 + 15*BFT1[i][j][1]);
		Canvas->Pen->Color = clBlue;
		Canvas->Rectangle (101 + 15*BFT1[i][j][0], 101 + 15*BFT1[i][j][1], 114 + 15*BFT1[i][j][0], 114 + 15*BFT1[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT1[i][j][0], 101 + 15*BFT1[i][j][1], 114 + 15*BFT1[i][j][0], 114 + 15*BFT1[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT1[i][j][0], 101 + 15*BFT1[i][j][1]);
		Canvas->LineTo (114 + 15*BFT1[i][j][0], 114 + 15*BFT1[i][j][1]);
		Canvas->LineTo (100 + 15*BFT1[i][j][0], 114 + 15*BFT1[i][j][1]);
		}
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clLime;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT2[i][j][0], 100 + 15*BFT2[i][j][1]);
		Canvas->LineTo (100 + 15*BFT2[i][j][0], 114 + 15*BFT2[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT2[i][j][0], 100 + 15*BFT2[i][j][1]);
		Canvas->LineTo (115 + 15*BFT2[i][j][0], 100 + 15*BFT2[i][j][1]);
		Canvas->Pen->Color = clLime;
		Canvas->Rectangle (101 + 15*BFT2[i][j][0], 101 + 15*BFT2[i][j][1], 114 + 15*BFT2[i][j][0], 114 + 15*BFT2[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT2[i][j][0], 101 + 15*BFT2[i][j][1], 114 + 15*BFT2[i][j][0], 114 + 15*BFT2[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT2[i][j][0], 101 + 15*BFT2[i][j][1]);
		Canvas->LineTo (114 + 15*BFT2[i][j][0], 114 + 15*BFT2[i][j][1]);
		Canvas->LineTo (100 + 15*BFT2[i][j][0], 114 + 15*BFT2[i][j][1]);
		}
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clFuchsia;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT3[i][j][0], 100 + 15*BFT3[i][j][1]);
		Canvas->LineTo (100 + 15*BFT3[i][j][0], 114 + 15*BFT3[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT3[i][j][0], 100 + 15*BFT3[i][j][1]);
		Canvas->LineTo (115 + 15*BFT3[i][j][0], 100 + 15*BFT3[i][j][1]);
		Canvas->Pen->Color = clFuchsia;
		Canvas->Rectangle (101 + 15*BFT3[i][j][0], 101 + 15*BFT3[i][j][1], 114 + 15*BFT3[i][j][0], 114 + 15*BFT3[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT3[i][j][0], 101 + 15*BFT3[i][j][1], 114 + 15*BFT3[i][j][0], 114 + 15*BFT3[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT3[i][j][0], 101 + 15*BFT3[i][j][1]);
		Canvas->LineTo (114 + 15*BFT3[i][j][0], 114 + 15*BFT3[i][j][1]);
		Canvas->LineTo (100 + 15*BFT3[i][j][0], 114 + 15*BFT3[i][j][1]);
		}
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clRed;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT4[i][j][0], 100 + 15*BFT4[i][j][1]);
		Canvas->LineTo (100 + 15*BFT4[i][j][0], 114 + 15*BFT4[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT4[i][j][0], 100 + 15*BFT4[i][j][1]);
		Canvas->LineTo (115 + 15*BFT4[i][j][0], 100 + 15*BFT4[i][j][1]);
		Canvas->Pen->Color = clRed;
		Canvas->Rectangle (101 + 15*BFT4[i][j][0], 101 + 15*BFT4[i][j][1], 114 + 15*BFT4[i][j][0], 114 + 15*BFT4[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT4[i][j][0], 101 + 15*BFT4[i][j][1], 114 + 15*BFT4[i][j][0], 114 + 15*BFT4[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT4[i][j][0], 101 + 15*BFT4[i][j][1]);
		Canvas->LineTo (114 + 15*BFT4[i][j][0], 114 + 15*BFT4[i][j][1]);
		Canvas->LineTo (100 + 15*BFT4[i][j][0], 114 + 15*BFT4[i][j][1]);
		}
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clAqua;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT5[i][j][0], 100 + 15*BFT5[i][j][1]);
		Canvas->LineTo (100 + 15*BFT5[i][j][0], 114 + 15*BFT5[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT5[i][j][0], 100 + 15*BFT5[i][j][1]);
		Canvas->LineTo (115 + 15*BFT5[i][j][0], 100 + 15*BFT5[i][j][1]);
		Canvas->Pen->Color = clAqua;
		Canvas->Rectangle (101 + 15*BFT5[i][j][0], 101 + 15*BFT5[i][j][1], 114 + 15*BFT5[i][j][0], 114 + 15*BFT5[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT5[i][j][0], 101 + 15*BFT5[i][j][1], 114 + 15*BFT5[i][j][0], 114 + 15*BFT5[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT5[i][j][0], 101 + 15*BFT5[i][j][1]);
		Canvas->LineTo (114 + 15*BFT5[i][j][0], 114 + 15*BFT5[i][j][1]);
		Canvas->LineTo (100 + 15*BFT5[i][j][0], 114 + 15*BFT5[i][j][1]);
		}
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clYellow;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT6[i][j][0], 100 + 15*BFT6[i][j][1]);
		Canvas->LineTo (100 + 15*BFT6[i][j][0], 114 + 15*BFT6[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT6[i][j][0], 100 + 15*BFT6[i][j][1]);
		Canvas->LineTo (115 + 15*BFT6[i][j][0], 100 + 15*BFT6[i][j][1]);
		Canvas->Pen->Color = clYellow;
		Canvas->Rectangle (101 + 15*BFT6[i][j][0], 101 + 15*BFT6[i][j][1], 114 + 15*BFT6[i][j][0], 114 + 15*BFT6[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT6[i][j][0], 101 + 15*BFT6[i][j][1], 114 + 15*BFT6[i][j][0], 114 + 15*BFT6[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT6[i][j][0], 101 + 15*BFT6[i][j][1]);
		Canvas->LineTo (114 + 15*BFT6[i][j][0], 114 + 15*BFT6[i][j][1]);
		Canvas->LineTo (100 + 15*BFT6[i][j][0], 114 + 15*BFT6[i][j][1]);
		}
		for (int j = 0; j < 4; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = clGray;
		//一ブロックのひな形
		Canvas->MoveTo (100 + 15*BFT7[i][j][0], 100 + 15*BFT7[i][j][1]);
		Canvas->LineTo (100 + 15*BFT7[i][j][0], 114 + 15*BFT7[i][j][1]);
		Canvas->MoveTo (100 + 15*BFT7[i][j][0], 100 + 15*BFT7[i][j][1]);
		Canvas->LineTo (115 + 15*BFT7[i][j][0], 100 + 15*BFT7[i][j][1]);
		Canvas->Pen->Color = clGray;
		Canvas->Rectangle (101 + 15*BFT7[i][j][0], 101 + 15*BFT7[i][j][1], 114 + 15*BFT7[i][j][0], 114 + 15*BFT7[i][j][1]);
		Canvas->FillRect (Rect (101 + 15*BFT7[i][j][0], 101 + 15*BFT7[i][j][1], 114 + 15*BFT7[i][j][0], 114 + 15*BFT7[i][j][1]));
		Canvas->Pen->Color = clBlack;
		Canvas->MoveTo (114 + 15*BFT7[i][j][0], 101 + 15*BFT7[i][j][1]);
		Canvas->LineTo (114 + 15*BFT7[i][j][0], 114 + 15*BFT7[i][j][1]);
		Canvas->LineTo (100 + 15*BFT7[i][j][0], 114 + 15*BFT7[i][j][1]);
		}
}*/

int Playmode = 1;



void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TColor colorSelect [7] = {clBlue, clLime, clFuchsia, clRed, clAqua, clYellow, clGray};

	switch (Playmode) {
	case 1:
		switch (Key) {
			//左キー
			case vkA:
			case vkL:
			case vkLeft:
			case vkNumpad4:
			Label1->Caption = "Left";

		if (player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x + mv.offset.x - 1]
													   + player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x + mv.offset.x - 1]
													   + player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x + mv.offset.x - 1]
													   + player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x + mv.offset.x - 1] == 0
		&& (mv.r[0].x + mv.offset.x) > 0 && (mv.r[1].x + mv.offset.x) > 0 && (mv.r[2].x + mv.offset.x) > 0 && (mv.r[3].x + mv.offset.x) > 0)
		{
		//ブロックが左に移動可能な場合
		//mv.offset.y--;

		ReservedX = -1;
		/*	Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}
		mv.offset.x--;
			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];
			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y)));
			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			}*/
		}



			break;

			//右キー
			case vkD:
			case 186: //コロン
			case vkRight:
			case vkNumpad6:
			Label1->Caption = "Right";
			//Label1->Caption = ShortCutToText(ShortCut(Word(':'), Shift));

		if (player1.blist [19 + mv.offset.y + mv.r[0].y].t [mv.r[0].x + mv.offset.x + 1]
													   + player1.blist [19 + mv.offset.y + mv.r[1].y].t [mv.r[1].x + mv.offset.x + 1]
													   + player1.blist [19 + mv.offset.y + mv.r[2].y].t [mv.r[2].x + mv.offset.x + 1]
													   + player1.blist [19 + mv.offset.y + mv.r[3].y].t [mv.r[3].x + mv.offset.x + 1] == 0
		&& (mv.r[0].x + mv.offset.x) < 9 && (mv.r[1].x + mv.offset.x) < 9 && (mv.r[2].x + mv.offset.x) < 9 && (mv.r[3].x + mv.offset.x) < 9)
		{
		//ブロックが右に移動可能な場合
		//mv.offset.y--;

		ReservedX = 1;
		/*	Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//一ブロックのひな形
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y), 55 + 16*(mv.r[j].x + mv.offset.x), 31 + 16*(mv.r[j].y + mv.offset.y)));
			}
		mv.offset.x++;
			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv.bfnt / 4];
			//一ブロックのひな形
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->MoveTo (40 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (55 + 16*(mv.r[j].x + mv.offset.x), 16 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y), 54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y)));
			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv.r[j].x + mv.offset.x), 17 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (54 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			Canvas->LineTo (40 + 16*(mv.r[j].x + mv.offset.x), 30 + 16*(mv.r[j].y + mv.offset.y));
			}*/

		}
			break;

			//回転キー
			case vkS:
			case 187: //セミコロン
			case vkReturn:
			case vkNumpad5:
			Label1->Caption = "Return";
			ReservedReturn = 1;

			break;

			case vkX:
			case vkSlash:
			case vkDown:
			case vkNumpad2:
			Label1->Caption = "Down";
			ReservedDown = 1;
			break;
		}
	case 2:
	case 3:
	default:
		;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm4::FormCreate(TObject *Sender)
{
	ClientHeight = 400;
	ClientWidth = 600;

	Label1->Visible = False;

	//while (music == 0) {}
	Image1->Left = 0;
	Image1->Top = 0;
	Image1->Height = 400;
	Image1->Width = 600;

	Image1->Picture->LoadFromFile("MIRAGE.bmp");
	Image1->Visible = True;

	//Sleep (60000);

	MediaPlayer1->FileName = "IFLOGO.wav";
	MediaPlayer1->Open ();
	MediaPlayer1->Play ();

	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::MediaPlayer1Notify(TObject *Sender)
{
	if (MediaPlayer1->FileName == (System::UnicodeString) "IFLOGO.wav")
	{
		music++;
		MediaPlayer1->FileName = "UEHR.wav";
		MediaPlayer1->Open ();
		MediaPlayer1->Play ();
		Image1->Picture->LoadFromFile("TETRAS.bmp");
	}
	else if (MediaPlayer1->FileName == (System::UnicodeString) "UEHR.wav")
	{
		music++;
		MediaPlayer1->FileName = "XMAS.wav";
		MediaPlayer1->Open ();
		MediaPlayer1->Play ();
		Image1->Left = 30;
		Image1->Top = 360;
		Image1->Picture->LoadFromFile("MirageSince1996.bmp");
		//Image1->Visible = False;
	}
}
//---------------------------------------------------------------------------



