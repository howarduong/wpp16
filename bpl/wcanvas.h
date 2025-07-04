//---------------------------------------------------------------------------

#ifndef WCanvasH
#define WCanvasH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "windsoul.h"
#include "wscanvas.h"
typedef void __fastcall (__closure *TKeyboardEvent)(System::TObject* Sender, int &Key);

//---------------------------------------------------------------------------
class PACKAGE TWCanvas : public TCustomControl
{
private:
   TMouseMoveEvent FOnMouseMove;
//   TMouseMoveEvent FOnMouseExit;
//   TMouseMoveEvent FOnMouseEnter;
//   TMouseEvent FOnClick;
   TMouseEvent FOnDblClick;
   TMouseEvent FOnMouseDown;
   TMouseEvent FOnMouseUp;
   TKeyboardEvent FOnKeyUp;
   TKeyboardEvent FOnKeyDown;

    TShiftState ShiftState(int WParam);
    TPoint MousePoint(DWORD LParam);
protected:
    WCanvas *canvas;

    void __fastcall DoMessage(TMessage &Message);
//    virtual void __fastcall DoMouseMove(TShiftState Shift, int X, int Y);
//    void __fastcall AfterConstruction();
    void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
    void __fastcall Paint(void);
	void __fastcall NextFrame() {canvas->NextFrame();}		// ׼����һ֡
public:
    __fastcall TWCanvas(TComponent* Owner);
    __fastcall ~TWCanvas();
    bool __fastcall IsValid() const { return (canvas!=0); } // �Ƿ���Բ��� canvas
	void __fastcall SkipFrame() {canvas->SkipFrame();}		// ������һ֡
//	void reset(int f);		// ʱ�Ӹ�λ
	void __fastcall MoveTo(int x,int y) {canvas->MoveTo(x,y);}	// �ƶ��� p
	void __fastcall Move(int x,int y) {canvas->Move(x,y);}	// �ƶ� (x,y)
	int __fastcall GetX() const { return canvas->GetX();}		// ��ȡ�������� X
	int __fastcall GetY() const { return canvas->GetY();}		// ��ȡ�������� Y
	int __fastcall GetW() const { return canvas->GetW();}		// ��� Canvas �Ŀ��ӿ��
	int __fastcall GetH() const { return canvas->GetH();}		// ��� Canvas �Ŀ��Ӹ߶�
	WPoint __fastcall GetViewPort(int x,int y) const { return canvas->GetViewPort(x,y);}	// ��ȡ�ӿ�����ö�Ӧ��������
	void __fastcall Clear(WPixel color) { canvas->Clear(color);}// ��� Canvas
	WSERR __fastcall Draw(const WObject &bmp, DWORD style) { return canvas->Draw(bmp,style); }		// ��һ��ͼ
	WSERR __fastcall DrawEx(const WObject &bmp, DWORD style) { return canvas->DrawEx(bmp,style); }		// ��һ��ͼ
	void __fastcall Draw(WCanvas &c) { canvas->Draw(c); }	   	// ������һ������
	void __fastcall SetOvlRect(int w,int h) { canvas->SetOvlRect(w,h); }// ��Ӹ��Ǿ���
	void __fastcall SetOvlRect(const WRect &rect) { canvas->operator()(rect.x,rect.y); canvas->SetOvlRect(rect.w,rect.h); }
	WCanvas* __fastcall Pos(int x,int y) {canvas->operator()(x,y); return canvas; }	// ���ùؼ���
	WCanvas* __fastcall ViewPort(int x,int y) { canvas->ViewPort(x,y); return canvas; }	// �����ӿڹؼ���
	WCanvas* __fastcall UnChange() { canvas->UnChange(); return canvas; }	// ���û���״̬Ϊ�����֡�����
	WCanvas* __fastcall Change() { canvas->Change(); return canvas; }	// ���û���״̬Ϊ�����֡���
	WCanvas* __fastcall SelfChange() { canvas->SelfChange(); return canvas; }//  ���û���״̬Ϊ�����֡������
	bool __fastcall IsMove() const { return canvas->IsMove(); }	// �Ƿ��ƶ�
	void __fastcall Update() { canvas->Blit2DC(Canvas->Handle,0,0); }   	// ���Ƶ� DC
__published:
    __property TAlign Align = {read=FAlign, write=SetAlign, default=0};
   // Events
//    __property TMouseEvent OnClick = {read=FOnClick,write=FOnClick};
    __property TMouseEvent OnDblClick = {read=FOnDblClick,write=FOnDblClick};
//    __property TMouseMoveEvent OnMouseEnter = {read=FOnMouseEnter,write=FOnMouseEnter};
//    __property TMouseMoveEvent OnMouseExit = {read=FOnMouseExit,write=FOnMouseExit};
    __property TMouseMoveEvent OnMouseMove = {read=FOnMouseMove,write=FOnMouseMove};
    __property TMouseEvent OnMouseUp = {read=FOnMouseUp,write=FOnMouseUp};
    __property TMouseEvent OnMouseDown = {read=FOnMouseDown,write=FOnMouseDown};
    __property TKeyboardEvent OnKeyUp = {read=FOnKeyUp, write=FOnKeyUp};
    __property TKeyboardEvent OnKeyDown = {read=FOnKeyDown, write=FOnKeyDown};
    __property TCursor Cursor = {read=FCursor, write=SetCursor, default=0};
};
//---------------------------------------------------------------------------
#endif
