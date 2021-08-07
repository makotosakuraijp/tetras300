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
	joyinfoex.dwFlags=JOY_RETURNALL;
	joyinfoex2.dwSize=sizeof(JOYINFOEX);
	joyinfoex2.dwFlags=JOY_RETURNALL;
	joyinfoex3.dwSize=sizeof(JOYINFOEX);
	joyinfoex3.dwFlags=JOY_RETURNALL;
	if (joyGetDevCaps(JOYSTICKID1,&joycaps,sizeof(JOYCAPS)) == JOYERR_NOERROR)
	{
		if (joyGetDevCaps(JOYSTICKID2,&joycaps2,sizeof(JOYCAPS)) == JOYERR_NOERROR)
		{
			if (joyGetDevCaps(JOYSTICKID1+2,&joycaps3,sizeof(JOYCAPS)) == JOYERR_NOERROR)
				controllers = 3;
			else
				controllers = 2;
		}
		else
			controllers = 1;
	}

   midlex=(joycaps.wXmax+joycaps.wXmin)/2.0;
   flexx=midlex/10.0+1;
   midley=(joycaps.wYmax+joycaps.wYmin)/2.0;
   flexy=(joycaps.wYmax-joycaps.wYmin)/10.0;
   //fprintf (output, "flexx: %d, midlex: %d, flexy: %d, midley: %d", flexx, midlex, flexy, midley);

   midlex2=(joycaps2.wXmax+joycaps2.wXmin)/2.0;
   flexx2=midlex2/10.0+1;
   midley2=(joycaps2.wYmax+joycaps2.wYmin)/2.0;
   flexy2=(joycaps2.wYmax-joycaps2.wYmin)/10.0;

   midlex3=(joycaps3.wXmax+joycaps3.wXmin)/2.0;
   flexx3=midlex3/10.0+1;
   midley3=(joycaps3.wYmax+joycaps3.wYmin)/2.0;
   flexy3=(joycaps3.wYmax-joycaps3.wYmin)/10.0;

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

void joystick1 (void)
{
	joyGetPosEx(JOYSTICKID1,&joyinfoex);
	if(joyinfoex.dwXpos > midlex + flexx)
	{
		if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
													   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
		&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
		{
			//ブロックが右に移動可能な場合

			ReservedX = 1;
		}
		//Label1->Caption ="RIGHT"; //midle=32K
	}
	if(joyinfoex.dwXpos < midlex - flexx)
	{
		if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
		+ player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
		+ player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
		+ player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
		&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
		{
		//ブロックが左に移動可能な場合

		ReservedX = -1;
		}
		//Label1->Caption ="LEFT";
	}
	if(joyinfoex.dwYpos > midley + flexy && ReservedX == 0)
	{
		ReservedDown = 1;
		//Label1->Caption ="DOWN";
	}
	if(joyinfoex.dwButtons==JOY_BUTTON1)
	{
		ReservedX = 0;
		ReservedReturn = 1;
		//Label1->Caption ="BUTTON"; //buttonA
	}

}

void joystick2 (void)
{
	joyGetPosEx(JOYSTICKID2,&joyinfoex2);
	if(joyinfoex2.dwXpos > midlex2 + flexx2)
	{
		if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x + 1]
		+ player1.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x + 1]
		+ player1.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x + 1]
		+ player1.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x + 1] == 0
		&& (mv [1].r[0].x + mv [1].offset.x) < 9 && (mv [1].r[1].x + mv [1].offset.x) < 9 && (mv [1].r[2].x + mv [1].offset.x) < 9 && (mv [1].r[3].x + mv [1].offset.x) < 9)
		{
			//ブロックが右に移動可能な場合

			ReservedX2 = 1;
		}
	//Label1->Caption ="RIGHT2"; //midle=32K
	}
	if(joyinfoex2.dwXpos < midlex2 - flexx2)
	{
		if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x - 1]
		+ player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x - 1]
		+ player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x - 1]
		+ player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x - 1] == 0
		&& (mv [1].r[0].x + mv [1].offset.x) > 0 && (mv [1].r[1].x + mv [1].offset.x) > 0 && (mv [1].r[2].x + mv [1].offset.x) > 0 && (mv [1].r[3].x + mv [1].offset.x) > 0)
		{
		//ブロックが左に移動可能な場合

		ReservedX2 = -1;
		}
		//Label1->Caption ="LEFT2";
	}
	if(joyinfoex2.dwYpos > midley2 + flexy2 && ReservedX2 == 0)
	{
		ReservedDown2 = 1;
		//Label1->Caption ="DOWN2";
	}
	if(joyinfoex2.dwButtons==JOY_BUTTON1)
	{
		ReservedX2 = 0;
		ReservedReturn2 = 1;
		//Label1->Caption ="BUTTON2"; //buttonA
	}
}

