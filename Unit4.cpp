//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit4.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;

//---------------------------------------------------------------------------
int music = 0, PlayMode = 1;
JOYCAPS joycaps, joycaps2, joycaps3;
JOYINFOEX joyinfoex, joyinfoex2, joyinfoex3;

DWORD midlex=0, flexx=0, midley=0, flexy=0;
DWORD midlex2=0, flexx2=0, midley2=0, flexy2=0;
DWORD midlex3=0, flexx3=0, midley3=0, flexy3=0;

int wait = 0, wait2 = 0, wait3 = 0;
int MaxWait = 40;
BlockList player1, player2, player3;
Mover mv [3], mv2 [3];
int ReservedX = 0, ReservedReturn = 0, ReservedDown = 0, ChangeBlock = -1;
int ReservedX2 = 0, ReservedReturn2 = 0, ReservedDown2 = 0, ChangeBlock2 = -1;
int ReservedX3 = 0, ReservedReturn3 = 0, ReservedDown3 = 0, ChangeBlock3 = -1;
int initial = 1, initial2 = 1, initial3 = 1;
std::vector<int> BlockTypeSeq (1);
long blockNumber = 0, blockNumber2 = 0, blockNumber3 = 0;
int TetrisHall [3];
int ChargedBlocks [3]; //ペナルティになっているブロックの高さ
int Charge2 [4] = {0, 1, 2, 4};
int Charge3 [4] = {0, 1, 1, 2};
int controllers = 0;

Block ChargeWithHall [3];
FILE *output2;

TColor colorSelect [7] = {clBlue, clLime, clFuchsia, clRed, clAqua, clYellow, clGray};
std::vector <BYTE> KeyTbl (256, 0);

int BFT1 [4][4][2]={{{2,0}, {2,1}, {2,2}, {2,3}}, {{0,2},{1,2},{2,2},{3,2}}, {{1,0}, {1,1}, {1,2}, {1,3}}, {{0,1}, {1,1}, {2,1}, {3,1}}};
int BFT2 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,0}}, {{1,1},{2,1},{3,1},{3,2}}, {{1,2}, {2,0}, {2,1}, {2,2}}, {{1,0}, {1,1}, {2,1}, {3,1}}};
int BFT3 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,1}}, {{1,1},{2,1},{3,1},{2,2}}, {{1,1}, {2,0}, {2,1}, {2,2}}, {{1,1}, {2,0}, {2,1}, {3,1}}};
int BFT4 [4][4][2]={{{2,0}, {2,1}, {2,2}, {3,2}}, {{1,1},{1,2},{2,1},{3,1}}, {{1,0}, {2,0}, {2,1}, {2,2}}, {{1,1}, {2,1}, {3,1}, {3,0}}};
int BFT5 [4][4][2]={{{1,0}, {1,1}, {2,1}, {2,2}}, {{1,2},{2,1},{2,2},{3,1}}, {{1,0}, {1,1}, {2,1}, {2,2}}, {{1,2},{2,1},{2,2},{3,1}}};
int BFT6 [4][4][2]={{{1,2}, {1,3}, {2,1}, {2,2}}, {{0,2},{1,2},{1,3},{2,3}}, {{1,2}, {1,3}, {2,1}, {2,2}}, {{0,2},{1,2},{1,3},{2,3}}};
int BFT7 [4][4][2]={{{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}, {{2,1}, {2,2}, {3,1}, {3,2}}};

__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}

void XY::operator =(XY a)
{
	x = a.x;
	y = a.y;
}

