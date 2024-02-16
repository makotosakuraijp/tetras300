object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Form4'
  ClientHeight = 400
  ClientWidth = 640
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  Visible = True
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  TextHeight = 13
  object Label1: TLabel
    Left = 346
    Top = 379
    Width = 31
    Height = 13
    Caption = 'Label1'
    Visible = False
  end
  object Image1: TImage
    Left = 272
    Top = 176
    Width = 105
    Height = 105
  end
  object MediaPlayer1: TMediaPlayer
    Left = 200
    Top = 192
    Width = 253
    Height = 30
    DoubleBuffered = True
    Visible = False
    ParentDoubleBuffered = False
    TabOrder = 0
    OnNotify = MediaPlayer1Notify
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 384
    Top = 16
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 56
    Top = 16
    object tai1: TMenuItem
      Caption = #23550#25126#12514#12540#12489
      object N1: TMenuItem
        Caption = #19968#20154#12503#12524#12540
        OnClick = N1Click
      end
      object N2: TMenuItem
        Caption = #20108#20154#12391#23550#25126
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #19977#20154#12391#23550#25126
        OnClick = N3Click
      end
    end
  end
end