void joystick3 ()
{
	joyGetPosEx(JOYSTICKID1+2,&joyinfoex3);
	if(joyinfoex3.dwXpos > midlex3 + flexx3)
	{
		if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x + 1]
		 + player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x + 1]
		 + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x + 1]
		 + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x + 1] == 0
		&& (mv [2].r[0].x + mv [2].offset.x) < 9 && (mv [2].r[1].x + mv [2].offset.x) < 9 && (mv [2].r[2].x + mv [2].offset.x) < 9 && (mv [2].r[3].x + mv [2].offset.x) < 9)
		{
			//ブロックが右に移動可能な場合
			ReservedX3 = 1;
		}
		//Label1->Caption ="RIGHT3"; //midle=32K
	}
	if(joyinfoex3.dwXpos < midlex3 - flexx3)
	{
		if (player1.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x - 1]
		+ player1.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x - 1]
		+ player1.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x - 1]
		+ player1.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x - 1] == 0
		&& (mv [2].r[0].x + mv [2].offset.x) > 0 && (mv [2].r[1].x + mv [2].offset.x) > 0 && (mv [2].r[2].x + mv [2].offset.x) > 0 && (mv [2].r[3].x + mv [2].offset.x) > 0)
		{
			//ブロックが左に移動可能な場合

			ReservedX3 = -1;
		}
		//Label1->Caption ="LEFT3";
	}
	if(joyinfoex3.dwYpos > midley3 + flexy3 && ReservedX3 == 0)
	{
		ReservedDown3 = 1;
		//Label1->Caption ="DOWN3";
	}
	if(joyinfoex3.dwButtons==JOY_BUTTON1)
	{
		ReservedX3 = 0;
		ReservedReturn3 = 1;
		//Label1->Caption ="BUTTON3"; //buttonA
	}
}

