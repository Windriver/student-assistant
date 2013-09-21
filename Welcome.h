#include <mzfc_inc.h>

//此代码演示了：
//  创建和初始化应用程序
//  创建和初始化窗体
//  按钮控件的使用及其命令消息的处理

// 按钮控件的ID
#define MZ_IDC_TESTBTN1  101

// 从 CMzWndEx 派生的主窗口类
class CSample1MainWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(CSample1MainWnd);
public:
  // 窗口中的按钮控件
  UiButton m_btn;

protected:
  // 窗口的初始化
  virtual BOOL OnInitDialog()
  {
    // 必须先调用基类的初始化
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

              // 初始化窗口中的控件
    m_btn.SetButtonType(MZC_BUTTON_GREEN);
    m_btn.SetPos(0,250,480,100);
    m_btn.SetID(MZ_IDC_TESTBTN1);
    m_btn.SetText(L"欢迎使用M8学生助手");
    m_btn.SetTextColor(RGB(255,255,255));

              // 把控件添加到窗口中
    AddUiWin(&m_btn);

    return TRUE;
  }

  // 重载命令消息的处理函数   L"You have pressed Exit button, Really want exit?"
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_TESTBTN1:
      {
		  CMzString i=L"好像";
		  CMzString q=L"";
		  int j=2009;
		  wsprintf(q.C_Str(),L"%s%s%d%s",L"是在",i.C_Str(),j,L"年");
        //if(1 == MzMessageBoxEx(m_hWnd, q, L"Exit", MB_YESNO, false))
          EndModal(MZ_IDC_TESTBTN1);
      }
      break;
    }
  }
};

MZ_IMPLEMENT_DYNAMIC(CSample1MainWnd)


