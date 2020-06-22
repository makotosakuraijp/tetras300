//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit4.h"
#include <deque>
#include <vector>
#include <hidsdi.h>
#include <windows.h> //���ꂪ�����ƁAmmsystem�֘A�̃G���[���ł�
#include <mmsystem.h>
#include <winuser.h> //�L�[�R�[�h�ꗗ

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
int music = 0, PlayMode = 1;

JOYCAPS joycaps, joycaps2, joycaps3;
JOYINFOEX joyinfoex, joyinfoex2, joyinfoex3;
unsigned int midlex=0, flexx=0, midley=0, flexy=0;
unsigned int midlex2=0, flexx2=0, midley2=0, flexy2=0;
unsigned int midlex3=0, flexx3=0, midley3=0, flexy3=0;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent*
 Owner)
	: TForm(Owner)
{
}
// �����̃f�[�^
class Block
{
	public:
	int                     t [10]; //�u���b�N�̑����B�ԕ��͍��Ȃ�
	int                     bfnt [10]; //�F����
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
//�v���C��ʑS�̂̃u���b�N38��
class BlockList
{
public:
	//Block                   blist [39]; //�����Ă��镔���P�X�{�\���P�X�{�P
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
	x = 2;
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



class Mover //�����u���b�N
{
//	DRAW                    it;
public:
	static TCanvas *canvas;
	XY                      offset; //����̗��_���W
	XY                      r [4];
	int                     bfnt; //�u���b�N�̃^�C�v�ƐF���i��
	int                     type; //���Ԗڂ̃u���b�N��
	int                     player; //���Ԗڂ̃v���[���[��
	int                     mode; //�v���C���[�̃��[�h�B��l�A��l�ΐ�A�O�l�ΐ�B
//							MOVER (void);
//	void                    enter (void);
//	void                    in (void); //�L�����o�X�ɕ`��
//	void                    out (void);
//	void                    change (int _x, int _y, int _bfnt, int _player, int _mode);
//	int                     can_put (BLOCK_LIST a, MOVER b);
//	int                     turn_enable (BLOCK_LIST a);
//	void                    turn (int errlv);
//	int                     move_enable (BLOCK_LIST a, XY b);
//	void                    move (XY a, int errlv);
};
//---------------------------------------------------------------------------
int wait = 0, wait2 = 0, wait3 = 0;
int MaxWait = 100;
BlockList player1, player2, player3;
Mover mv [3], mv2 [3];
static int ReservedX = 0, ReservedReturn = 0, ReservedDown = 0, ChangeBlock = -1;
static int ReservedX2 = 0, ReservedReturn2 = 0, ReservedDown2 = 0, ChangeBlock2 = -1;
static int ReservedX3 = 0, ReservedReturn3 = 0, ReservedDown3 = 0, ChangeBlock3 = -1;
static int initial = 1, initial2 = 1, initial3 = 1;
std::vector<int> BlockTypeSeq (1);
long blockNumber = 0, blockNumber2 = 0, blockNumber3 = 0;
int TetrisHall [3];
int ChargedBlocks [3]; //�y�i���e�B�ɂȂ��Ă���u���b�N�̍���
int Charge2 [4] = {0, 1, 2, 4};
int Charge3 [4] = {0, 1, 1, 2};
//TCanvas *Mover::canvas = TForm28::Canvas;
Block ChargeWithHall [3];

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
	if (music != 2) {
		return;
	}
	//Label1->Visible = True;
	//Label1->Visible = False;

   //Label1->Visible = True;

	BYTE KeyTbl[256];
   //String YesNo[2] = {"No", "Yes"};
	for (int i = 0; i < 256; i++)
		KeyTbl [i] = GetAsyncKeyState (i); //�L�[����

   //if (KeyTbl [83])
   //		Label1->Caption = "Yes";
   //else
   //		Label1->Caption = "No";

			switch (PlayMode) {
	case 1:
		if (KeyTbl [65] || KeyTbl [76] || KeyTbl [VK_LEFT] || KeyTbl [VK_NUMPAD4])
		{
			Label1->Caption = "Left";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
				ReservedX = -1;
		}

			//�E�L�[
		//	case vkD:
		//	case 186: //�R����
		//	case vkRight:
		//	case vkNumpad6:
		if (KeyTbl [68] || KeyTbl [186] || KeyTbl [VK_RIGHT] || KeyTbl [VK_NUMPAD6])
		{
			Label1->Caption = "Right";
			//Label1->Caption = ShortCutToText(ShortCut(Word(':'), Shift));

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
				ReservedX = 1;
		}

			//��]�L�[
		//	case vkS:
		//	case 187: //�Z�~�R����
		//	case vkReturn:
		//	case vkNumpad5:
		if (KeyTbl [83] || KeyTbl [187] || KeyTbl [VK_RETURN] || KeyTbl [VK_NUMPAD5])
		{

			Label1->Caption = "Return";
			if (ReservedX == 0)
				ReservedReturn = 1;
		}

			//case vkX:
			//case vkSlash:
			//case vkDown:
			//case vkNumpad2:
		if (KeyTbl [88] || KeyTbl [VK_OEM_2] || KeyTbl [VK_DOWN] || KeyTbl [VK_NUMPAD2])
		{
			Label1->Caption = "Down";
			if (ReservedX == 0)
				ReservedDown = 1;
			//break;
		}
		break;
	case 2:
		if (KeyTbl [65] || KeyTbl [76])
		{
			Label1->Caption = "Left1";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
				ReservedX = -1;
		}

		if (KeyTbl [VK_LEFT] || KeyTbl [VK_NUMPAD4])
		{
			Label1->Caption = "Left2";

			if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x - 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x - 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x - 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x - 1] == 0
				&& (mv [1].r[0].x + mv [1].offset.x) > 0 && (mv [1].r[1].x + mv [1].offset.x) > 0 && (mv [1].r[2].x + mv [1].offset.x) > 0 && (mv [1].r[3].x + mv [1].offset.x) > 0)
					ReservedX2 = -1;
		}

			//�E�L�[
		if (KeyTbl [68] || KeyTbl [186])
		{
			Label1->Caption = "Right1";
			//Label1->Caption = ShortCutToText(ShortCut(Word(':'), Shift));

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
				ReservedX = 1;
		}