void KeyboardInputSwitch (void)
{
	switch (PlayMode) {
	case 1:
		if (KeyTbl [65] || KeyTbl [76] || KeyTbl [VK_LEFT] || KeyTbl [VK_NUMPAD4])
		{
			//Label1->Caption = "Left";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
				ReservedX = -1;
		}

		//右キー
		//	case vkD:
		//	case 186: //コロン
		//	case vkRight:
		//	case vkNumpad6:
		if (KeyTbl [68] || KeyTbl [186] || KeyTbl [VK_RIGHT] || KeyTbl [VK_NUMPAD6])
		{
			//Label1->Caption = "Right";
			//Label1->Caption = ShortCutToText(ShortCut(Word(':'), Shift));

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
				ReservedX = 1;
		}

		//回転キー
		//	case vkS:
		//	case 187: //セミコロン
		//	case vkReturn:
		//	case vkNumpad5:
		if (KeyTbl [83] || KeyTbl [187] || KeyTbl [VK_RETURN] || KeyTbl [VK_NUMPAD5])
		{

			//Label1->Caption = "Return";
			if (ReservedX == 0)
				ReservedReturn = 1;
		}

		//case vkX:
		//case vkSlash:
		//case vkDown:
		//case vkNumpad2:
		if (KeyTbl [88] || KeyTbl [VK_OEM_2] || KeyTbl [VK_DOWN] || KeyTbl [VK_NUMPAD2])
		{
			//Label1->Caption = "Down";
			if (ReservedX == 0)
				ReservedDown = 1;
			//break;
		}
		break;

	case 2:
		if (KeyTbl [65] || KeyTbl [76])
		{
			//Label1->Caption = "Left1";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
				ReservedX = -1;
		}

		if (KeyTbl [VK_LEFT] || KeyTbl [VK_NUMPAD4])
		{
			//Label1->Caption = "Left2";

			if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x - 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x - 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x - 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x - 1] == 0
				&& (mv [1].r[0].x + mv [1].offset.x) > 0 && (mv [1].r[1].x + mv [1].offset.x) > 0 && (mv [1].r[2].x + mv [1].offset.x) > 0 && (mv [1].r[3].x + mv [1].offset.x) > 0)
					ReservedX2 = -1;
		}

		//右キー
		if (KeyTbl [68] || KeyTbl [186])
		{
			//Label1->Caption = "Right1";
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
			//Label1->Caption = "Right2";
			//Label1->Caption = ShortCutToText(ShortCut(Word(':'), Shift));

				if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x + 1]
															   + player2.blist [19 + mv [1].offset.y + mv[1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x + 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x + 1]
															   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x + 1] == 0
				&& (mv [1].r[0].x + mv [1].offset.x) < 9 && (mv [1].r[1].x + mv [1].offset.x) < 9 && (mv [1].r[2].x + mv [1].offset.x) < 9 && (mv [1].r[3].x + mv [1].offset.x) < 9)
					ReservedX2 = 1;
		}

		//回転キー
		if (KeyTbl [83] || KeyTbl [187])
		{
			//Label1->Caption = "Return1";
			if (ReservedX == 0)
				ReservedReturn = 1;
		}

		if (KeyTbl [VK_RETURN] || KeyTbl [VK_NUMPAD5])
		{
			//Label1->Caption = "Return2";
			if (ReservedX2 == 0)
				ReservedReturn2 = 1;
		}

		if (KeyTbl [88] || KeyTbl [VK_OEM_2])
		{
			//Label1->Caption = "Down1";
			if (ReservedX == 0)
				ReservedDown = 1;
		}


		if (KeyTbl [VK_DOWN] || KeyTbl [VK_NUMPAD2])
		{
			//Label1->Caption = "Down2";
			if (ReservedX2 == 0)
				ReservedDown2 = 1;
		}
		break;

	case 3:
		//左キー
		case vkA:
		if (KeyTbl [65])
		{
			//Label1->Caption = "Left1";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x - 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x - 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) > 0 && (mv [0].r[1].x + mv [0].offset.x) > 0 && (mv [0].r[2].x + mv [0].offset.x) > 0 && (mv [0].r[3].x + mv [0].offset.x) > 0)
				ReservedX = -1;
		}

		if (KeyTbl [65] || KeyTbl [76] || KeyTbl [VK_LEFT] || KeyTbl [VK_NUMPAD4])
		{
			//Label1->Caption = "Left2";

			if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x - 1]
													   + player2.blist [19 + mv [1].offset.y + mv [1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x - 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x - 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x - 1] == 0
			&& (mv [1].r[0].x + mv [1].offset.x) > 0 && (mv [1].r[1].x + mv [1].offset.x) > 0 && (mv [1].r[2].x + mv [1].offset.x) > 0 && (mv [1].r[3].x + mv [1].offset.x) > 0)
				ReservedX2 = -1;
		}

		//左キー
		if (KeyTbl [76])
		{
			case vkL:
			//Label1->Caption = "Left3";

			if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x - 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x - 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x - 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x - 1] == 0
			&& (mv [2].r[0].x + mv [2].offset.x) > 0 && (mv [2].r[1].x + mv [2].offset.x) > 0 && (mv [2].r[2].x + mv [2].offset.x) > 0 && (mv [2].r[3].x + mv [2].offset.x) > 0)
				ReservedX3 = -1;
		}

		//右キー
		if (KeyTbl [68])
		{
			//Label1->Caption = "Right1";

			if (player1.blist [19 + mv [0].offset.y + mv [0].r[0].y].t [mv [0].r[0].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[1].y].t [mv [0].r[1].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[2].y].t [mv [0].r[2].x + mv [0].offset.x + 1]
														   + player1.blist [19 + mv [0].offset.y + mv [0].r[3].y].t [mv [0].r[3].x + mv [0].offset.x + 1] == 0
			&& (mv [0].r[0].x + mv [0].offset.x) < 9 && (mv [0].r[1].x + mv [0].offset.x) < 9 && (mv [0].r[2].x + mv [0].offset.x) < 9 && (mv [0].r[3].x + mv [0].offset.x) < 9)
				ReservedX = 1;
		}

		if (KeyTbl [VK_RIGHT] || KeyTbl [VK_NUMPAD6])
		{
			//Label1->Caption = "Right2";

			if (player2.blist [19 + mv [1].offset.y + mv [1].r[0].y].t [mv [1].r[0].x + mv [1].offset.x + 1]
														   + player2.blist [19 + mv [1].offset.y + mv[1].r[1].y].t [mv [1].r[1].x + mv [1].offset.x + 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[2].y].t [mv [1].r[2].x + mv [1].offset.x + 1]
														   + player2.blist [19 + mv [1].offset.y + mv [1].r[3].y].t [mv [1].r[3].x + mv [1].offset.x + 1] == 0
			&& (mv [1].r[0].x + mv [1].offset.x) < 9 && (mv [1].r[1].x + mv [1].offset.x) < 9 && (mv [1].r[2].x + mv [1].offset.x) < 9 && (mv [1].r[3].x + mv [1].offset.x) < 9)
				ReservedX2 = 1;
		}

		if (KeyTbl [186])
		{
			//Label1->Caption = "Right3";

			if (player3.blist [19 + mv [2].offset.y + mv [2].r[0].y].t [mv [2].r[0].x + mv [2].offset.x + 1]
														   + player3.blist [19 + mv [2].offset.y + mv[2].r[1].y].t [mv [2].r[1].x + mv [2].offset.x + 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[2].y].t [mv [2].r[2].x + mv [2].offset.x + 1]
														   + player3.blist [19 + mv [2].offset.y + mv [2].r[3].y].t [mv [2].r[3].x + mv [2].offset.x + 1] == 0
			&& (mv [2].r[0].x + mv [2].offset.x) < 9 && (mv [2].r[1].x + mv [2].offset.x) < 9 && (mv [2].r[2].x + mv [2].offset.x) < 9 && (mv [2].r[3].x + mv [2].offset.x) < 9)
				ReservedX3 = 1;
		}

		//回転キー
		if (KeyTbl [83])
		{
			//Label1->Caption = "Return1";
			if (ReservedX == 0)
				ReservedReturn = 1;
		}

		if (KeyTbl [VK_RETURN] || KeyTbl [VK_NUMPAD5])
		{
			//Label1->Caption = "Return2";
			if (ReservedX2 == 0)
				ReservedReturn2 = 1;
		}

		if (KeyTbl [187])
		{
			//Label1->Caption = "Return3";
			if (ReservedX3 == 0)
				ReservedReturn3 = 1;
		}

		if (KeyTbl [88])
		{
			//Label1->Caption = "Down1";
			if (ReservedX == 0)
				ReservedDown = 1;
		}


		if (KeyTbl [VK_DOWN] || KeyTbl [VK_NUMPAD2])
		{
			//Label1->Caption = "Down2";
			if (ReservedX2 == 0)
				ReservedDown2 = 1;
		}

		if (KeyTbl [VK_OEM_2])
		{
			//Label1->Caption = "Down3";
			if (ReservedX3 == 0)
				ReservedDown3 = 1;
		}
		break;

		default:
		break;
	}
}

