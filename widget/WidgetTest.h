#include <mzfc_inc.h>
#include <Sqlite/CppSQLite3U.h>
#include <ShellWidget/ShellWidget.h>
#include <ShellNotifyMsg.h>


#include "MyUiList.h"


// Widget必须从UiWidget派生
// 根据需要，可重载StartWidget()以自定义Widget的启动行为

// SHWidget是一个简易的时钟Widget，显示当前时间，点击会变颜色。
class SHWidget: public UiWidget
{
public:
    SHWidget();
    virtual ~SHWidget();

    virtual void PaintWin(HDC hdcDst, RECT* prcWin, RECT* prcUpdate);

    virtual int OnLButtonDown(UINT fwKeys, int xPos, int yPos);
    virtual int OnLButtonUp(UINT fwKeys, int xPos, int yPos);
    virtual int OnMouseMove(UINT fwKeys, int xPos, int yPos);
	virtual int OnLButtonDblClk(UINT fwKeys, int xPos, int yPos);
    virtual bool StartWidget();
    virtual void EndWidget();

    virtual void OnCalcItemSize(__out int &xSize, __out int &ySize);

    virtual int OnTimer(UINT_PTR nIDEvent);
protected:

	void CheckNotify();
	void PrintAgenda();
	void SilenceSet();
	void BeSilent();
	BOOL SilenceSendMsgToShell(BOOL bSilence);



private:


public:

	MyUiList a_List;
	SYSTEMTIME st;
	//ColorfulCareer mycareer;
	//UiStatic carMsg;
	HANDLE hr;


};