//---------------------------------------------------------------------------

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{

	if (music != 2) {
		return;
	}
	//Label1->Visible = True;
	//Label1->Visible = False;

   //Label1->Visible = True;

   //String YesNo[2] = {"No", "Yes"};
	for (int i = 0; i < 256; i++)
		KeyTbl [i] = GetAsyncKeyState (i); //キー入力

   //if (KeyTbl [83])
   //		Label1->Caption = "Yes";
   //else
   //		Label1->Caption = "No";

	KeyboardInputSwitch ();

	//ジョイスティック
	if (controllers >= 1)
		joystick1 ();
	if (controllers >= 2)
		joystick2 ();
	if (controllers >= 3)
		joystick3 ();

	if (wait + 1 >= MaxWait)
	{
		ReservedX = 0;
		ReservedDown = 0;
		ReservedReturn = 0;
	}
	if (wait2 + 1 >= MaxWait)
	{
		ReservedX2 = 0;
		ReservedDown2 = 0;
		ReservedReturn2 = 0;
	}
	if (wait3 + 1 >= MaxWait)
	{
		ReservedX3 = 0;
		ReservedDown3 = 0;
		ReservedReturn3 = 0;
	}

	//randomize ();
	srand ((unsigned int)time( 0 ));

	char tmpStr [100];
	//sprintf (tmpStr, "%d %d\n", wait, wait2);
	//Label1->Caption = tmpStr;

	int totalK = 0;
	std::vector<int> RememberingPosition (4, 0);

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
		Player1Elimination (totalK, RememberingPosition);
	}
	//ブロックの消去終わり

	//二人目のブロック消去
	if (PlayMode >= 2)
	{
		totalK = 0;
		for (int i = 0; i < 38; i++) {
			int k = 0;
			for (int j = 0; j < 10; j++) {
				if (player2.blist [i].t [j] != 0)
					k++;
			}
			if (k == 10) {
				RememberingPosition [totalK] = i;
				totalK++;
			}
		}
		if (totalK != 0) {
			Player2Elimination (totalK, RememberingPosition);
		}
	}
	//ブロックの消去終わり

	//三人目のブロック消去
	if (PlayMode >= 3)
	{
		totalK = 0;
		for (int i = 0; i < 38; i++) {
			int k = 0;
			for (int j = 0; j < 10; j++) {
				if (player3.blist [i].t [j] != 0)
					k++;
			}
			if (k == 10) {
				RememberingPosition [totalK] = i;
				totalK++;
			}
		}
		if (totalK != 0) {
			Player3Elimination (totalK, RememberingPosition);
		}
	}
	//ブロックの消去終わり

	if (ReservedDown == 1) {
		wait = MaxWait + 1;
	}
	if (ReservedDown2 == 1) {
		wait2 = MaxWait + 1;
	}
	if (ReservedDown3 == 1) {
		wait3 = MaxWait + 1;
	}

	for (int i = 0; i < 10; i++) {
		player1.blist [38].t [i] = 8;
		player2.blist [38].t [i] = 8;
		player3.blist [38].t [i] = 8;
	}

	//新しいブロックに変えるとき
	int tmp = BlockTypeSeq.size ();
	if (ChangeBlock == 1 || initial == 1){
		Player1Newblock ();
		if (initial == 1)
			initial = -1;
		return;
	}
	else
	{
		wait++;
	}

	//二人目のブロックを変えるとき
	if (PlayMode == 2 || PlayMode == 3)
	{
		if (ChangeBlock2 == 1 || initial2 == 1){
			Player2Newblock ();
			if (initial2 == 1)
				initial2 = -1;
			return;
		}
		else
		{
			wait2++;
		}
	}

	//三人目のブロックを変えるとき
	if (PlayMode == 3)
	{
		if (ChangeBlock3 == 1 || initial3 == 1){
			Player3Newblock ();
			if (initial3 == 1)
				initial3 = -1;
			return;
		}
		else
		{
			wait3++;
		}
	}

	if (initial == -1)
		Player1Reinitialize ();
	if (initial2 == -1 && PlayMode >= 2)
		Player2Reinitialize ();
	if (initial3 == -1 && PlayMode >= 3)
		Player3Reinitialize ();

	static int i = 3;

	if (ReservedDown == 1 && ChangeBlock == 0)
		Player1DoNotChangeBlock ();

	if (ReservedDown2 == 1 && ChangeBlock2 == 0 && PlayMode >= 2)
		Player2DoNotChangeBlock ();

	if (ReservedDown3 == 1 && ChangeBlock3 == 0 && PlayMode >= 3)
		Player3DoNotChangeBlock ();

	//回転が予約されている場合
	if (ReservedReturn == 1)
		if (Player1Rotate () == -1)
			return;

	//回転終了

	//回転が予約されている場合（二人目のブロック）
	if (ReservedReturn2 == 1 && PlayMode >= 2)
		if (Player2Rotate () == -1)
			return;

	//回転終了

	//回転が予約されている場合（三人目のブロック）
	if (ReservedReturn3 == 1 && PlayMode >= 3)
		if (Player3Rotate () == -1)
			return;

	//回転終了

	if (ReservedX != 0)
	{
		Player1Slide ();
		ReservedX = 0;
		return;
	}
	//wait = 0;

	if (ReservedX2 != 0 && PlayMode >= 2)
	{
		Player2Slide ();
		ReservedX2 = 0;
		return;
	}
	//wait = 0;


	if (ReservedX3 != 0 && PlayMode >= 3)
	{
		Player3Slide ();
		ReservedX3 = 0;
		return;
	}
	//wait = 0;

	if (wait + 1 >= MaxWait)
	{
		wait = 0;
		if (Player1MoreThanMaxWait () == -1)
			return;
	}
	else
	{
		wait++;
	}

	//2プレイヤーについて、同様。
	if (wait2 + 1 >= MaxWait && PlayMode >= 2)
	{
		wait2 = 0;
		if (Player2MoreThanMaxWait () == -1)
			return;
	}
	else
	{
		wait2++;
	}

	//3プレイヤーについて、同様。
	if (wait3 + 1 >= MaxWait && PlayMode >= 3)
	{
		wait3 = 0;
		if (Player3MoreThanMaxWait () == -1)
			return;
	}
	else
	{
		wait3++;
	}

	LeftRepaint ();

	if (PlayMode >= 2)
		RightRepaint ();


	if (PlayMode >= 3)
		CenterRepaint ();
}
//---------------------------------------------------------------------------

