
















//包含MZFC库的头文件
#include <mzfc_inc.h>
#include <Sqlite/CppSQLite3U.h>
#include "MyCareer.h"

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
    m_btn.SetPos(100,250,280,100);
    m_btn.SetID(MZ_IDC_TESTBTN1);
    m_btn.SetText(L"Hello MZFC!");
    m_btn.SetTextColor(RGB(255,255,255));

              // 把控件添加到窗口中
    AddUiWin(&m_btn);

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_TESTBTN1:
      {
        MyCareerWnd mycareerwnd;
			RECT rcWork = MzGetWorkArea();
			mycareerwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		    mycareerwnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			mycareerwnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			mycareerwnd.DoModal();
      }
      break;
    }
  }
};

MZ_IMPLEMENT_DYNAMIC(CSample1MainWnd)

// 从 CMzApp 派生的应用程序类
class CSample1App: public CMzApp
{
public:
  // 应用程序的主窗口
  CSample1MainWnd m_MainWnd;

  // 应用程序的初始化
  virtual BOOL Init()
  {
              // 初始化 COM 组件
    CoInitializeEx(0, COINIT_MULTITHREADED);

              // 创建主窗口
    RECT rcWork = MzGetWorkArea();
    m_MainWnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork), 0, 0, 0);
    m_MainWnd.Show();

              // 成功则返回TRUE
    return TRUE;
  }
};

// 全局的应用程序对象
CSample1App theApp;

