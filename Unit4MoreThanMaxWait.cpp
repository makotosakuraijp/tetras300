#include "Unit4.h"

extern int music, PlayMode;
extern JOYCAPS joycaps, joycaps2, joycaps3;
extern JOYINFOEX joyinfoex, joyinfoex2, joyinfoex3;

extern DWORD midlex, flexx, midley, flexy;
extern DWORD midlex2, flexx2, midley2, flexy2;
extern DWORD midlex3, flexx3, midley3, flexy3;

extern int wait, wait2, wait3;
extern int MaxWait;
extern BlockList player1, player2, player3;
extern Mover mv [3], mv2 [3];
extern int ReservedX, ReservedReturn, ReservedDown, ChangeBlock;
extern int ReservedX2, ReservedReturn2, ReservedDown2, ChangeBlock2;
extern int ReservedX3, ReservedReturn3, ReservedDown3, ChangeBlock3;
extern int initial, initial2, initial3;
extern std::vector<int> BlockTypeSeq;
extern long blockNumber, blockNumber2, blockNumber3;
extern int TetrisHall [3];
extern int ChargedBlocks [3]; //ペナルティになっているブロックの高さ
extern int Charge2 [4];
extern int Charge3 [4];

extern Block ChargeWithHall [3];
extern FILE *output2;

extern TColor colorSelect [7];

extern TForm4 *Form4;
extern std::vector <BYTE> KeyTbl;
extern int controllers;

extern int BFT1 [4][4][2];
extern int BFT2 [4][4][2];
extern int BFT3 [4][4][2];
extern int BFT4 [4][4][2];
extern int BFT5 [4][4][2];
extern int BFT6 [4][4][2];
extern int BFT7 [4][4][2];

inline bool Player1EmerginableNext (void)
{
	return player1.blist [19 + mv [0].offset.y + mv2 [0].r[0].y].t [mv2 [0].r[0].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv2 [0].r[1].y].t [mv2 [0].r[1].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv2 [0].r[2].y].t [mv2 [0].r[2].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv2 [0].r[3].y].t [mv2 [0].r[3].x + mv [0].offset.x] == 0
	 && mv2 [0].r[0].x + mv [0].offset.x >= 0 && mv2 [0].r[0].x + mv [0].offset.x <= 9
	 && mv2 [0].r[1].x + mv [0].offset.x >= 0 && mv2 [0].r[1].x + mv [0].offset.x <= 9
	 && mv2 [0].r[2].x + mv [0].offset.x >= 0 && mv2 [0].r[2].x + mv [0].offset.x <= 9
	 && mv2 [0].r[3].x + mv [0].offset.x >= 0 && mv2 [0].r[3].x + mv [0].offset.x <= 9;
}

inline bool Player1EmerginableDown (void)
{
	return player1.blist [19 + mv [0].offset.y + mv2 [0].r[0].y + 1].t [mv2 [0].r[0].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv2 [0].r[1].y + 1].t [mv2 [0].r[1].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv2 [0].r[2].y + 1].t [mv2 [0].r[2].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv2 [0].r[3].y + 1].t [mv2 [0].r[3].x + mv [0].offset.x] == 0
	 && mv2 [0].r[0].x + mv [0].offset.x >= 0 && mv2 [0].r[0].x + mv [0].offset.x <= 9
	 && mv2 [0].r[1].x + mv [0].offset.x >= 0 && mv2 [0].r[1].x + mv [0].offset.x <= 9
	 && mv2 [0].r[2].x + mv [0].offset.x >= 0 && mv2 [0].r[2].x + mv [0].offset.x <= 9
	 && mv2 [0].r[3].x + mv [0].offset.x >= 0 && mv2 [0].r[3].x + mv [0].offset.x <= 9;
}

