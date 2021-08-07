//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.MPlayer.hpp>
#include <Vcl.Menus.hpp>
#include <deque>
#include <vector>
#include <hidsdi.h>
#include <windows.h> //���ꂪ�����ƁAmmsystem�֘A�̃G���[���ł�
#include <mmsystem.h>
#include <winuser.h> //�L�[�R�[�h�ꗗ
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TTimer *Timer1;
	TLabel *Label1;
	TMediaPlayer *MediaPlayer1;
	TImage *Image1;
	TMainMenu *MainMenu1;
	TMenuItem *tai1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MediaPlayer1Notify(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
	__fastcall TForm4(TComponent* Owner);
};

// �����̃f�[�^
class Block
{
	public:
	int                     t [10]; //�u���b�N�̑����B�ԕ��͍��Ȃ�
	int                     bfnt [10]; //�F����
	int                     all (void);
							Block (void)
	{
		for (int i = 0; i < 10; i++) {
			t [i] = 0;
			bfnt [i] = 0;
		}
	};
	void                    operator =(int a);
};


//�v���C��ʑS�̂̃u���b�N38��
class BlockList
{
public:
	//Block                   blist [39]; //�����Ă��镔���P�X�{�\���P�X�{�P
	std::deque<Block> blist;
	BlockList (void)
	{
		blist.resize (39);
	};
};

class XY
{
public:
	int                     x;
	int                     y;
							XY (void)
	{
		x = 2;
		y = 0;
	};
							XY (int a, int b)
	{
		x = a;
		y = b;
	};
	void                    operator =(XY a);
};

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
//	int                     turn_enable (BLOCK_LIST);
//	void                    turn (int errlv);
//	int                     move_enable (BLOCK_LIST a, XY b);
//	void                    move (XY a, int errlv);
};


void joystick1 (void);
void joystick2 (void);
void joystick3 (void);

void KeyboardInputSwitch (void);

void Player1Elimination (int &totalK, std::vector<int> &RememberingPosition);
void Player2Elimination (int &totalK, std::vector<int> &RememberingPosition);
void Player3Elimination (int &totalK, std::vector<int> &RememberingPosition);

void Player1Newblock (void);
void Player2Newblock (void);
void Player3Newblock (void);

void Player1Reinitialize (void);
void Player2Reinitialize (void);
void Player3Reinitialize (void);

void Player1DoNotChangeBlock (void);
void Player2DoNotChangeBlock (void);
void Player3DoNotChangeBlock (void);

int Player1Rotate (void);
int Player2Rotate (void);
int Player3Rotate (void);

void Player1Slide (void);
void Player2Slide (void);
void Player3Slide (void);

int Player1MoreThanMaxWait (void);
int Player2MoreThanMaxWait (void);
int Player3MoreThanMaxWait (void);

void LeftRepaint ();
void RightRepaint ();
void CenterRepaint ();

void Player1Penalty (void);
void Player2Penalty (void);
void Player3Penalty (void);

//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
