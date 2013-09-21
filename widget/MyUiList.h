#include <mzfc_inc.h>

class MyListItem
{
public:
	CMzString WeekTime;  
	CMzString VagueTime; 
	CMzString Remind;
	CMzString DateTime;
};

class MyUiList: public UiList
{
public:
//	MyUiList();
//	virtual ~MyUiList();
	virtual void DrawItem (HDC hdcDst, int nIndex, RECT *prcItem, RECT *prcWin, RECT *prcUpdate)
	{
		ListItem* pItem = GetItem(nIndex);
		if (pItem==0)
			return;
		if (pItem->Data==0)
			return;

		MyListItem *pmlid = (MyListItem*)pItem->Data;


		COLORREF clr = RGB(154 ,255 ,154 );
		COLORREF clr_Important = RGB(255 ,174 ,185 );
		RECT agendaRect=*prcItem;
		InflateRect(&agendaRect,-4,-4);		
		
		agendaRect.right=agendaRect.left+90;
//		DrawRoundRect(hdcDst,&agendaRect,15,clr,clr);		
		MzDrawText(hdcDst,pmlid->WeekTime, &agendaRect, DT_VCENTER|DT_CENTER);
		DrawColorLine(hdcDst,agendaRect.right,agendaRect.top,agendaRect.right,agendaRect.bottom,RGB(207 ,207 ,207 ));

		agendaRect.left=agendaRect.right;
		agendaRect.right=agendaRect.left+70;
		MzDrawText(hdcDst,pmlid->VagueTime, &agendaRect, DT_VCENTER|DT_CENTER);
		DrawColorLine(hdcDst,agendaRect.right,agendaRect.top,agendaRect.right,agendaRect.bottom,RGB(207 ,207 ,207 ));

		agendaRect.left=agendaRect.right+5;
		agendaRect.right=agendaRect.left+175;	
		if(pmlid->VagueTime.Length()==5)
		{
			DrawRoundRect(hdcDst,&agendaRect,5,clr_Important,clr_Important);
		}
		else{
			DrawRoundRect(hdcDst,&agendaRect,5,clr,clr);
		}
		agendaRect.left=agendaRect.left+5;
		agendaRect.right=agendaRect.left+165;

		MzDrawText(hdcDst,pmlid->Remind, &agendaRect, DT_VCENTER|DT_LEFT);
		DrawColorLine(hdcDst,agendaRect.right+10,agendaRect.top,agendaRect.right+10,agendaRect.bottom,RGB(207 ,207 ,207 ));
 
		agendaRect.left=agendaRect.right+15;
		agendaRect.right=agendaRect.left+50;		
//		DrawRoundRect(hdcDst,&agendaRect,15,clr,clr);
		MzDrawText(hdcDst,pmlid->DateTime, &agendaRect, DT_VCENTER|DT_CENTER);		
	}
	virtual void OnRemoveItem(int nIndex)
	{
		ListItem* pItem = GetItem(nIndex);
		if(pItem)
		{
			MyListItem* mlid = (MyListItem*)pItem->Data;
			if(mlid)
				delete mlid; 
		}
	}

};


class ColorfulCareer: public UiWin
{
private:
	float proportion;

public:
	ColorfulCareer()
	{
		proportion=0.6;
	}

	void SetProportion(float pro)
	{
		this->proportion=pro;
		this->Invalidate();
		this->Update();
	}
	

	virtual void PaintWin(HDC hdcDst, RECT *prcWin, RECT *prcUpdate)
	{

		COLORREF clr = RGB(154 ,255 ,154 );
		COLORREF clr_Important = RGB(255 ,174 ,185 );
//		COLORREF clr = RGB(0, 255 ,127 );
//		COLORREF clr_Important = RGB(255 ,20 ,147 );
		COLORREF clr_Under_Line = RGB(0,0,0);
		COLORREF clr_Under = RGB(156  ,156  ,156   );
	//	COLORREF clr_White = RGB(255,255,255 );
		RECT rect=*prcWin;
		::InflateRect(&rect,-5,-1);
		DrawRoundRect(hdcDst,&rect,5,RGB(54, 54 ,54 ),RGB(54, 54 ,54 ));
		::InflateRect(&rect,-5,-5);

		RECT PastRect=rect;
		PastRect.right=PastRect.right*proportion;			  
		::DrawRect(hdcDst,&PastRect,clr_Important,clr_Important);

		RECT ToBePastRect=rect;
		ToBePastRect.left=PastRect.right;
		::DrawRect(hdcDst,&ToBePastRect,clr,clr);

		/*rect=*prcWin;
		rect.left=PastRect.right-5;
		rect.right=ToBePastRect.left+5;
		::DrawRoundRect(hdcDst,&rect,1,RGB(54, 54 ,54 ),RGB(54, 54 ,54 ));*/

	}
};