		if (KeyTbl [VK_RIGHT] || KeyTbl [VK_NUMPAD6])
		{
			Label1->Caption = "Right2";
			//Label1->Caption = ShortCutToText(ShortCut(Word(':'), Shift));

				if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x + 1]
															   + player2.blist [19 + mv [1].offset.y + mv[1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x + 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x + 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x + 1] == 0
				&& (mv [1].r[0].x + mv [1].offset.x) < 9 && (mv [1].r[1].x + mv [1].offset.x) < 9 && (mv [1].r[2].x + mv [1].offset.x) < 9 && (mv [1].r[3].x + mv [1].offset.x) < 9)
					ReservedX2 = 1;
		}

			//��]�L�[
		if (KeyTbl [83] || KeyTbl [187])
		{
			Label1->Caption = "Return1";
			if (ReservedX == 0)
				ReservedReturn = 1;
		}

		if (KeyTbl [VK_RETURN] || KeyTbl [VK_NUMPAD5])
		{
			Label1->Caption = "Return2";
			if (ReservedX2 == 0)
				ReservedReturn2 = 1;
		}

		if (KeyTbl [88] || KeyTbl [VK_OEM_2])
		{
			Label1->Caption = "Down1";
			if (ReservedX == 0)
				ReservedDown = 1;
		}


		if (KeyTbl [VK_DOWN] || KeyTbl [VK_NUMPAD2])
		{
			Label1->Caption = "Down2";
			if (ReservedX2 == 0)
				ReservedDown2 = 1;
		}
		break;

	case 3:
			//���L�[
			case vkA:
		if (KeyTbl [65])
		{
			Label1->Caption = "Left1";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
				ReservedX = -1;
		}

		if (KeyTbl [65] || KeyTbl [76] || KeyTbl [VK_LEFT] || KeyTbl [VK_NUMPAD4])
		{
			Label1->Caption = "Left2";

			if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x - 1]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x - 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x - 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x - 1] == 0
			&& (mv [1].r[0].x + mv [1].offset.x) > 0 && (mv [1].r[1].x + mv [1].offset.x) > 0 && (mv [1].r[2].x + mv [1].offset.x) > 0 && (mv [1].r[3].x + mv [1].offset.x) > 0)
				ReservedX2 = -1;
		}

			//���L�[
		if (KeyTbl [76])
		{
			case vkL:
			Label1->Caption = "Left3";

			if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x - 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x - 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x - 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x - 1] == 0
			&& (mv [2].r[0].x + mv [2].offset.x) > 0 && (mv [2].r[1].x + mv [2].offset.x) > 0 && (mv [2].r[2].x + mv [2].offset.x) > 0 && (mv [2].r[3].x + mv [2].offset.x) > 0)
				ReservedX3 = -1;
		}

			//�E�L�[
		if (KeyTbl [68])
		{
			Label1->Caption = "Right1";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
				ReservedX = 1;
		}

		if (KeyTbl [VK_RIGHT] || KeyTbl [VK_NUMPAD6])
		{
			Label1->Caption = "Right2";

			if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x + 1]
														   + player2.blist [19 + mv [1].offset.y + mv[1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x + 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x + 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x + 1] == 0
			&& (mv [1].r[0].x + mv [1].offset.x) < 9 && (mv [1].r[1].x + mv [1].offset.x) < 9 && (mv [1].r[2].x + mv [1].offset.x) < 9 && (mv [1].r[3].x + mv [1].offset.x) < 9)
				ReservedX2 = 1;
		}

		if (KeyTbl [186])
		{
			Label1->Caption = "Right3";

			if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x + 1]
														   + player3.blist [19 + mv [2].offset.y + mv[2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x + 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x + 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x + 1] == 0
			&& (mv [2].r[0].x + mv [2].offset.x) < 9 && (mv [2].r[1].x + mv [2].offset.x) < 9 && (mv [2].r[2].x + mv [2].offset.x) < 9 && (mv [2].r[3].x + mv [2].offset.x) < 9)
				ReservedX3 = 1;
		}

			//��]�L�[
		if (KeyTbl [83])
		{
			Label1->Caption = "Return1";
			if (ReservedX == 0)
				ReservedReturn = 1;
		}

		if (KeyTbl [VK_RETURN] || KeyTbl [VK_NUMPAD5])
		{
			Label1->Caption = "Return2";
			if (ReservedX2 == 0)
				ReservedReturn2 = 1;
		}

		if (KeyTbl [187])
		{
			Label1->Caption = "Return3";
			if (ReservedX3 == 0)
				ReservedReturn3 = 1;
		}

		if (KeyTbl [88])
		{
			Label1->Caption = "Down1";
			if (ReservedX == 0)
				ReservedDown = 1;
		}


		if (KeyTbl [VK_DOWN] || KeyTbl [VK_NUMPAD2])
		{
			Label1->Caption = "Down2";
			if (ReservedX2 == 0)
				ReservedDown2 = 1;
		}

		if (KeyTbl [VK_OEM_2])
		{
			Label1->Caption = "Down3";
			if (ReservedX3 == 0)
				ReservedDown3 = 1;
		}
		break;
		default:
		break;
	}

	   joyGetPosEx(JOYSTICKID1,&joyinfoex);
	if(joyinfoex.dwXpos > midlex + flexx)
	{
		if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
		&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
		{
		//�u���b�N���E�Ɉړ��\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
	Label1->Caption ="RIGHT"; //midle=32K
	}
	if(joyinfoex.dwXpos < midlex - flexx)
	{
		if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
		&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
		{
		//�u���b�N�����Ɉړ��\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
	Label1->Caption ="LEFT";
	}
	if(joyinfoex.dwYpos > midley + flexy && ReservedX == 0)
	{
		ReservedDown = 1;
		Label1->Caption ="DOWN";
	}
	if(joyinfoex.dwButtons==JOY_BUTTON1)
	{
		ReservedX = 0;
		ReservedReturn = 1;
		Label1->Caption ="BUTTON"; //buttonA
	}

	joyGetPosEx(JOYSTICKID2,&joyinfoex2);
	if(joyinfoex2.dwXpos > midlex2 + flexx2)
	{
		if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x + 1]
													   + player1.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x + 1]
													   + player1.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x + 1]
													   + player1.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x + 1] == 0
		&& (mv [1].r[0].x + mv [1].offset.x) < 9 && (mv [1].r[1].x + mv [1].offset.x) < 9 && (mv [1].r[2].x + mv [1].offset.x) < 9 && (mv [1].r[3].x + mv [1].offset.x) < 9)
		{
		//�u���b�N���E�Ɉړ��\�ȏꍇ
		//mv.offset.y--;

		ReservedX2 = 1;
		/*	Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
	Label1->Caption ="RIGHT2"; //midle=32K
	}
	if(joyinfoex2.dwXpos < midlex2 - flexx2)
	{
		if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x - 1]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x - 1]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x - 1]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x - 1] == 0
		&& (mv [1].r[0].x + mv [1].offset.x) > 0 && (mv [1].r[1].x + mv [1].offset.x) > 0 && (mv [1].r[2].x + mv [1].offset.x) > 0 && (mv [1].r[3].x + mv [1].offset.x) > 0)
		{
		//�u���b�N�����Ɉړ��\�ȏꍇ
		//mv.offset.y--;

		ReservedX2 = -1;
		/*	Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
	Label1->Caption ="LEFT2";
	}
	if(joyinfoex2.dwYpos > midley2 + flexy2 && ReservedX2 == 0)
	{
		ReservedDown2 = 1;
		Label1->Caption ="DOWN2";
	}
	if(joyinfoex2.dwButtons==JOY_BUTTON1)
	{
		ReservedX2 = 0;
		ReservedReturn2 = 1;
		Label1->Caption ="BUTTON2"; //buttonA
	}

	joyGetPosEx(JOYSTICKID1+2,&joyinfoex3);
	if(joyinfoex3.dwXpos > midlex3 + flexx3)
	{
		if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x + 1]
													   + player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x + 1]
													   + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x + 1]
													   + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x + 1] == 0
		&& (mv [2].r[0].x + mv [2].offset.x) < 9 && (mv [2].r[1].x + mv [2].offset.x) < 9 && (mv [2].r[2].x + mv [2].offset.x) < 9 && (mv [2].r[3].x + mv [2].offset.x) < 9)
		{
		//�u���b�N���E�Ɉړ��\�ȏꍇ
		//mv.offset.y--;

		ReservedX3 = 1;
		/*	Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
	Label1->Caption ="RIGHT3"; //midle=32K
	}
	if(joyinfoex3.dwXpos < midlex3 - flexx3)
	{
		if (player1.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x - 1]
													   + player1.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x - 1]
													   + player1.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x - 1]
													   + player1.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x - 1] == 0
		&& (mv [2].r[0].x + mv [2].offset.x) > 0 && (mv [2].r[1].x + mv [2].offset.x) > 0 && (mv [2].r[2].x + mv [2].offset.x) > 0 && (mv [2].r[3].x + mv [2].offset.x) > 0)
		{
		//�u���b�N�����Ɉړ��\�ȏꍇ
		//mv.offset.y--;

		ReservedX3 = -1;
		/*	Canvas->Pen->Color = clBtnFace;
			Canvas->Brush->Color = clBtnFace;
			//Canvas->Rectangle (40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y);
			//Canvas->FillRect (Rect(40, 15 + 16*mv.offset.y, 104, 79 + 16*mv.offset.y));
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
	Label1->Caption ="LEFT3";
	}
	if(joyinfoex3.dwYpos > midley3 + flexy3 && ReservedX3 == 0)
	{
		ReservedDown3 = 1;
		Label1->Caption ="DOWN3";
	}
	if(joyinfoex3.dwButtons==JOY_BUTTON1)
	{
		ReservedX3 = 0;
		ReservedReturn3 = 1;
		Label1->Caption ="BUTTON3"; //buttonA
	}


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
	TColor colorSelect [7] = {clBlue, clLime, clFuchsia, clRed, clAqua, clYellow, clGray};
	//randomize ();
	srand ((unsigned int)time( 0 ));

	char tmpStr [100];
	//sprintf (tmpStr, "%d %d\n", wait, wait2);
	//Label1->Caption = tmpStr;

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
		//�u���b�N�������n�߂�
		//Graphics::TBitmap* Bitmap = new Graphics::TBitmap();
		//Bitmap->Canvas->CopyMode = cmSrcCopy;
		//Bitmap->Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));

		//Canvas->CopyMode = cmSrcCopy;
		//Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Bitmap->Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));
		if (PlayMode == 2)
			ChargedBlocks [1] += Charge2 [totalK - 1];
		else
		{
			ChargedBlocks [1] += Charge3 [totalK - 1];
			ChargedBlocks [2] += Charge3 [totalK - 1];
		}
		for (int k = 0; k < 10; k++) {
		for (int i = 0; i < totalK; i++) {
		for (int j = 0; j < 10; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player1.blist [RememberingPosition [i]].t[j] - 1];

			//��u���b�N�̂ЂȌ`
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

			//��u���b�N�̂ЂȌ`
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

			//��u���b�N�̂ЂȌ`
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
	//�u���b�N�̏����I���

	//��l�ڂ̃u���b�N����
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
		//�u���b�N�������n�߂�
		//Graphics::TBitmap* Bitmap = new Graphics::TBitmap();
		//Bitmap->Canvas->CopyMode = cmSrcCopy;
		//Bitmap->Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));

		//Canvas->CopyMode = cmSrcCopy;
		//Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Bitmap->Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));
		if (PlayMode == 2)
			ChargedBlocks [0] += Charge2 [totalK - 1];
		else
		{
			ChargedBlocks [0] += Charge3 [totalK - 1];
			ChargedBlocks [2] += Charge3 [totalK - 1];
		}
		for (int k = 0; k < 10; k++) {
		for (int i = 0; i < totalK; i++) {
		for (int j = 0; j < 10; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player2.blist [RememberingPosition [i]].t[j] - 1];

			//��u���b�N�̂ЂȌ`
			Canvas->MoveTo (440 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (440 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->MoveTo (440 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (455 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (441 + 16*j, 17 + 16*(RememberingPosition [i]-19), 454 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->FillRect (Rect (441 + 16*j, 17 + 16*(RememberingPosition [i]-19), 454 + 16*j, 30 + 16*(RememberingPosition [i]-19)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (454 + 16*j, 17 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (454 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (440 + 16*j, 30 + 16*(RememberingPosition [i]-19));

		}
		}

			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;

		for (int i = 0; i < totalK; i++) {
		Canvas->Rectangle (440, 16 + 16*(RememberingPosition [i]-19), 455 + 16*9, 31 + 16*(RememberingPosition [i]-19));
		Canvas->FillRect (Rect (440, 16 + 16*(RememberingPosition [i]-19), 455 + 16*9, 31 + 16*(RememberingPosition [i]-19)));
		}
		}


		for (int k = 0; k < 4; k++)
			RememberingPosition [k] = 0;

		for (int j = 0; j < 10; j++)
			player2.blist [38].t[j] = 0;

		std::reverse (player2.blist.begin (), player2.blist.end ());
		for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player2.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player2.blist.erase (player2.blist.begin () + i);
				player2.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}
		std::reverse (player2.blist.begin (), player2.blist.end ());
		totalK = 0;

		for (int i = 19; i < 39; i++) {
		for (int j= 0; j < 10; j++) {
			if (player2.blist [i].t [j] != 0)
			{

			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player2.blist [i].t[j] - 1];

			//��u���b�N�̂ЂȌ`
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
			//Canvas->Pen->Color = clBlack;
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19)));
			}

		}
		}


		for (int i = 0; i < 10; i++) {
			player2.blist [38].t [i] = 8;
		}
	}
	}
	//�u���b�N�̏����I���

	//�O�l�ڂ̃u���b�N����
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
		//�u���b�N�������n�߂�
		//Graphics::TBitmap* Bitmap = new Graphics::TBitmap();
		//Bitmap->Canvas->CopyMode = cmSrcCopy;
		//Bitmap->Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));

		//Canvas->CopyMode = cmSrcCopy;
		//Canvas->CopyRect (Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)), Bitmap->Canvas, Rect(40, 16 + 16*(RememberingPosition [0]-19), 55 + 16*9, 31 + 16*(RememberingPosition [0]-19)));
		ChargedBlocks [0] += Charge3 [totalK - 1];
		ChargedBlocks [1] += Charge3 [totalK - 1];

		for (int k = 0; k < 10; k++) {
		for (int i = 0; i < totalK; i++) {
		for (int j = 0; j < 10; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player3.blist [RememberingPosition [i]].t[j] - 1];

			//��u���b�N�̂ЂȌ`
			Canvas->MoveTo (240 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (240 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->MoveTo (240 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (255 + 16*j, 16 + 16*(RememberingPosition [i]-19));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (241 + 16*j, 17 + 16*(RememberingPosition [i]-19), 254 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->FillRect (Rect (241 + 16*j, 17 + 16*(RememberingPosition [i]-19), 254 + 16*j, 30 + 16*(RememberingPosition [i]-19)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (254 + 16*j, 17 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (254 + 16*j, 30 + 16*(RememberingPosition [i]-19));
			Canvas->LineTo (240 + 16*j, 30 + 16*(RememberingPosition [i]-19));

		}
		}

			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;

		for (int i = 0; i < totalK; i++) {
		Canvas->Rectangle (240, 16 + 16*(RememberingPosition [i]-19), 255 + 16*9, 31 + 16*(RememberingPosition [i]-19));
		Canvas->FillRect (Rect (240, 16 + 16*(RememberingPosition [i]-19), 255 + 16*9, 31 + 16*(RememberingPosition [i]-19)));
		}
		}


		for (int k = 0; k < 4; k++)
			RememberingPosition [k] = 0;

		for (int j = 0; j < 10; j++)
			player3.blist [38].t[j] = 0;

		std::reverse (player3.blist.begin (), player3.blist.end ());
		for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player3.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player3.blist.erase (player3.blist.begin () + i);
				player3.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}
		std::reverse (player3.blist.begin (), player3.blist.end ());
		totalK = 0;

		for (int i = 19; i < 39; i++) {
		for (int j= 0; j < 10; j++) {
			if (player3.blist [i].t [j] != 0)
			{

			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [player3.blist [i].t[j] - 1];

			//��u���b�N�̂ЂȌ`
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


		for (int i = 0; i < 10; i++) {
			player3.blist [38].t [i] = 8;
		}
	}
	}
	//�u���b�N�̏����I���

	if (ReservedDown == 1) {
		wait = MaxWait + 1;
	}
	if (ReservedDown2 == 1) {
		wait2 = MaxWait + 1;
	}
	if (ReservedDown3 == 1) {
		wait3 = MaxWait + 1;
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
		player2.blist [38].t [i] = 8;
		player3.blist [38].t [i] = 8;
	}
	//Canvas->Pen->Color = clBlue;
	//Canvas->Pen->Style = psSolid;
	//Canvas->Pen->Width = 1;
	//Canvas->Brush->Color = clBlue;
	//Canvas->Rectangle (39, 15, 200, 320);
	//Canvas->Rectangle (239, 15, 400, 320);
	//Canvas->Rectangle (439, 15, 600, 320);

	//�V�����u���b�N�ɕς���Ƃ�
	int tmp = BlockTypeSeq.size ();
	if (ChangeBlock == 1 || initial == 1){
		if (blockNumber >= BlockTypeSeq.size ())
		{
			mv2 [0].bfnt = std::rand () % 28; //�V�����u���b�N�ɕς���
			BlockTypeSeq.resize (blockNumber + 1);
			BlockTypeSeq [blockNumber] = mv2 [0].bfnt;
			blockNumber++;
		}
		else
		{
			mv2 [0].bfnt = BlockTypeSeq [blockNumber]; //�V�����u���b�N�ɕς���
			blockNumber++;
		}
		mv2 [0].type = mv2 [0].bfnt % 4;
		mv2 [0].player = 1;
		mv2 [0].mode = 1;
		switch (mv2 [0].bfnt / 4) {
			case 0:
			mv2 [0].r[0].x = BFT1 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT1 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT1 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT1 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT1 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT1 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT1 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT1 [mv2 [0].type][3][1];
			break;

			case 1:
			mv2 [0].r[0].x = BFT2 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT2 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT2 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT2 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT2 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT2 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT2 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT2 [mv2 [0].type][3][1];
			break;
			case 2:
			mv2 [0].r[0].x = BFT3 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT3 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT3 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT3 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT3 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT3 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT3 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT3 [mv2 [0].type][3][1];
			break;
			case 3:
			mv2 [0].r[0].x = BFT4 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT4 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT4 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT4 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT4 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT4 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT4 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT4 [mv2 [0].type][3][1];
			break;
			case 4:
			mv2 [0].r[0].x = BFT5 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT5 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT5 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT5 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT5 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT5 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT5 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT5 [mv2 [0].type][3][1];
			break;
			case 5:
			mv2 [0].r[0].x = BFT6 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT6 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT6 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT6 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT6 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT6 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT6 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT6 [mv2 [0].type][3][1];
			break;
			case 6:
			mv2 [0].r[0].x = BFT7 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT7 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT7 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT7 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT7 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT7 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT7 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT7 [mv2 [0].type][3][1];
			break;
		}
		if (ChangeBlock == 1)
		{
			mv [0].bfnt = mv2 [0].bfnt;
			mv [0].type = mv2 [0].type;
			mv [0].r[0].x = mv2 [0].r[0].x;
			mv [0].r[1].x = mv2 [0].r[1].x;
			mv [0].r[2].x = mv2 [0].r[2].x;
			mv [0].r[3].x = mv2 [0].r[3].x;
			mv [0].r[0].y = mv2 [0].r[0].y;
			mv [0].r[1].y = mv2 [0].r[1].y;
			mv [0].r[2].y = mv2 [0].r[2].y;
			mv [0].r[3].y = mv2 [0].r[3].y;

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


	//��l�ڂ̃u���b�N��ς���Ƃ�
	if (PlayMode == 2 || PlayMode == 3)
	{
	if (ChangeBlock2 == 1 || initial2 == 1){
		if (blockNumber2 >= BlockTypeSeq.size())
		{
			mv2 [1].bfnt = std::rand () % 28; //�V�����u���b�N�ɕς���
			BlockTypeSeq.resize (blockNumber2 + 1);
			BlockTypeSeq [blockNumber2] = mv2 [1].bfnt;
			blockNumber2++;
		}
		else
		{
			mv2 [1].bfnt = BlockTypeSeq [blockNumber2]; //�V�����u���b�N�ɕς���
			blockNumber2++;
		}
		mv2 [1].type = mv2 [1].bfnt % 4;
		mv2 [1].player = 1;
		mv2 [1].mode = 1;
		switch (mv2 [1].bfnt / 4) {
			case 0:
			mv2 [1].r[0].x = BFT1 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT1 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT1 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT1 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT1 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT1 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT1 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT1 [mv2 [1].type][3][1];
			break;

			case 1:
			mv2 [1].r[0].x = BFT2 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT2 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT2 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT2 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT2 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT2 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT2 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT2 [mv2 [1].type][3][1];
			break;
			case 2:
			mv2 [1].r[0].x = BFT3 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT3 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT3 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT3 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT3 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT3 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT3 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT3 [mv2 [1].type][3][1];
			break;
			case 3:
			mv2 [1].r[0].x = BFT4 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT4 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT4 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT4 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT4 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT4 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT4 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT4 [mv2 [1].type][3][1];
			break;
			case 4:
			mv2 [1].r[0].x = BFT5 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT5 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT5 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT5 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT5 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT5 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT5 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT5 [mv2 [1].type][3][1];
			break;
			case 5:
			mv2 [1].r[0].x = BFT6 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT6 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT6 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT6 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT6 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT6 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT6 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT6 [mv2 [1].type][3][1];
			break;
			case 6:
			mv2 [1].r[0].x = BFT7 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT7 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT7 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT7 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT7 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT7 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT7 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT7 [mv2 [1].type][3][1];
			break;
		}
		if (ChangeBlock2 == 1)
		{
			mv [1].bfnt = mv2 [1].bfnt;
			mv [1].type = mv2 [1].type;
			mv [1].r[0].x = mv2 [1].r[0].x;
			mv [1].r[1].x = mv2 [1].r[1].x;
			mv [1].r[2].x = mv2 [1].r[2].x;
			mv [1].r[3].x = mv2 [1].r[3].x;
			mv [1].r[0].y = mv2 [1].r[0].y;
			mv [1].r[1].y = mv2 [1].r[1].y;
			mv [1].r[2].y = mv2 [1].r[2].y;
			mv [1].r[3].y = mv2 [1].r[3].y;

			ChangeBlock2 = -1;
		}
		if (initial2 == 1)
			initial2 = -1;
		return;
	}
	else
	{
		wait2++;
	}
	}

	//�O�l�ڂ̃u���b�N��ς���Ƃ�
	if (PlayMode == 3)
	{
	if (ChangeBlock3 == 1 || initial3 == 1){
		if (blockNumber3 >= BlockTypeSeq.size())
		{
			mv2 [2].bfnt = std::rand () % 28; //�V�����u���b�N�ɕς���
			BlockTypeSeq.resize (blockNumber3 + 1);
			BlockTypeSeq [blockNumber3] = mv2 [2].bfnt;
			blockNumber3++;
		}
		else
		{
			mv2 [2].bfnt = BlockTypeSeq [blockNumber3]; //�V�����u���b�N�ɕς���
			blockNumber3++;
		}
		mv2 [2].type = mv2 [2].bfnt % 4;
		mv2 [2].player = 1;
		mv2 [2].mode = 1;
		switch (mv2 [2].bfnt / 4) {
			case 0:
			mv2 [2].r[0].x = BFT1 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT1 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT1 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT1 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT1 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT1 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT1 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT1 [mv2 [2].type][3][1];
			break;

			case 1:
			mv2 [2].r[0].x = BFT2 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT2 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT2 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT2 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT2 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT2 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT2 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT2 [mv2 [2].type][3][1];
			break;
			case 2:
			mv2 [2].r[0].x = BFT3 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT3 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT3 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT3 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT3 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT3 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT3 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT3 [mv2 [2].type][3][1];
			break;
			case 3:
			mv2 [2].r[0].x = BFT4 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT4 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT4 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT4 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT4 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT4 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT4 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT4 [mv2 [2].type][3][1];
			break;
			case 4:
			mv2 [2].r[0].x = BFT5 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT5 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT5 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT5 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT5 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT5 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT5 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT5 [mv2 [2].type][3][1];
			break;
			case 5:
			mv2 [2].r[0].x = BFT6 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT6 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT6 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT6 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT6 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT6 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT6 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT6 [mv2 [2].type][3][1];
			break;
			case 6:
			mv2 [2].r[0].x = BFT7 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT7 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT7 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT7 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT7 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT7 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT7 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT7 [mv2 [2].type][3][1];
			break;
		}
		if (ChangeBlock3 == 1)
		{
			mv [2].bfnt = mv2 [2].bfnt;
			mv [2].type = mv2 [2].type;
			mv [2].r[0].x = mv2 [2].r[0].x;
			mv [2].r[1].x = mv2 [2].r[1].x;
			mv [2].r[2].x = mv2 [2].r[2].x;
			mv [2].r[3].x = mv2 [2].r[3].x;
			mv [2].r[0].y = mv2 [2].r[0].y;
			mv [2].r[1].y = mv2 [2].r[1].y;
			mv [2].r[2].y = mv2 [2].r[2].y;
			mv [2].r[3].y = mv2 [2].r[3].y;

			ChangeBlock3 = -1;
		}
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
	{
		mv [0].bfnt = mv2 [0].bfnt;
		mv [0].type = mv2 [0].type;
		mv [0].player = 1;
		mv [0].mode = 1;
		mv [0].r[0].x = mv2 [0].r[0].x;
		mv [0].r[1].x = mv2 [0].r[1].x;
		mv [0].r[2].x = mv2 [0].r[2].x;
		mv [0].r[3].x = mv2 [0].r[3].x;
		mv [0].r[0].y = mv2 [0].r[0].y;
		mv [0].r[1].y = mv2 [0].r[1].y;
		mv [0].r[2].y = mv2 [0].r[2].y;
		mv [0].r[3].y = mv2 [0].r[3].y;
	}
	if (initial2 == -1 && PlayMode >= 2)
	{
		mv [1].bfnt = mv2 [1].bfnt;
		mv [1].type = mv2 [1].type;
		mv [1].player = 1;
		mv [1].mode = 1;
		mv [1].r[0].x = mv2 [1].r[0].x;
		mv [1].r[1].x = mv2 [1].r[1].x;
		mv [1].r[2].x = mv2 [1].r[2].x;
		mv [1].r[3].x = mv2 [1].r[3].x;
		mv [1].r[0].y = mv2 [1].r[0].y;
		mv [1].r[1].y = mv2 [1].r[1].y;
		mv [1].r[2].y = mv2 [1].r[2].y;
		mv [1].r[3].y = mv2 [1].r[3].y;
	}
	if (initial3 == -1 && PlayMode >= 3)
	{
		mv [2].bfnt = mv2 [2].bfnt;
		mv [2].type = mv2 [2].type;
		mv [2].player = 1;
		mv [2].mode = 1;
		mv [2].r[0].x = mv2 [2].r[0].x;
		mv [2].r[1].x = mv2 [2].r[1].x;
		mv [2].r[2].x = mv2 [2].r[2].x;
		mv [2].r[3].x = mv2 [2].r[3].x;
		mv [2].r[0].y = mv2 [2].r[0].y;
		mv [2].r[1].y = mv2 [2].r[1].y;
		mv [2].r[2].y = mv2 [2].r[2].y;
		mv [2].r[3].y = mv2 [2].r[3].y;
	}

	static int i = 3;

	if (ReservedDown == 1 && ChangeBlock == 0)
	{
			mv2 [0].bfnt = mv [0].bfnt; //�V�����u���b�N�ɕς��Ȃ�
			mv2 [0].type = mv [0].type;
			mv2 [0].player = mv [0].player;
			mv2 [0].mode = mv [0].mode;
			mv2 [0].r[0].x = mv [0].r[0].x;
			mv2 [0].r[1].x = mv [0].r[1].x;
			mv2 [0].r[2].x = mv [0].r[2].x;
			mv2 [0].r[3].x = mv [0].r[3].x;
			mv2 [0].r[0].y = mv [0].r[0].y;
			mv2 [0].r[1].y = mv [0].r[1].y;
			mv2 [0].r[2].y = mv [0].r[2].y;
			mv2 [0].r[3].y = mv [0].r[3].y;

		ReservedDown = 0;
	}
	if (ReservedDown2 == 1 && ChangeBlock2 == 0 && PlayMode >= 2)
	{
			mv2 [1].bfnt = mv [1].bfnt; //�V�����u���b�N�ɕς��Ȃ�
			mv2 [1].type = mv [1].type;
			mv2 [1].player = mv [1].player;
			mv2 [1].mode = mv [1].mode;
			mv2 [1].r[0].x = mv [1].r[0].x;
			mv2 [1].r[1].x = mv [1].r[1].x;
			mv2 [1].r[2].x = mv [1].r[2].x;
			mv2 [1].r[3].x = mv [1].r[3].x;
			mv2 [1].r[0].y = mv [1].r[0].y;
			mv2 [1].r[1].y = mv [1].r[1].y;
			mv2 [1].r[2].y = mv [1].r[2].y;
			mv2 [1].r[3].y = mv [1].r[3].y;

		ReservedDown2 = 0;
	}
	if (ReservedDown3 == 1 && ChangeBlock3 == 0 && PlayMode >= 3)
	{
			mv2 [2].bfnt = mv [2].bfnt; //�V�����u���b�N�ɕς��Ȃ�
			mv2 [2].type = mv [2].type;
			mv2 [2].player = mv [2].player;
			mv2 [2].mode = mv [2].mode;
			mv2 [2].r[0].x = mv [2].r[0].x;
			mv2 [2].r[1].x = mv [2].r[1].x;
			mv2 [2].r[2].x = mv [2].r[2].x;
			mv2 [2].r[3].x = mv [2].r[3].x;
			mv2 [2].r[0].y = mv [2].r[0].y;
			mv2 [2].r[1].y = mv [2].r[1].y;
			mv2 [2].r[2].y = mv [2].r[2].y;
			mv2 [2].r[3].y = mv [2].r[3].y;

		ReservedDown3 = 0;
	}

	//��]���\�񂳂�Ă���ꍇ
	if (ReservedReturn == 1)
	{
			mv2 [0].type = (mv [0].bfnt + 1) % 4;
			mv2 [0].bfnt = mv [0].bfnt - mv [0].type + mv2 [0].type; //�V�����u���b�N�ɕς���
			switch (mv2 [0].bfnt / 4) {
			case 0:
			mv2 [0].r[0].x = BFT1 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT1 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT1 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT1 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT1 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT1 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT1 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT1 [mv2 [0].type][3][1];
			break;

			case 1:
			mv2 [0].r[0].x = BFT2 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT2 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT2 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT2 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT2 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT2 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT2 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT2 [mv2 [0].type][3][1];
			break;
			case 2:
			mv2 [0].r[0].x = BFT3 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT3 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT3 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT3 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT3 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT3 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT3 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT3 [mv2 [0].type][3][1];
			break;
			case 3:
			mv2 [0].r[0].x = BFT4 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT4 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT4 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT4 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT4 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT4 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT4 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT4 [mv2 [0].type][3][1];
			break;
			case 4:
			mv2 [0].r[0].x = BFT5 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT5 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT5 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT5 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT5 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT5 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT5 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT5 [mv2 [0].type][3][1];
			break;
			case 5:
			mv2 [0].r[0].x = BFT6 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT6 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT6 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT6 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT6 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT6 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT6 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT6 [mv2 [0].type][3][1];
			break;
			case 6:
			mv2 [0].r[0].x = BFT7 [mv2 [0].type][0][0]; mv2 [0].r[0].y = BFT7 [mv2 [0].type][0][1];
			mv2 [0].r[1].x = BFT7 [mv2 [0].type][1][0]; mv2 [0].r[1].y = BFT7 [mv2 [0].type][1][1];
			mv2 [0].r[2].x = BFT7 [mv2 [0].type][2][0]; mv2 [0].r[2].y = BFT7 [mv2 [0].type][2][1];
			mv2 [0].r[3].x = BFT7 [mv2 [0].type][3][0]; mv2 [0].r[3].y = BFT7 [mv2 [0].type][3][1];
			break;
		}

		if (player1.blist [19 + mv [0].offset.y + mv2 [0].r[0].y].t [mv2 [0].r[0].x + mv [0].offset.x]
														   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[1].y].t [mv2 [0].r[1].x + mv [0].offset.x]
														   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[2].y].t [mv2 [0].r[2].x + mv [0].offset.x]
														   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[3].y].t [mv2 [0].r[3].x + mv [0].offset.x] == 0
		 && mv2 [0].r[0].x + mv [0].offset.x >= 0 && mv2 [0].r[0].x + mv [0].offset.x <= 9
		 && mv2 [0].r[1].x + mv [0].offset.x >= 0 && mv2 [0].r[1].x + mv [0].offset.x <= 9
		 && mv2 [0].r[2].x + mv [0].offset.x >= 0 && mv2 [0].r[2].x + mv [0].offset.x <= 9
		 && mv2 [0].r[3].x + mv [0].offset.x >= 0 && mv2 [0].r[3].x + mv [0].offset.x <= 9)
		 {
		 //��]��̃u���b�N���o���\�ȏꍇ
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv2 [0].bfnt / 4];

			//��u���b�N�̂ЂȌ`
			Canvas->MoveTo (40 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 16 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->LineTo (40 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->MoveTo (40 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 16 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->LineTo (55 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 16 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (41 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 17 + 16*(mv2 [0].r[j].y + mv [0].offset.y), 54 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->FillRect (Rect (41 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 17 + 16*(mv2 [0].r[j].y + mv [0].offset.y), 54 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (54 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 17 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->LineTo (54 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y));
			Canvas->LineTo (40 + 16*(mv2 [0].r[j].x + mv [0].offset.x), 30 + 16*(mv2 [0].r[j].y + mv [0].offset.y));

			}
			ReservedReturn = 0;

			mv [0].bfnt = mv2 [0].bfnt; //�V�����u���b�N�ɕς���
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
			return;
		 }
		 else
		 {
			mv2 [0].bfnt = mv [0].bfnt; //�V�����u���b�N�ɕς��Ȃ�
			mv2 [0].type = mv [0].type;
			mv2 [0].player = mv [0].player;
			mv2 [0].mode = mv [0].mode;
			mv2 [0].r[0].x = mv [0].r[0].x;
			mv2 [0].r[1].x = mv [0].r[1].x;
			mv2 [0].r[2].x = mv [0].r[2].x;
			mv2 [0].r[3].x = mv [0].r[3].x;
			mv2 [0].r[0].y = mv [0].r[0].y;
			mv2 [0].r[1].y = mv [0].r[1].y;
			mv2 [0].r[2].y = mv [0].r[2].y;
			mv2 [0].r[3].y = mv [0].r[3].y;
			ReservedReturn = 0;
			return;
		 }
	}
	//��]�I��

	//��]���\�񂳂�Ă���ꍇ�i��l�ڂ̃u���b�N�j
	if (ReservedReturn2 == 1 && PlayMode >= 2)
	{
			mv2 [1].type = (mv [1].bfnt + 1) % 4;
			mv2 [1].bfnt = mv [1].bfnt - mv [1].type + mv2 [1].type; //�V�����u���b�N�ɕς���
			switch (mv2 [1].bfnt / 4) {
			case 0:
			mv2 [1].r[0].x = BFT1 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT1 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT1 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT1 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT1 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT1 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT1 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT1 [mv2 [1].type][3][1];
			break;

			case 1:
			mv2 [1].r[0].x = BFT2 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT2 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT2 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT2 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT2 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT2 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT2 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT2 [mv2 [1].type][3][1];
			break;
			case 2:
			mv2 [1].r[0].x = BFT3 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT3 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT3 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT3 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT3 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT3 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT3 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT3 [mv2 [1].type][3][1];
			break;
			case 3:
			mv2 [1].r[0].x = BFT4 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT4 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT4 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT4 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT4 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT4 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT4 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT4 [mv2 [1].type][3][1];
			break;
			case 4:
			mv2 [1].r[0].x = BFT5 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT5 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT5 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT5 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT5 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT5 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT5 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT5 [mv2 [1].type][3][1];
			break;
			case 5:
			mv2 [1].r[0].x = BFT6 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT6 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT6 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT6 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT6 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT6 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT6 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT6 [mv2 [1].type][3][1];
			break;
			case 6:
			mv2 [1].r[0].x = BFT7 [mv2 [1].type][0][0]; mv2 [1].r[0].y = BFT7 [mv2 [1].type][0][1];
			mv2 [1].r[1].x = BFT7 [mv2 [1].type][1][0]; mv2 [1].r[1].y = BFT7 [mv2 [1].type][1][1];
			mv2 [1].r[2].x = BFT7 [mv2 [1].type][2][0]; mv2 [1].r[2].y = BFT7 [mv2 [1].type][2][1];
			mv2 [1].r[3].x = BFT7 [mv2 [1].type][3][0]; mv2 [1].r[3].y = BFT7 [mv2 [1].type][3][1];
			break;
		}

		if (player2.blist [19 + mv [1].offset.y + mv2 [1].r[0].y].t [mv2 [1].r[0].x + mv [1].offset.x]
														   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[1].y].t [mv2 [1].r[1].x + mv [1].offset.x]
														   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[2].y].t [mv2 [1].r[2].x + mv [1].offset.x]
														   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[3].y].t [mv2 [1].r[3].x + mv [1].offset.x] == 0
		 && mv2 [1].r[0].x + mv [1].offset.x >= 0 && mv2 [1].r[0].x + mv [1].offset.x <= 9
		 && mv2 [1].r[1].x + mv [1].offset.x >= 0 && mv2 [1].r[1].x + mv [1].offset.x <= 9
		 && mv2 [1].r[2].x + mv [1].offset.x >= 0 && mv2 [1].r[2].x + mv [1].offset.x <= 9
		 && mv2 [1].r[3].x + mv [1].offset.x >= 0 && mv2 [1].r[3].x + mv [1].offset.x <= 9)
		 {
		 //��]��̃u���b�N���o���\�ȏꍇ
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
			Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv2 [1].bfnt / 4];

			//��u���b�N�̂ЂȌ`
			Canvas->MoveTo (440 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 16 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->LineTo (440 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->MoveTo (440 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 16 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->LineTo (455 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 16 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (441 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 17 + 16*(mv2 [1].r[j].y + mv [1].offset.y), 454 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->FillRect (Rect (441 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 17 + 16*(mv2 [1].r[j].y + mv [1].offset.y), 454 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (454 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 17 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->LineTo (454 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y));
			Canvas->LineTo (440 + 16*(mv2 [1].r[j].x + mv [1].offset.x), 30 + 16*(mv2 [1].r[j].y + mv [1].offset.y));

			}
			ReservedReturn2 = 0;

			mv [1].bfnt = mv2 [1].bfnt; //�V�����u���b�N�ɕς���
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
			return;
		 }
		 else
		 {
			mv2 [1].bfnt = mv [1].bfnt; //�V�����u���b�N�ɕς��Ȃ�
			mv2 [1].type = mv [1].type;
			mv2 [1].player = mv [1].player;
			mv2 [1].mode = mv [1].mode;
			mv2 [1].r[0].x = mv [1].r[0].x;
			mv2 [1].r[1].x = mv [1].r[1].x;
			mv2 [1].r[2].x = mv [1].r[2].x;
			mv2 [1].r[3].x = mv [1].r[3].x;
			mv2 [1].r[0].y = mv [1].r[0].y;
			mv2 [1].r[1].y = mv [1].r[1].y;
			mv2 [1].r[2].y = mv [1].r[2].y;
			mv2 [1].r[3].y = mv [1].r[3].y;
			ReservedReturn2 = 0;
			return;
		 }
	}
	//��]�I��

	//��]���\�񂳂�Ă���ꍇ�i�O�l�ڂ̃u���b�N�j
	if (ReservedReturn3 == 1 && PlayMode >= 3)
	{
			mv2 [2].type = (mv [2].bfnt + 1) % 4;
			mv2 [2].bfnt = mv [2].bfnt - mv [2].type + mv2 [2].type; //�V�����u���b�N�ɕς���
			switch (mv2 [2].bfnt / 4) {
			case 0:
			mv2 [2].r[0].x = BFT1 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT1 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT1 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT1 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT1 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT1 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT1 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT1 [mv2 [2].type][3][1];
			break;

			case 1:
			mv2 [2].r[0].x = BFT2 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT2 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT2 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT2 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT2 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT2 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT2 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT2 [mv2 [2].type][3][1];
			break;
			case 2:
			mv2 [2].r[0].x = BFT3 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT3 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT3 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT3 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT3 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT3 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT3 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT3 [mv2 [2].type][3][1];
			break;
			case 3:
			mv2 [2].r[0].x = BFT4 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT4 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT4 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT4 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT4 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT4 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT4 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT4 [mv2 [2].type][3][1];
			break;
			case 4:
			mv2 [2].r[0].x = BFT5 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT5 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT5 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT5 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT5 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT5 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT5 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT5 [mv2 [2].type][3][1];
			break;
			case 5:
			mv2 [2].r[0].x = BFT6 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT6 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT6 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT6 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT6 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT6 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT6 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT6 [mv2 [2].type][3][1];
			break;
			case 6:
			mv2 [2].r[0].x = BFT7 [mv2 [2].type][0][0]; mv2 [2].r[0].y = BFT7 [mv2 [2].type][0][1];
			mv2 [2].r[1].x = BFT7 [mv2 [2].type][1][0]; mv2 [2].r[1].y = BFT7 [mv2 [2].type][1][1];
			mv2 [2].r[2].x = BFT7 [mv2 [2].type][2][0]; mv2 [2].r[2].y = BFT7 [mv2 [2].type][2][1];
			mv2 [2].r[3].x = BFT7 [mv2 [2].type][3][0]; mv2 [2].r[3].y = BFT7 [mv2 [2].type][3][1];
			break;
		}

		if (player3.blist [19 + mv [2].offset.y + mv2 [2].r[0].y].t [mv2 [2].r[0].x + mv [2].offset.x]
														   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[1].y].t [mv2 [2].r[1].x + mv [2].offset.x]
														   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[2].y].t [mv2 [2].r[2].x + mv [2].offset.x]
														   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[3].y].t [mv2 [2].r[3].x + mv [2].offset.x] == 0
		 && mv2 [2].r[0].x + mv [2].offset.x >= 0 && mv2 [2].r[0].x + mv [2].offset.x <= 9
		 && mv2 [2].r[1].x + mv [2].offset.x >= 0 && mv2 [2].r[1].x + mv [2].offset.x <= 9
		 && mv2 [2].r[2].x + mv [2].offset.x >= 0 && mv2 [2].r[2].x + mv [2].offset.x <= 9
		 && mv2 [2].r[3].x + mv [2].offset.x >= 0 && mv2 [2].r[3].x + mv [2].offset.x <= 9)
		 {
		 //��]��̃u���b�N���o���\�ȏꍇ
			for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = clBtnFace;

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
			Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv2 [2].bfnt / 4];

			//��u���b�N�̂ЂȌ`
			Canvas->MoveTo (240 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 16 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->LineTo (240 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->MoveTo (240 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 16 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->LineTo (255 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 16 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->Pen->Color = clBlue;
			Canvas->Rectangle (241 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 17 + 16*(mv2 [2].r[j].y + mv [2].offset.y), 254 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->FillRect (Rect (241 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 17 + 16*(mv2 [2].r[j].y + mv [2].offset.y), 254 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y)));

			Canvas->Pen->Color = clBlack;
			Canvas->MoveTo (254 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 17 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->LineTo (254 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y));
			Canvas->LineTo (240 + 16*(mv2 [2].r[j].x + mv [2].offset.x), 30 + 16*(mv2 [2].r[j].y + mv [2].offset.y));

			}
			ReservedReturn3 = 0;

			mv [2].bfnt = mv2 [2].bfnt; //�V�����u���b�N�ɕς���
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
			return;
		 }
		 else
		 {
			mv2 [2].bfnt = mv [2].bfnt; //�V�����u���b�N�ɕς��Ȃ�
			mv2 [2].type = mv [2].type;
			mv2 [2].player = mv [2].player;
			mv2 [2].mode = mv [2].mode;
			mv2 [2].r[0].x = mv [2].r[0].x;
			mv2 [2].r[1].x = mv [2].r[1].x;
			mv2 [2].r[2].x = mv [2].r[2].x;
			mv2 [2].r[3].x = mv [2].r[3].x;
			mv2 [2].r[0].y = mv [2].r[0].y;
			mv2 [2].r[1].y = mv [2].r[1].y;
			mv2 [2].r[2].y = mv [2].r[2].y;
			mv2 [2].r[3].y = mv [2].r[3].y;
			ReservedReturn3 = 0;
			return;
		 }
	}
	//��]�I��

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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

		mv [0].offset.x += ReservedX;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv [0].bfnt / 4];

			//��u���b�N�̂ЂȌ`
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
		ReservedX = 0;
		return;
	}
	//wait = 0;

	if (ReservedX2 != 0 && PlayMode >= 2)
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
			Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

		mv [1].offset.x += ReservedX2;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv [1].bfnt / 4];

			//��u���b�N�̂ЂȌ`
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
		ReservedX2 = 0;
		return;
	}
	//wait = 0;


	if (ReservedX3 != 0 && PlayMode >= 3)
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
			Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

		mv [2].offset.x += ReservedX3;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv [2].bfnt / 4];

			//��u���b�N�̂ЂȌ`
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
		ReservedX3 = 0;
		return;
	}
	//wait = 0;



	if (wait + 1 >= MaxWait)
	{
	wait = 0;
	//�u���b�N���o���ł��邩�ǂ����e�X�g
	if ((player1.blist [19 + mv [0].offset.y + mv2 [0].r[0].y].t [mv2 [0].r[0].x + mv [0].offset.x]
												   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[1].y].t [mv2 [0].r[1].x + mv [0].offset.x]
												   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[2].y].t [mv2 [0].r[2].x + mv [0].offset.x]
												   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[3].y].t [mv2 [0].r[3].x + mv [0].offset.x] == 0
	 && mv2 [0].r[0].x + mv [0].offset.x >= 0 && mv2 [0].r[0].x + mv [0].offset.x <= 9
	 && mv2 [0].r[1].x + mv [0].offset.x >= 0 && mv2 [0].r[1].x + mv [0].offset.x <= 9
	 && mv2 [0].r[2].x + mv [0].offset.x >= 0 && mv2 [0].r[2].x + mv [0].offset.x <= 9
	 && mv2 [0].r[3].x + mv [0].offset.x >= 0 && mv2 [0].r[3].x + mv [0].offset.x <= 9) || initial == -1)
	{
	//���̃u���b�N���o���\�ȏꍇ
		if ((player1.blist [19 + mv [0].offset.y + mv2 [0].r[0].y + 1].t [mv2 [0].r[0].x + mv [0].offset.x]
														   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[1].y + 1].t [mv2 [0].r[1].x + mv [0].offset.x]
														   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[2].y + 1].t [mv2 [0].r[2].x + mv [0].offset.x]
														   + player1.blist [19 + mv [0].offset.y + mv2 [0].r[3].y + 1].t [mv2 [0].r[3].x + mv [0].offset.x] == 0
		 && mv2 [0].r[0].x + mv [0].offset.x >= 0 && mv2 [0].r[0].x + mv [0].offset.x <= 9
		 && mv2 [0].r[1].x + mv [0].offset.x >= 0 && mv2 [0].r[1].x + mv [0].offset.x <= 9
		 && mv2 [0].r[2].x + mv [0].offset.x >= 0 && mv2 [0].r[2].x + mv [0].offset.x <= 9
		 && mv2 [0].r[3].x + mv [0].offset.x >= 0 && mv2 [0].r[3].x + mv [0].offset.x <= 9) || initial == -1)

		{
		//���̃u���b�N�ŁA��i���ɗ����邱�Ƃ��\�ȏꍇ
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

			mv [0].offset.y++; //�P�����āA���̕`��̏����Ɉڂ�B
			ChangeBlock = 0;
			initial = 0;
		}
		else
		{
		//���̃u���b�N�ŁA����ɗ����邱�Ƃ��s�\�ȏꍇ�B
		//mv.bfnt = mv2.bfnt; //�V�����u���b�N�ɕς���
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



		//����ɗ����邱�Ƃ��\�ȏꍇ�B
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y));
			Canvas->FillRect (Rect (40 + 16*(mv [0].r[j].x + mv [0].offset.x), 16 + 16*(mv [0].r[j].y + mv [0].offset.y), 55 + 16*(mv [0].r[j].x + mv [0].offset.x), 31 + 16*(mv [0].r[j].y + mv [0].offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv [0].bfnt / 4];

			//��u���b�N�̂ЂȌ`
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

		//mv.offset.y--;
		player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		mv [0].offset.x = 2;
		mv [0].offset.y = 0;
		ChangeBlock = 1;
		initial = 0;
		wait = 0;

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [0] != 0) {
		for (int j = 0; j < 10; j++)
			player1.blist [38].t[j] = 0;

		std::reverse (player1.blist.begin (), player1.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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
		mv [0].bfnt = mv2 [0].bfnt; //�V�����u���b�N�ɕς���
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
	//���̃u���b�N���o���s�\�ȏꍇ
		if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y + 1].t [mv [0].r[0].x + mv [0].offset.x]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y + 1].t [mv [0].r[1].x + mv [0].offset.x]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y + 1].t [mv [0].r[2].x + mv [0].offset.x]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y + 1].t [mv [0].r[3].x + mv [0].offset.x] == 0
		 && mv [0].r[0].x + mv [0].offset.x >= 0 && mv [0].r[0].x + mv [0].offset.x <= 9
		 && mv [0].r[1].x + mv [0].offset.x >= 0 && mv [0].r[1].x + mv [0].offset.x <= 9
		 && mv [0].r[2].x + mv [0].offset.x >= 0 && mv [0].r[2].x + mv [0].offset.x <= 9
		 && mv [0].r[3].x + mv [0].offset.x >= 0 && mv [0].r[3].x + mv [0].offset.x <= 9)
		{
		//�u���b�N�����Ɏ��R�����\�ȏꍇ
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

			//��u���b�N�̂ЂȌ`
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

			//��u���b�N�̂ЂȌ`
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
		ChangeBlock = 1; //������������
		wait = 0;

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [0] != 0) {
		for (int j = 0; j < 10; j++)
			player1.blist [38].t[j] = 0;

		std::reverse (player1.blist.begin (), player1.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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

		return;
		}
		else
		{
		//�u���b�N�����Ɏ��R�����s�\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
		//�u���b�N�����Ɏ��R�����\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
		player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x] = mv [0].bfnt / 4 + 1;
		mv [0].offset.x = 2;
		mv [0].offset.y = 0;
		//ChangeBlock = 1;
		ChangeBlock = 1; //���������ɉ�����
		initial = 0;
		wait = 0;

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [0] != 0) {
		for (int j = 0; j < 10; j++)
			player1.blist [38].t[j] = 0;

		std::reverse (player1.blist.begin (), player1.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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

		return;
		}
	}
	}
	else
	{
		wait++;
	}

	//2�v���C���[�ɂ��āA���l�B
	if (wait2 + 1 >= MaxWait && PlayMode >= 2)
	{
	wait2 = 0;
	//�u���b�N���o���ł��邩�ǂ����e�X�g
	if ((player2.blist [19 + mv [1].offset.y + mv2 [1].r[0].y].t [mv2 [1].r[0].x + mv [1].offset.x]
												   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[1].y].t [mv2 [1].r[1].x + mv [1].offset.x]
												   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[2].y].t [mv2 [1].r[2].x + mv [1].offset.x]
												   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[3].y].t [mv2 [1].r[3].x + mv [1].offset.x] == 0
	 && mv2 [1].r[0].x + mv [1].offset.x >= 0 && mv2 [1].r[0].x + mv [1].offset.x <= 9
	 && mv2 [1].r[1].x + mv [1].offset.x >= 0 && mv2 [1].r[1].x + mv [1].offset.x <= 9
	 && mv2 [1].r[2].x + mv [1].offset.x >= 0 && mv2 [1].r[2].x + mv [1].offset.x <= 9
	 && mv2 [1].r[3].x + mv [1].offset.x >= 0 && mv2 [1].r[3].x + mv [1].offset.x <= 9) || initial2 == -1)
	{
	//���̃u���b�N���o���\�ȏꍇ
		if ((player2.blist [19 + mv [1].offset.y + mv2 [1].r[0].y + 1].t [mv2 [1].r[0].x + mv [1].offset.x]
														   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[1].y + 1].t [mv2 [1].r[1].x + mv [1].offset.x]
														   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[2].y + 1].t [mv2 [1].r[2].x + mv [1].offset.x]
														   + player2.blist [19 + mv [1].offset.y + mv2 [1].r[3].y + 1].t [mv2 [1].r[3].x + mv [1].offset.x] == 0
		 && mv2 [1].r[0].x + mv [1].offset.x >= 0 && mv2 [1].r[0].x + mv [1].offset.x <= 9
		 && mv2 [1].r[1].x + mv [1].offset.x >= 0 && mv2 [1].r[1].x + mv [1].offset.x <= 9
		 && mv2 [1].r[2].x + mv [1].offset.x >= 0 && mv2 [1].r[2].x + mv [1].offset.x <= 9
		 && mv2 [1].r[3].x + mv [1].offset.x >= 0 && mv2 [1].r[3].x + mv [1].offset.x <= 9) || initial2 == -1)

		{
		//���̃u���b�N�ŁA��i���ɗ����邱�Ƃ��\�ȏꍇ
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
			Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

			mv [1].offset.y++; //�P�����āA���̕`��̏����Ɉڂ�B
			ChangeBlock2 = 0;
			initial2 = 0;
		}
		else
		{
		//���̃u���b�N�ŁA����ɗ����邱�Ƃ��s�\�ȏꍇ�B
		//mv.bfnt = mv2.bfnt; //�V�����u���b�N�ɕς���
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



		//����ɗ����邱�Ƃ��\�ȏꍇ�B
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y));
			Canvas->FillRect (Rect (440 + 16*(mv [1].r[j].x + mv [1].offset.x), 16 + 16*(mv [1].r[j].y + mv [1].offset.y), 455 + 16*(mv [1].r[j].x + mv [1].offset.x), 31 + 16*(mv [1].r[j].y + mv [1].offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv [1].bfnt / 4];

			//��u���b�N�̂ЂȌ`
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

		//mv.offset.y--;
		player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
		player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
		player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
		player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x] = mv [1].bfnt / 4 + 1;
		mv [1].offset.x = 2;
		mv [1].offset.y = 0;
		ChangeBlock2 = 1;
		initial2 = 0;
		wait2 = 0;

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [1] != 0) {
		for (int j = 0; j < 10; j++)
			player2.blist [38].t[j] = 0;

		std::reverse (player2.blist.begin (), player2.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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
			//Canvas->Pen->Color = clBlack;
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19)));
			}

		}
		}


		for (int i = 0; i < 10; i++) {
			player2.blist [38].t [i] = 8;
		}
	}

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
		mv [1].bfnt = mv2 [1].bfnt; //�V�����u���b�N�ɕς���
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
	//���̃u���b�N���o���s�\�ȏꍇ
		if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y + 1].t [mv [1].r[0].x + mv [1].offset.x]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[1].y + 1].t [mv [1].r[1].x + mv [1].offset.x]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y + 1].t [mv [1].r[2].x + mv [1].offset.x]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y + 1].t [mv [1].r[3].x + mv [1].offset.x] == 0
		 && mv [0].r[0].x + mv [1].offset.x >= 0 && mv [1].r[0].x + mv [1].offset.x <= 9
		 && mv [0].r[1].x + mv [1].offset.x >= 0 && mv [1].r[1].x + mv [1].offset.x <= 9
		 && mv [0].r[2].x + mv [1].offset.x >= 0 && mv [1].r[2].x + mv [1].offset.x <= 9
		 && mv [0].r[3].x + mv [1].offset.x >= 0 && mv [1].r[3].x + mv [1].offset.x <= 9)
		{
		//�u���b�N�����Ɏ��R�����\�ȏꍇ
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

			//��u���b�N�̂ЂȌ`
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

			//��u���b�N�̂ЂȌ`
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

		//mv.offset.y--;
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

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [1] != 0) {
		for (int j = 0; j < 10; j++)
			player2.blist [38].t[j] = 0;

		std::reverse (player2.blist.begin (), player2.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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
			//Canvas->Pen->Color = clBlack;
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19)));
			}

		}
		}


		for (int i = 0; i < 10; i++) {
			player2.blist [38].t [i] = 8;
		}
	}

		return;
		}
		else
		{
		//�u���b�N�����Ɏ��R�����s�\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
		//�u���b�N�����Ɏ��R�����\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [1] != 0) {
		for (int j = 0; j < 10; j++)
			player2.blist [38].t[j] = 0;

		std::reverse (player2.blist.begin (), player2.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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
			//Canvas->Pen->Color = clBlack;
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (440 + 16*j, 16 + 16*(i-19), 455 + 16*j, 31 + 16*(i-19)));
			}

		}
		}


		for (int i = 0; i < 10; i++) {
			player2.blist [38].t [i] = 8;
		}
	}

		return;
		}
	}
	}
	else
	{
		wait2++;
	}


	//3�v���C���[�ɂ��āA���l�B
	if (wait3 + 1 >= MaxWait && PlayMode >= 3)
	{
	wait3 = 0;
	//�u���b�N���o���ł��邩�ǂ����e�X�g
	if ((player3.blist [19 + mv [2].offset.y + mv2 [2].r[0].y].t [mv2 [2].r[0].x + mv [2].offset.x]
												   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[1].y].t [mv2 [2].r[1].x + mv [2].offset.x]
												   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[2].y].t [mv2 [2].r[2].x + mv [2].offset.x]
												   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[3].y].t [mv2 [2].r[3].x + mv [2].offset.x] == 0
	 && mv2 [2].r[0].x + mv [2].offset.x >= 0 && mv2 [2].r[0].x + mv [2].offset.x <= 9
	 && mv2 [2].r[1].x + mv [2].offset.x >= 0 && mv2 [2].r[1].x + mv [2].offset.x <= 9
	 && mv2 [2].r[2].x + mv [2].offset.x >= 0 && mv2 [2].r[2].x + mv [2].offset.x <= 9
	 && mv2 [2].r[3].x + mv [2].offset.x >= 0 && mv2 [2].r[3].x + mv [2].offset.x <= 9) || initial3 == -1)
	{
	//���̃u���b�N���o���\�ȏꍇ
		if ((player3.blist [19 + mv [2].offset.y + mv2 [2].r[0].y + 1].t [mv2 [2].r[0].x + mv [2].offset.x]
														   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[1].y + 1].t [mv2 [2].r[1].x + mv [2].offset.x]
														   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[2].y + 1].t [mv2 [2].r[2].x + mv [2].offset.x]
														   + player3.blist [19 + mv [2].offset.y + mv2 [2].r[3].y + 1].t [mv2 [2].r[3].x + mv [2].offset.x] == 0
		 && mv2 [2].r[0].x + mv [2].offset.x >= 0 && mv2 [2].r[0].x + mv [2].offset.x <= 9
		 && mv2 [2].r[1].x + mv [2].offset.x >= 0 && mv2 [2].r[1].x + mv [2].offset.x <= 9
		 && mv2 [2].r[2].x + mv [2].offset.x >= 0 && mv2 [2].r[2].x + mv [2].offset.x <= 9
		 && mv2 [2].r[3].x + mv [2].offset.x >= 0 && mv2 [2].r[3].x + mv [2].offset.x <= 9) || initial3 == -1)

		{
		//���̃u���b�N�ŁA��i���ɗ����邱�Ƃ��\�ȏꍇ
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
			Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

			mv [2].offset.y++; //�P�����āA���̕`��̏����Ɉڂ�B
			ChangeBlock3 = 0;
			initial3 = 0;
		}
		else
		{
		//���̃u���b�N�ŁA����ɗ����邱�Ƃ��s�\�ȏꍇ�B
		//mv.bfnt = mv2.bfnt; //�V�����u���b�N�ɕς���
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



		//����ɗ����邱�Ƃ��\�ȏꍇ�B
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

			//��u���b�N�̂ЂȌ`
			Canvas->Pen->Color = clBtnFace;
			Canvas->Rectangle (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y));
			Canvas->FillRect (Rect (240 + 16*(mv [2].r[j].x + mv [2].offset.x), 16 + 16*(mv [2].r[j].y + mv [2].offset.y), 255 + 16*(mv [2].r[j].x + mv [2].offset.x), 31 + 16*(mv [2].r[j].y + mv [2].offset.y)));
			}

		//mv.offset.y++;

			for (int j = 0; j < 4; j++) {
			Canvas->Pen->Color = clWhite;
			Canvas->Pen->Style = psSolid;
			Canvas->Pen->Width = 1;
			Canvas->Brush->Color = colorSelect [mv [2].bfnt / 4];

			//��u���b�N�̂ЂȌ`
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

		//mv.offset.y--;
		player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
		player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
		player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
		player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x] = mv [2].bfnt / 4 + 1;
		mv [2].offset.x = 2;
		mv [2].offset.y = 0;
		ChangeBlock3 = 1;
		initial3 = 0;
		wait3 = 0;

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [2] != 0) {
		for (int j = 0; j < 10; j++)
			player3.blist [38].t[j] = 0;

		std::reverse (player3.blist.begin (), player3.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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


		for (int i = 0; i < 10; i++) {
			player3.blist [38].t [i] = 8;
		}
	}

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
		mv [2].bfnt = mv2 [2].bfnt; //�V�����u���b�N�ɕς���
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
	//���̃u���b�N���o���s�\�ȏꍇ
		if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y + 1].t [mv [2].r[0].x + mv [2].offset.x]
													   + player3.blist [19 + mv [2].offset.y + mv [2].r[1].y + 1].t [mv [2].r[1].x + mv [2].offset.x]
													   + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y + 1].t [mv [2].r[2].x + mv [2].offset.x]
													   + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y + 1].t [mv [2].r[3].x + mv [2].offset.x] == 0
		 && mv [2].r[0].x + mv [2].offset.x >= 0 && mv [2].r[0].x + mv [2].offset.x <= 9
		 && mv [2].r[1].x + mv [2].offset.x >= 0 && mv [2].r[1].x + mv [21].offset.x <= 9
		 && mv [2].r[2].x + mv [2].offset.x >= 0 && mv [2].r[2].x + mv [2].offset.x <= 9
		 && mv [2].r[3].x + mv [2].offset.x >= 0 && mv [2].r[3].x + mv [2].offset.x <= 9)
		{
		//�u���b�N�����Ɏ��R�����\�ȏꍇ
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

			//��u���b�N�̂ЂȌ`
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

			//��u���b�N�̂ЂȌ`
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

		//mv.offset.y--;
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

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [2] != 0) {
		for (int j = 0; j < 10; j++)
			player3.blist [38].t[j] = 0;

		std::reverse (player2.blist.begin (), player2.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
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

			//��u���b�N�̂ЂȌ`
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


		for (int i = 0; i < 10; i++) {
			player3.blist [38].t [i] = 8;
		}
	}

		return;
		}
		else
		{
		//�u���b�N�����Ɏ��R�����s�\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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
		//�u���b�N�����Ɏ��R�����\�ȏꍇ
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
			//��u���b�N�̂ЂȌ`
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
			//��u���b�N�̂ЂȌ`
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

	//�y�i���e�B�̍�Ƃ��n�߂�B
	if (ChargedBlocks [2] != 0) {
		for (int j = 0; j < 10; j++)
			player3.blist [38].t[j] = 0;

		std::reverse (player2.blist.begin (), player2.blist.end ());
		/*for (int i = 38, k = 0; i >= 0; i--, k = 0) {
			for (int j = 0; j < 10; j++)
				if (player1.blist [i].t [j] != 0)
					k++;
			if (k == 10) {
				player1.blist.erase (player1.blist.begin () + i);
				player1.blist.resize (39);
			}
			//player1.blist.erase (player1.blist.begin () + RememberingPosition [i], player1.blist.begin () + RememberingPosition [i]);
		}*/
		for (int i = 0; i < ChargedBlocks [2]; i++)
			player3.blist.insert (player3.blist.begin () + 1, ChargeWithHall [1]);
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

			//��u���b�N�̂ЂȌ`
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


		for (int i = 0; i < 10; i++) {
			player3.blist [38].t [i] = 8;
		}
	}

		return;
		}
	}
	}
	else
	{
		wait3++;
	}

	//���ɉ������邩�J�E���g�B
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
	Canvas->Brush->Color = colorSelect [mv [0].bfnt / 4];

	//��u���b�N�̂ЂȌ`
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

	if (PlayMode >= 2)
	{
	for (int j = 0; j < 4; j++) {
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Style = psSolid;
	Canvas->Pen->Width = 1;
	Canvas->Brush->Color = colorSelect [mv [1].bfnt / 4];

	//��u���b�N�̂ЂȌ`
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

	Canvas->Pen->Color = clBlue;
	Canvas->MoveTo (439, 15);
	Canvas->LineTo (600, 15);
	Canvas->MoveTo (600, 15);
	Canvas->LineTo (600, 320);
	Canvas->MoveTo (600, 320);
	Canvas->LineTo (439, 320);
	Canvas->MoveTo (439, 320);
	Canvas->LineTo (439, 15);
	//Canvas->Rectangle (39, 15, 200, 320);

	initial2 = 0;
	}


	if (PlayMode >= 3)
	{
	for (int j = 0; j < 4; j++) {
	Canvas->Pen->Color = clWhite;
	Canvas->Pen->Style = psSolid;
	Canvas->Pen->Width = 1;
	Canvas->Brush->Color = colorSelect [mv [2].bfnt / 4];

	//��u���b�N�̂ЂȌ`
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

	Canvas->Pen->Color = clBlue;
	Canvas->MoveTo (239, 15);
	Canvas->LineTo (400, 15);
	Canvas->MoveTo (400, 15);
	Canvas->LineTo (400, 320);
	Canvas->MoveTo (400, 320);
	Canvas->LineTo (239, 320);
	Canvas->MoveTo (239, 320);
	Canvas->LineTo (239, 15);
	//Canvas->Rectangle (39, 15, 200, 320);

	initial3 = 0;
	}
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
		//��u���b�N�̂ЂȌ`
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
		//��u���b�N�̂ЂȌ`
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
		//��u���b�N�̂ЂȌ`
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
		//��u���b�N�̂ЂȌ`
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
		//��u���b�N�̂ЂȌ`
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
		//��u���b�N�̂ЂȌ`
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
		//��u���b�N�̂ЂȌ`
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


void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TColor colorSelect [7] = {clBlue, clLime, clFuchsia, clRed, clAqua, clYellow, clGray};


}
//---------------------------------------------------------------------------


void __fastcall TForm4::FormCreate(TObject *Sender)
{
	ClientHeight = 400;
	ClientWidth = 640;

	Label1->Visible = False;

	//while (music == 0) {}
	Image1->Left = 0;
	Image1->Top = 0;
	Image1->Height = 400;
	Image1->Width = 640;

	Image1->Picture->LoadFromFile("MIRAGE.bmp");
	Image1->Visible = True;

	//Sleep (60000);

	MediaPlayer1->FileName = "IFLOGO.wav";
	MediaPlayer1->Open ();
	MediaPlayer1->Play ();

   joyinfoex.dwSize=sizeof(JOYINFOEX);
   joyinfoex.dwFlags=JOY_RETURNBUTTONS|JOY_RETURNX;
   joyinfoex2.dwSize=sizeof(JOYINFOEX);
   joyinfoex2.dwFlags=JOY_RETURNBUTTONS|JOY_RETURNX;
   joyinfoex3.dwSize=sizeof(JOYINFOEX);
   joyinfoex3.dwFlags=JOY_RETURNBUTTONS|JOY_RETURNX;
   //if(joyGetNumDevs()==0)MessageBox(Handle,"NoJoyStick","TITLE",MB_OK);
		joyGetDevCaps(JOYSTICKID1,&joycaps,sizeof(JOYCAPS));
		joyGetDevCaps(JOYSTICKID2,&joycaps2,sizeof(JOYCAPS));
		joyGetDevCaps(JOYSTICKID1+2,&joycaps3,sizeof(JOYCAPS));
   midlex=(joycaps.wXmax+joycaps.wXmin)/2;
   flexx=midlex/10;
   midley=(joycaps.wYmax+joycaps.wYmin)/2;
   flexy=midley/10;

   midlex2=(joycaps2.wXmax+joycaps2.wXmin)/2;
   flexx2=midlex2/10;
   midley2=(joycaps2.wYmax+joycaps2.wYmin)/2;
   flexy2=midley2/10;

   midlex3=(joycaps3.wXmax+joycaps3.wXmin)/2;
   flexx3=midlex3/10;
   midley3=(joycaps3.wYmax+joycaps3.wYmin)/2;
   flexy3=midley3/10;

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
		BlockTypeSeq.resize (1);
		BlockTypeSeq [0] = std::rand () % 28;
        this->Menu = NULL;

	}
	else if (MediaPlayer1->FileName == (System::UnicodeString) "XMAS.wav")
	{
		MediaPlayer1->Open ();
		MediaPlayer1->Play ();
		this->Menu = NULL;
	}
}
//---------------------------------------------------------------------------




