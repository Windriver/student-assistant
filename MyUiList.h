#include <mzfc_inc.h>






class BlackBlock: public UiWin
{

public:
	
	virtual void PaintWin(HDC hdcDst, RECT *prcWin, RECT *prcUpdate)
	{
	//	COLORREF clr = RGB(54, 54 ,54 );
		COLORREF clr = RGB(28 ,28, 28 );
		RECT rect=*prcWin;
	//	::InflateRect(&rect,-1,-1);
		
		DrawRect(hdcDst,&rect,clr,clr);	
	}
};

class GradBlackBlock: public UiWin
{

public:
	
	virtual void PaintWin(HDC hdcDst, RECT *prcWin, RECT *prcUpdate)
	{
	//	COLORREF clr_1 = RGB(79, 79 ,79 );
	//	COLORREF clr_2 = RGB(105 ,105 ,105 );
		COLORREF clr_1 = RGB(54, 54 ,54 );
		COLORREF clr_2 = RGB(79, 79 ,79 );

		RECT rect=*prcWin;
		
		DrawGradRect(hdcDst,&rect,clr_1,clr_2,0);	
	}
};