void Player1Elimination (int &totalK, std::vector<int> &RememberingPosition)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;
	//ブロック消去を始める
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
			Canvas->Brush->Color = clBtnFace;
			Canvas->Rectangle (40 + 16*j, 16 + 16*(i-19), 55 + 16*j, 31 + 16*(i-19));
			Canvas->FillRect (Rect (40 + 16*j, 16 + 16*(i-19), 55 + 16*j, 31 + 16*(i-19)));
		}
	}
	}

	for (int i = 0; i < 10; i++)
		player1.blist [38].t [i] = 8;
}

void Player2Elimination (int &totalK, std::vector<int> &RememberingPosition)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;
	//ブロック消去を始める
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

		//一ブロックのひな形
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

	//一ブロックのひな形
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

void Player3Elimination (int &totalK, std::vector<int> &RememberingPosition)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;
	//ブロック消去を始める

	ChargedBlocks [0] += Charge3 [totalK - 1];
	ChargedBlocks [1] += Charge3 [totalK - 1];

	for (int k = 0; k < 10; k++) {
	for (int i = 0; i < totalK; i++) {
	for (int j = 0; j < 10; j++) {
		Canvas->Pen->Color = clWhite;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		Canvas->Brush->Color = colorSelect [player3.blist [RememberingPosition [i]].t[j] - 1];

		//一ブロックのひな形
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

		//一ブロックのひな形
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
				Canvas->Brush->Color = clBtnFace;
				Canvas->Rectangle (240 + 16*j, 16 + 16*(i-19), 255 + 16*j, 31 + 16*(i-19));
				Canvas->FillRect (Rect (240 + 16*j, 16 + 16*(i-19), 255 + 16*j, 31 + 16*(i-19)));
			}
		}
	}


	for (int i = 0; i < 10; i++)
		player3.blist [38].t [i] = 8;
}