void __fastcall TForm4::N1Click(TObject *Sender)
{
	if (MediaPlayer1->FileName == (System::UnicodeString) "XMAS.wav")
		return;
	PlayMode = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::N2Click(TObject *Sender)
{
	if (MediaPlayer1->FileName == (System::UnicodeString) "XMAS.wav")
		return;
	PlayMode = 2;
	srand ((unsigned int)time( 0 ));
	TetrisHall [0] = std::rand () % 10;
	TetrisHall [1] = std::rand () % 10;
	for (int i = 0; i < 10; i++)
	{
		ChargeWithHall [0].bfnt [i] = 7;
		ChargeWithHall [0].t [i] = 7;
	}
	ChargeWithHall [0].bfnt [TetrisHall [0]] = 0;
	ChargeWithHall [0].t [TetrisHall [0]] = 0;
	for (int i = 0; i < 10; i++)
	{
		ChargeWithHall [1].bfnt [i] = 7;
		ChargeWithHall [1].t [i] = 7;
	}
	ChargeWithHall [1].bfnt [TetrisHall [1]] = 0;
	ChargeWithHall [1].t [TetrisHall [1]] = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::N3Click(TObject *Sender)
{
	if (MediaPlayer1->FileName == (System::UnicodeString) "XMAS.wav")
		return;
	PlayMode = 3;
	srand ((unsigned int)time( 0 ));
	TetrisHall [0] = std::rand () % 10;
	TetrisHall [1] = std::rand () % 10;
	TetrisHall [2] = std::rand () % 10;
	for (int i = 0; i < 10; i++)
	{
		ChargeWithHall [0].bfnt [i] = 7;
		ChargeWithHall [0].t [i] = 7;
	}
	ChargeWithHall [0].bfnt [TetrisHall [0]] = 0;
	ChargeWithHall [0].t [TetrisHall [0]] = 0;
	for (int i = 0; i < 10; i++)
	{
		ChargeWithHall [1].bfnt [i] = 7;
		ChargeWithHall [1].t [i] = 7;
	}
	ChargeWithHall [1].bfnt [TetrisHall [1]] = 0;
	ChargeWithHall [1].t [TetrisHall [1]] = 0;
	for (int i = 0; i < 10; i++)
	{
		ChargeWithHall [2].bfnt [i] = 7;
		ChargeWithHall [2].t [i] = 7;
	}
	ChargeWithHall [2].bfnt [TetrisHall [2]] = 0;
	ChargeWithHall [2].t [TetrisHall [2]] = 0;
}
//---------------------------------------------------------------------------

