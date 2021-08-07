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
#include <windows.h> //これが無いと、mmsystem関連のエラーがでる
#include <mmsystem.h>
#include <winuser.h> //キーコード一覧
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE で管理されるコンポーネント
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
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TForm4(TComponent* Owner);
};

// 横一列のデータ
class Block
{
	public:
	int                     t [10]; //ブロックの属性。番兵は作らない
	int                     bfnt [10]; //色や種類
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


//プレイ画面全体のブロック38列
class BlockList
{
public:
	//Block                   blist [39]; //見えている部分１９＋予備１９＋１
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