void Player1Newblock (void)
{
	if (blockNumber >= BlockTypeSeq.size())
	{
		mv2 [0].bfnt = std::rand () % 28; //新しいブロックに変える
		BlockTypeSeq.resize (blockNumber + 1);
		BlockTypeSeq [blockNumber] = mv2 [0].bfnt;
		blockNumber++;
	}
	else
	{
		mv2 [0].bfnt = BlockTypeSeq [blockNumber]; //新しいブロックに変える
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
}

void Player2Newblock (void)
{
	if (blockNumber2 >= BlockTypeSeq.size())
	{
		mv2 [1].bfnt = std::rand () % 28; //新しいブロックに変える
		BlockTypeSeq.resize (blockNumber2 + 1);
		BlockTypeSeq [blockNumber2] = mv2 [1].bfnt;
		blockNumber2++;
	}
	else
	{
		mv2 [1].bfnt = BlockTypeSeq [blockNumber2]; //新しいブロックに変える
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
}

void Player3Newblock (void)
{
	if (blockNumber3 >= BlockTypeSeq.size())
	{
		mv2 [2].bfnt = std::rand () % 28; //新しいブロックに変える
		BlockTypeSeq.resize (blockNumber3 + 1);
		BlockTypeSeq [blockNumber3] = mv2 [2].bfnt;
		blockNumber3++;
	}
	else
	{
		mv2 [2].bfnt = BlockTypeSeq [blockNumber3]; //新しいブロックに変える
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
}

void Player1Reinitialize (void)
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
void Player2Reinitialize (void)
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
void Player3Reinitialize (void)
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

void Player1DoNotChangeBlock (void)
{
	mv2 [0].bfnt = mv [0].bfnt; //新しいブロックに変えない
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

void Player2DoNotChangeBlock (void)
{
	mv2 [1].bfnt = mv [1].bfnt; //新しいブロックに変えない
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

void Player3DoNotChangeBlock (void)
{
	mv2 [2].bfnt = mv [2].bfnt; //新しいブロックに変えない
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

int Player1Rotate (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	mv2 [0].type = (mv [0].bfnt + 1) % 4;
	mv2 [0].bfnt = mv [0].bfnt - mv [0].type + mv2 [0].type; //新しいブロックに変える
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
	//回転後のブロックが出現可能な場合
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
		Canvas->Brush->Color = colorSelect [mv2 [0].bfnt / 4];

		//一ブロックのひな形
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
	return -1;
	}
	else
	{
		mv2 [0].bfnt = mv [0].bfnt; //新しいブロックに変えない
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
		return -1;
	}
	return 1;
}

int Player2Rotate (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	mv2 [1].type = (mv [1].bfnt + 1) % 4;
	mv2 [1].bfnt = mv [1].bfnt - mv [1].type + mv2 [1].type; //新しいブロックに変える
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
		//回転後のブロックが出現可能な場合
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
			Canvas->Brush->Color = colorSelect [mv2 [1].bfnt / 4];

			//一ブロックのひな形
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
		return -1;
	 }
	 else
	 {
		mv2 [1].bfnt = mv [1].bfnt; //新しいブロックに変えない
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
		return -1;
	 }
	 return 1;

}

int Player3Rotate (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

	mv2 [2].type = (mv [2].bfnt + 1) % 4;
	mv2 [2].bfnt = mv [2].bfnt - mv [2].type + mv2 [2].type; //新しいブロックに変える
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
		 //回転後のブロックが出現可能な場合
		for (int j = 0; j < 4; j++) {
			//Canvas->Pen->Color = clWhite;
			//Canvas->Pen->Style = psSolid;
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
			Canvas->Brush->Color = colorSelect [mv2 [2].bfnt / 4];

			//一ブロックのひな形
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
		return -1;
	 }
	 else
	 {
		mv2 [2].bfnt = mv [2].bfnt; //新しいブロックに変えない
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
		return -1;
	 }
	 return 1;
}

void Player1Slide (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

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

	mv [0].offset.x += ReservedX;

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
}

void Player2Slide (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

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

	mv [1].offset.x += ReservedX2;

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
}

void Player3Slide (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

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

	mv [2].offset.x += ReservedX3;

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
}

void LeftRepaint (void)
{
	Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

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

void RightRepaint (void)
{
		Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

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

void CenterRepaint (void)
{
		Vcl::Graphics::TCanvas *Canvas = Form4->Canvas;

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
//---------------------------------------------------------------------------
