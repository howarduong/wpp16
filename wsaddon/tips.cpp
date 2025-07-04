/*
 "               ..;;;;,                     ;;;,    
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
       ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
      .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
     ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
     ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
    :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
 
                        Windsoul++

                by �Ʒ� (Cloud Wu)  1999-2001
 
		http://www.codingnow.com 
		mailto:cloudwu@263.net
 
		���Ķ� readme.txt �еİ�Ȩ��Ϣ
		See readme.txt for copyright information.

		Description:		Tips ��
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/11/13
		Modify Time:
		Comment:			�������ʾ�������չ���Ļ�ͼ����,
							WTips �� ���� WLine, һ�� WBox ��һЩ WChar
							�ϲ���һ��, ����һ������, ��������.
							Ч���� WIndows �ĺڿ�ǳ��ɫ�� Tips ��һ��.

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>

#include "windsoul.h"
#include "wstips.h"
#include "wsfont.h"
#include "wsgeo.h"

struct WTipsStruct : public WObjStruct, memory<WTipsStruct> {
	int w;					// �ȼ���ÿ��
	WPixel color;
	WFont *font;
	char * text;			// �ַ���
	int userdata;
	
	WTipsStruct() {}
	~WTipsStruct() { WFree(text); }
	WTipsStruct(WFont *f,const char *string);
	// ��Ϊ Canvas �������� WString, ����ֱ���� byte copy ������ WString::operator=
//	WTipsStruct(const WTipsStruct& tips) { w=tips.w,font=tips.font,text=tips.text,userdata=tips.userdata,color=tips.color; }
	using memory<WTipsStruct>::operator new;
	using memory<WTipsStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WTipsStruct& operator=(const WTipsStruct&box);		//�޴˺���

};

WTipsStruct::WTipsStruct(WFont *f,const char *string)
{
	font=f;
	w=f->GetLength(string)+6;
	text=(char*)WAlloc(64);
	int i;
	for (i=0;i<64 && string[i];i++) {
		text[i]=string[i];
	}
	if (i==64) {
		WFree(text);	// �� string
		int n;
		for (n=i;string[n];n++) ;
		text=(char*)WAlloc(n+1);
		for (i=0;i<n;i++)
			text[i]=string[i];
	}
	text[i]=0;
	color=0xffffe7;
	kx=ky=0;
}

WObjStruct* WTips::Duplicate(WObjectHeap* heap) const
{
	// ���� WString �� ����copy
	WTipsStruct *tips=new(heap)WTipsStruct();
	WMemCpy(tips,GetTipsStruct(),sizeof(WTipsStruct));
	return tips;
}

void WTips::Destroy()
{
	if (objdata) delete GetTipsStruct();
	objdata=0;
}

void WTips::Create(WFont &font,const char *str)
{
	if (objdata==0) {
		objdata=new WTipsStruct(&font,str);
	}
	else {
		WTipsStruct *tips=GetTipsStruct();
		delete tips;
		objdata=new WTipsStruct(&font,str);
	}
}

int WTips::GetH() const
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	return tips->font->GetHeight()+4;
}

int WTips::GetW() const
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	return tips->w;
}

void WTips::SetColor(WPixel color)
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	tips->color=color;
}

void WTips::SetUserData(DWORD userdata) const
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	tips->userdata=userdata;
}

static WSERR _fastcall _draw_tips(WBmpStruct *bmp,const WTipsStruct *tips,int style)
{
	WBitmap temp;
	temp.SetData(bmp);
	int kx=bmp->kx,ky=bmp->ky;
	int h=tips->font->GetHeight()+2;
	WLine hline(tips->w,0,0);
	WLine vline(0,h,0);
	WBox box(tips->w-2,h,tips->color);
	hline.SetUserData(tips->userdata);
	vline.SetUserData(tips->userdata);
	box.SetUserData(tips->userdata);

	hline.SetPos(tips->kx,tips->ky);
	vline.SetPos(tips->kx,tips->ky-1);
	box.SetPos(tips->kx-1,tips->ky-1);

	temp.Draw(hline,style);
//	��һ�����д���������ʽ, �Ͳ���Ҫ������ʱλͼ temp
//	hline.DrawFunc(style)((DWORD)bmp,(DWORD)hline.GetLineStruct());

	temp.Draw(vline,style);

	hline.SetPos(tips->kx,tips->ky-tips->font->GetHeight()-3);
	vline.SetPos(tips->kx-tips->w+1,tips->ky-1);

	temp.Draw(hline,style);
	temp.Draw(vline,style);
	temp.Draw(box,style);

	temp.AddPos(3-tips->kx,2-tips->ky);
	tips->font->Draw(temp,tips->text,0);
	temp(kx,ky);			// �ָ� bmp �� kx,ky
	temp.SetData(0);		// ��֤ temp �˳���ʱ��ṹ�����ͷŵ�
	return WS_OK;
}

static WSERR _stdcall _draw_tips_solid(WBmpStruct *bmp,const WTipsStruct *tips)
{
	return _draw_tips(bmp,tips,BLIT_NORMAL);
}


static WSERR _stdcall _draw_tips_trans(WBmpStruct *bmp,const WTipsStruct *tips)
{
	return _draw_tips(bmp,tips,BLIT_TRANS);
}


BLIT_FUNC WTips::DrawFunc(DWORD style) const
{
	if (style==BLIT_TRANS) return (BLIT_FUNC)_draw_tips_trans;
	else return (BLIT_FUNC)_draw_tips_solid;
}