inline bool Player1EmerginableNow (void)
{
	return player1.blist [19 + mv [0].offset.y + mv [0].r[0].y + 1].t [mv [0].r[0].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv [0].r[1].y + 1].t [mv [0].r[1].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv [0].r[2].y + 1].t [mv [0].r[2].x + mv [0].offset.x]
	+ player1.blist [19 + mv [0].offset.y + mv [0].r[3].y + 1].t [mv [0].r[3].x + mv [0].offset.x] == 0
	 && mv [0].r[0].x + mv [0].offset.x >= 0 && mv [0].r[0].x + mv [0].offset.x <= 9
	 && mv [0].r[1].x + mv [0].offset.x >= 0 && mv [0].r[1].x + mv [0].offset.x <= 9
	 && mv [0].r[2].x + mv [0].offset.x >= 0 && mv [0].r[2].x + mv [0].offset.x <= 9
	 && mv [0].r[3].x + mv [0].offset.x >= 0 && mv [0].r[3].x + mv [0].offset.x <= 9;
}

int Player1MoreThanMaxWait (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	//ブロックが出現できるかどうかテスト
	if (Player1EmerginableNext () || initial == -1)
	{
	//次のブロックが出現可能な場合
		if (Player1EmerginableDown () || initial == -1)

		{

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

			mv [0].offset.y++; //１足して、次の描画の処理に移る。
			ChangeBlock = 0;
			initial = 0;
		}
		else
		{
		//次のブロックで、一つ下に落ちることが不可能な場合。

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Color = clWhite;
				Canvas->Pen->Style = psSolid;
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = colorSelect [mv [0].bfnt / 4];

				//一ブロックのひな形
				Canvas->MoveTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->MoveTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (55 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->Pen->Color = clBlue;
				Canvas->Rectangle (41 + 16*(mv [0].r[j].x + mv [0].offset.x), 17 + 16*(mv [0].r[j].y + mv [0].offset.y), 54 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
				Canvas->FillRect (Rect (41 + 16*(mv [0].r[j].x + mv [0].offset.x), 17 + 16*(mv [0].r[j].y + mv [0].offset.y), 54 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y)));

				Canvas->Pen->Color = clBlack;
				Canvas->MoveTo (54 + 16*(mv [0].r[j].x + mv [0].offset.x), 17 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (54 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
			}

			player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			mv [0].offset.x = 2;
			mv [0].offset.y = 0;
			ChangeBlock = 1;
			initial = 0;
			wait = 0;

		//ペナルティの作業を始める。
		if (ChargedBlocks [0] != 0)
			Player1Penalty ();

		return -1;
		}

		//if (ChangeBlock == 1)
		//{
		mv [0].bfnt = mv2 [0].bfnt; //新しいブロックに変える
		mv [0].type = mv2 [0].type;
		mv [0].player = mv2 [0].player;
		mv [0].mode = mv2 [0].mode;
		mv [0].r[0].x = mv2 [0].r[0].x;
		mv [0].r[1].x = mv2 [0].r[1].x;
		mv [0].r[2].x = mv2 [0].r[2].x;
		mv [0].r[3].x = mv2 [0].r[3].x;
		mv [0].r[0].y = mv2 [0].r[0].y;
		mv [0].r[1].y = mv2 [0].r[1].y;
		mv [0].r[2].y = mv2 [0].r[2].y;
		mv [0].r[3].y = mv2 [0].r[3].y;
		initial = 0;
	}
	else
	{
	//次のブロックが出現不能な場合
		if (Player1EmerginableNow ())
		{
		//ブロックが下に自然落下可能な場合

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

			mv [0].offset.y++;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Color = clWhite;
				Canvas->Pen->Style = psSolid;
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = colorSelect [mv [0].bfnt / 4];

				//一ブロックのひな形
				Canvas->MoveTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->MoveTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (55 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->Pen->Color = clBlue;
				Canvas->Rectangle (41 + 16*(mv [0].r[j].x + mv [0].offset.x), 17 + 16*(mv [0].r[j].y + mv [0].offset.y), 54 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->FillRect (Rect (41 + 16*(mv [0].r[j].x + mv [0].offset.x), 17 + 16*(mv [0].r[j].y + mv [0].offset.y), 54 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y)));

				Canvas->Pen->Color = clBlack;
				Canvas->MoveTo (54 + 16*(mv [0].r[j].x + mv [0].offset.x), 17 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (54 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
				Canvas->LineTo (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 30 + 16*(mv [0].r[j].y + mv [0].offset.y));
			}

			//mv.offset.y--;
			player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			mv [0].offset.x = 2;
			mv [0].offset.y = 0;
			initial = 0;
			//ChangeBlock = 1;
			ChangeBlock = 1; //ここが怪しい
			wait = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [0] != 0)
				Player1Penalty ();

			return -1;
		}
		else
		{
			player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
			mv [0].offset.x = 2;
			mv [0].offset.y = 0;
			//ChangeBlock = 1;
			ChangeBlock = 1; //ここが次に怪しい
			initial = 0;
			wait = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [0] != 0) {
				Player1Penalty ();
			}

			return -1;
		}
	}
	return 1;
}

inline bool Player2EmerginableNext (void)
{
	return player2.blist [19 + mv [1].offset.y + mv2 [1].r[0].y].t [mv2 [1].r[0].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv2 [1].r[1].y].t [mv2 [1].r[1].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv2 [1].r[2].y].t [mv2 [1].r[2].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv2 [1].r[3].y].t [mv2 [1].r[3].x + mv [1].offset.x] == 0
	 && mv2 [1].r[0].x + mv [1].offset.x >= 0 && mv2 [1].r[0].x + mv [1].offset.x <= 9
	 && mv2 [1].r[1].x + mv [1].offset.x >= 0 && mv2 [1].r[1].x + mv [1].offset.x <= 9
	 && mv2 [1].r[2].x + mv [1].offset.x >= 0 && mv2 [1].r[2].x + mv [1].offset.x <= 9
	 && mv2 [1].r[3].x + mv [1].offset.x >= 0 && mv2 [1].r[3].x + mv [1].offset.x <= 9;
}

inline bool Player2EmerginableDown (void)
{
	return player2.blist [19 + mv [1].offset.y + mv2 [1].r[0].y + 1].t [mv2 [1].r[0].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv2 [1].r[1].y + 1].t [mv2 [1].r[1].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv2 [1].r[2].y + 1].t [mv2 [1].r[2].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv2 [1].r[3].y + 1].t [mv2 [1].r[3].x + mv [1].offset.x] == 0
	 && mv2 [1].r[0].x + mv [1].offset.x >= 0 && mv2 [1].r[0].x + mv [1].offset.x <= 9
	 && mv2 [1].r[1].x + mv [1].offset.x >= 0 && mv2 [1].r[1].x + mv [1].offset.x <= 9
	 && mv2 [1].r[2].x + mv [1].offset.x >= 0 && mv2 [1].r[2].x + mv [1].offset.x <= 9
	 && mv2 [1].r[3].x + mv [1].offset.x >= 0 && mv2 [1].r[3].x + mv [1].offset.x <= 9;
}

inline bool Player2EmerginableNow (void)
{
	return player2.blist [19 + mv [1].offset.y + mv [1].r[0].y + 1].t [mv [1].r[0].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv [1].r[1].y + 1].t [mv [1].r[1].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv [1].r[2].y + 1].t [mv [1].r[2].x + mv [1].offset.x]
	+ player2.blist [19 + mv [1].offset.y + mv [1].r[3].y + 1].t [mv [1].r[3].x + mv [1].offset.x] == 0
	 && mv [0].r[0].x + mv [1].offset.x >= 0 && mv [1].r[0].x + mv [1].offset.x <= 9
	 && mv [0].r[1].x + mv [1].offset.x >= 0 && mv [1].r[1].x + mv [1].offset.x <= 9
	 && mv [0].r[2].x + mv [1].offset.x >= 0 && mv [1].r[2].x + mv [1].offset.x <= 9
	 && mv [0].r[3].x + mv [1].offset.x >= 0 && mv [1].r[3].x + mv [1].offset.x <= 9;
}

int Player2MoreThanMaxWait (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	//ブロックが出現できるかどうかテスト
	if (Player2EmerginableNext () || initial2 == -1)
	{
	//次のブロックが出現可能な場合
		if (Player2EmerginableDown () || initial2 == -1)

		{
		//次のブロックで、一段下に落ちることが可能な場合

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

			mv [1].offset.y++; //１足して、次の描画の処理に移る。
			ChangeBlock2 = 0;
			initial2 = 0;
		}
		else
		{
		//次のブロックで、一つ下に落ちることが不可能な場合。

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Color = clWhite;
				Canvas->Pen->Style = psSolid;
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = colorSelect [mv [1].bfnt / 4];

				//一ブロックのひな形
				Canvas->MoveTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->MoveTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (455 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->Pen->Color = clBlue;
				Canvas->Rectangle (441 + 16*(mv [1].r[j].x + mv [1].offset.x), 17 + 16*(mv [1].r[j].y + mv [1].offset.y), 454 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
				Canvas->FillRect (Rect (441 + 16*(mv [1].r[j].x + mv [1].offset.x), 17 + 16*(mv [1].r[j].y + mv [1].offset.y), 454 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y)));

				Canvas->Pen->Color = clBlack;
				Canvas->MoveTo (454 + 16*(mv [1].r[j].x + mv [1].offset.x), 17 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (454 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
			}

			player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			mv [1].offset.x = 2;
			mv [1].offset.y = 0;
			ChangeBlock2 = 1;
			initial2 = 0;
			wait2 = 0;

		//ペナルティの作業を始める。
		if (ChargedBlocks [1] != 0)
			Player2Penalty ();

		return -1;
		}

		//if (ChangeBlock == 1)
		//{
		mv [1].bfnt = mv2 [1].bfnt; //新しいブロックに変える
		mv [1].type = mv2 [1].type;
		mv [1].player = mv2 [1].player;
		mv [1].mode = mv2 [1].mode;
		mv [1].r[0].x = mv2 [1].r[0].x;
		mv [1].r[1].x = mv2 [1].r[1].x;
		mv [1].r[2].x = mv2 [1].r[2].x;
		mv [1].r[3].x = mv2 [1].r[3].x;
		mv [1].r[0].y = mv2 [1].r[0].y;
		mv [1].r[1].y = mv2 [1].r[1].y;
		mv [1].r[2].y = mv2 [1].r[2].y;
		mv [1].r[3].y = mv2 [1].r[3].y;
		initial2 = 0;
	}
	else
	{
		//次のブロックが出現不能な場合
		if (Player2EmerginableNow ())
		{
		//ブロックが下に自然落下可能な場合

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

			mv [1].offset.y++;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Color = clWhite;
				Canvas->Pen->Style = psSolid;
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = colorSelect [mv [1].bfnt / 4];

				//一ブロックのひな形
				Canvas->MoveTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->MoveTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (455 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->Pen->Color = clBlue;
				Canvas->Rectangle (441 + 16*(mv [1].r[j].x + mv [1].offset.x), 17 + 16*(mv [1].r[j].y + mv [1].offset.y), 454 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->FillRect (Rect (441 + 16*(mv [1].r[j].x + mv [1].offset.x), 17 + 16*(mv [1].r[j].y + mv [1].offset.y), 454 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y)));

				Canvas->Pen->Color = clBlack;
				Canvas->MoveTo (454 + 16*(mv [1].r[j].x + mv [1].offset.x), 17 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (454 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
				Canvas->LineTo (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 30 + 16*(mv [1].r[j].y + mv [1].offset.y));
			}

			player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			mv [1].offset.x = 2;
			mv [1].offset.y = 0;
			initial2 = 0;
			//ChangeBlock = 1;
			ChangeBlock2 = 1;
			wait2 = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [1] != 0)
				Player2Penalty ();

			return -1;
		}
		else
		{
			//ブロックが下に自然落下不可能な場合
			player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
			mv [1].offset.x = 2;
			mv [1].offset.y = 0;
			//ChangeBlock = 1;
			ChangeBlock2 = 1;
			initial2 = 0;
			wait2 = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [1] != 0)
				Player2Penalty ();

			return -1;
		}
	}
	return 1;

}

inline bool Player3EmerginableNext (void)
{
	return player3.blist [19 + mv [2].offset.y + mv2 [2].r[0].y].t [mv2 [2].r[0].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv2 [2].r[1].y].t [mv2 [2].r[1].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv2 [2].r[2].y].t [mv2 [2].r[2].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv2 [2].r[3].y].t [mv2 [2].r[3].x + mv [2].offset.x] == 0
	 && mv2 [2].r[0].x + mv [2].offset.x >= 0 && mv2 [2].r[0].x + mv [2].offset.x <= 9
	 && mv2 [2].r[1].x + mv [2].offset.x >= 0 && mv2 [2].r[1].x + mv [2].offset.x <= 9
	 && mv2 [2].r[2].x + mv [2].offset.x >= 0 && mv2 [2].r[2].x + mv [2].offset.x <= 9
	 && mv2 [2].r[3].x + mv [2].offset.x >= 0 && mv2 [2].r[3].x + mv [2].offset.x <= 9;
}

inline bool Player3EmerginableDown (void)
{
	return player3.blist [19 + mv [2].offset.y + mv2 [2].r[0].y + 1].t [mv2 [2].r[0].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv2 [2].r[1].y + 1].t [mv2 [2].r[1].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv2 [2].r[2].y + 1].t [mv2 [2].r[2].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv2 [2].r[3].y + 1].t [mv2 [2].r[3].x + mv [2].offset.x] == 0
	 && mv2 [2].r[0].x + mv [2].offset.x >= 0 && mv2 [2].r[0].x + mv [2].offset.x <= 9
	 && mv2 [2].r[1].x + mv [2].offset.x >= 0 && mv2 [2].r[1].x + mv [2].offset.x <= 9
	 && mv2 [2].r[2].x + mv [2].offset.x >= 0 && mv2 [2].r[2].x + mv [2].offset.x <= 9
	 && mv2 [2].r[3].x + mv [2].offset.x >= 0 && mv2 [2].r[3].x + mv [2].offset.x <= 9;
}

inline bool Player3EmerginableNow (void)
{
	return player3.blist [19 + mv [2].offset.y + mv [2].r[0].y + 1].t [mv [2].r[0].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv [2].r[1].y + 1].t [mv [2].r[1].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv [2].r[2].y + 1].t [mv [2].r[2].x + mv [2].offset.x]
	+ player3.blist [19 + mv [2].offset.y + mv [2].r[3].y + 1].t [mv [2].r[3].x + mv [2].offset.x] == 0
	 && mv [2].r[0].x + mv [2].offset.x >= 0 && mv [2].r[0].x + mv [2].offset.x <= 9
	 && mv [2].r[1].x + mv [2].offset.x >= 0 && mv [2].r[1].x + mv [21].offset.x <= 9
	 && mv [2].r[2].x + mv [2].offset.x >= 0 && mv [2].r[2].x + mv [2].offset.x <= 9
	 && mv [2].r[3].x + mv [2].offset.x >= 0 && mv [2].r[3].x + mv [2].offset.x <= 9;
}

int Player3MoreThanMaxWait (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	//ブロックが出現できるかどうかテスト
	if (Player3EmerginableNext () || initial3 == -1)
	{
	//次のブロックが出現可能な場合
		if (Player3EmerginableDown () || initial3 == -1)

		{
		//次のブロックで、一段下に落ちることが可能な場合

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

			mv [2].offset.y++; //１足して、次の描画の処理に移る。
			ChangeBlock3 = 0;
			initial3 = 0;
		}
		else
		{
			//次のブロックで、一つ下に落ちることが不可能な場合。

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Color = clWhite;
				Canvas->Pen->Style = psSolid;
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = colorSelect [mv [2].bfnt / 4];

				//一ブロックのひな形
				Canvas->MoveTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->MoveTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (255 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->Pen->Color = clBlue;
				Canvas->Rectangle (241 + 16*(mv [2].r[j].x + mv [2].offset.x), 17 + 16*(mv [2].r[j].y + mv [2].offset.y), 254 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
				Canvas->FillRect (Rect (241 + 16*(mv [2].r[j].x + mv [2].offset.x), 17 + 16*(mv [2].r[j].y + mv [2].offset.y), 254 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y)));

				Canvas->Pen->Color = clBlack;
				Canvas->MoveTo (254 + 16*(mv [2].r[j].x + mv [2].offset.x), 17 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (254 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
			}

			player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			mv [2].offset.x = 2;
			mv [2].offset.y = 0;
			ChangeBlock3 = 1;
			initial3 = 0;
			wait3 = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [2] != 0)
				Player3Penalty ();

			return -1;
		}

		//if (ChangeBlock == 1)
		//{
		mv [2].bfnt = mv2 [2].bfnt; //新しいブロックに変える
		mv [2].type = mv2 [2].type;
		mv [2].player = mv2 [2].player;
		mv [2].mode = mv2 [2].mode;
		mv [2].r[0].x = mv2 [2].r[0].x;
		mv [2].r[1].x = mv2 [2].r[1].x;
		mv [2].r[2].x = mv2 [2].r[2].x;
		mv [2].r[3].x = mv2 [2].r[3].x;
		mv [2].r[0].y = mv2 [2].r[0].y;
		mv [2].r[1].y = mv2 [2].r[1].y;
		mv [2].r[2].y = mv2 [2].r[2].y;
		mv [2].r[3].y = mv2 [2].r[3].y;
		initial3 = 0;
	}
	else
	{
		//次のブロックが出現不能な場合
		if (Player3EmerginableNow ())
		{
		//ブロックが下に自然落下可能な場合

			Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = clBtnFace;

				//一ブロックのひな形
				Canvas->Pen->Color = clBtnFace;
				Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

			mv [2].offset.y++;

			for (int j = 0; j < 4; j++) {
				Canvas->Pen->Color = clWhite;
				Canvas->Pen->Style = psSolid;
				Canvas->Pen->Width = 1;
				Canvas->Brush->Color = colorSelect [mv [2].bfnt / 4];

				//一ブロックのひな形
				Canvas->MoveTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->MoveTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (255 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->Pen->Color = clBlue;
				Canvas->Rectangle (241 + 16*(mv [2].r[j].x + mv [2].offset.x), 17 + 16*(mv [2].r[j].y + mv [2].offset.y), 254 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->FillRect (Rect (241 + 16*(mv [2].r[j].x + mv [2].offset.x), 17 + 16*(mv [2].r[j].y + mv [2].offset.y), 254 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y)));

				Canvas->Pen->Color = clBlack;
				Canvas->MoveTo (254 + 16*(mv [2].r[j].x + mv [2].offset.x), 17 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (254 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
				Canvas->LineTo (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 30 + 16*(mv [2].r[j].y + mv [2].offset.y));
			}

			player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			mv [2].offset.x = 2;
			mv [2].offset.y = 0;
			initial3 = 0;
			//ChangeBlock = 1;
			ChangeBlock3 = 1;
			wait3 = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [2] != 0)
				Player3Penalty ();

			return -1;
		}
		else
		{
			//ブロックが下に自然落下不可能な場合
			player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
			mv [2].offset.x = 2;
			mv [2].offset.y = 0;
			//ChangeBlock = 1;
			ChangeBlock3 = 1;
			initial3 = 0;
			wait3 = 0;

			//ペナルティの作業を始める。
			if (ChargedBlocks [2] != 0)
				Player3Penalty ();

			return -1;
		}
	}
	return 1;
}

void Player1Penalty (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	for (int j = 0; j < 10; j++)
		player1.blist [38].t[j] = 0;

	std::reverse (player1.blist.begin (), player1.blist.end ());
	for (int i = 0; i < ChargedBlocks [0]; i++)
		player1.blist.insert (player1.blist.begin () + 1, ChargeWithHall [0]);
	player1.blist.resize (39);
	std::reverse (player1.blist.begin (), player1.blist.end ());
	ChargedBlocks [0] = 0;

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
		Canvas->Brush->Color = clBtnFace;
		Canvas->Rectangle (40 + 16*j, 16 + 16*(i-19), 55 + 16*j, 31 + 16*(i-19));
		Canvas->FillRect (Rect (40 + 16*j, 16 + 16*(i-19), 55 + 16*j, 31 + 16*(i-19)));
		}
	}
	}


	for (int i = 0; i < 10; i++)
		player1.blist [38].t [i] = 8;
}

void Player2Penalty (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	for (int j = 0; j < 10; j++)
		player2.blist [38].t[j] = 0;

	std::reverse (player2.blist.begin (), player2.blist.end ());
	for (int i = 0; i < ChargedBlocks [1]; i++)
		player2.blist.insert (player2.blist.begin () + 1, ChargeWithHall [1]);
	player2.blist.resize (39);
	std::reverse (player2.blist.begin (), player2.blist.end ());
	ChargedBlocks [1] = 0;

	for (int i = 19; i < 39; i++) {
	for (int j= 0; j < 10; j++) {
		if (player2.blist [i].t [j] != 0)
		{
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player2.blist [i].t[j] - 1];

			//一ブロックのひな形
			Canvas->MoveTo (440 + 16*j, 16 + 16*(i-19));
			Canvas->LineTo (440 + 16*j, 30 + 16*(i-19));
			Canvas->MoveTo (440 + 16*j, 16 + 16*(i-19));
			Canvas->LineTo (455 + 16*j, 16 + 16*(i-19));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (441 + 16*j, 17 + 16*(i-19), 454 + 16*j, 30 + 16*(i-19));
			Canvas->FillRect (Rect (441 + 16*j, 17 + 16*(i-19), 454 + 16*j, 30 + 16*(i-19)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (454 + 16*j, 17 + 16*(i-19));
			Canvas->LineTo (454 + 16*j, 30 + 16*(i-19));
			Canvas->LineTo (440 + 16*j, 30 + 16*(i-19));
		}
		else
		{
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19)));
		}
	}
	}

	for (int i = 0; i < 10; i++)
		player2.blist [38].t [i] = 8;
}

void Player3Penalty (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	for (int j = 0; j < 10; j++)
		player3.blist [38].t[j] = 0;

	std::reverse (player2.blist.begin (), player2.blist.end ());
	for (int i = 0; i < ChargedBlocks [2]; i++)
		player3.blist.insert (player3.blist.begin () + 1, ChargeWithHall [2]);
	player3.blist.resize (39);
	std::reverse (player3.blist.begin (), player3.blist.end ());
	ChargedBlocks [2] = 0;

	for (int i = 19; i < 39; i++) {
	for (int j= 0; j < 10; j++) {
		if (player3.blist [i].t [j] != 0)
		{

			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player3.blist [i].t[j] - 1];

			//一ブロックのひな形
			Canvas->MoveTo (240 + 16*j, 16 + 16*(i-19));
			Canvas->LineTo (240 + 16*j, 30 + 16*(i-19));
			Canvas->MoveTo (240 + 16*j, 16 + 16*(i-19));
			Canvas->LineTo (255 + 16*j, 16 + 16*(i-19));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (241 + 16*j, 17 + 16*(i-19), 254 + 16*j, 30 + 16*(i-19));
			Canvas->FillRect (Rect (241 + 16*j, 17 + 16*(i-19), 254 + 16*j, 30 + 16*(i-19)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (254 + 16*j, 17 + 16*(i-19));
			Canvas->LineTo (254 + 16*j, 30 + 16*(i-19));
			Canvas->LineTo (240 + 16*j, 30 + 16*(i-19));
		}
		else
		{
			//Canvas->Pen->Color = clBlack;
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (240 + 16*j, 16 + 16*(i-19), 255 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (240 + 16*j, 16 + 16*(i-19), 255 + 16*j, 31 + 16*(i-19)));
		}
	}
	}

	for (int i = 0; i < 10; i++)
		player3.blist [38].t [i] = 8;
}
//---------------------------------------------------------------------------
