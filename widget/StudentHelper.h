


//包含MZFC库的头文件
#include <mzfc_inc.h>
#include "welcome.h"
#include "define.h"
#include "ScheduleEdit.h"


//此代码演示了：
//  创建和初始化应用程序
//  创建和初始化窗体
//  按钮控件的使用及其命令消息的处理





// 从 CMzWndEx 派生的主窗口类
class MainWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(MainWnd);
public:
  // 窗口中的按钮控件
  UiCaption Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday;
  UiStatic Mon[5],Tues[5],Wed[5],Thurs[5],Fri[5],Sat[5],Sun[5];
  UiToolbar_Text m_Bottom;


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

	Monday.SetID(MZ_IDC_MON);
	Monday.SetPos(0,0,160,MZM_HEIGHT_SUBJECT);
	Monday.SetText(L"周一");
	Monday.SetTextSize(25);
	AddUiWin(&Monday);

	Tuesday.SetID(MZ_IDC_TUES);
	Tuesday.SetPos(160,0,160,MZM_HEIGHT_SUBJECT);
	Tuesday.SetText(L"周二");
	Tuesday.SetTextSize(25);
	AddUiWin(&Tuesday);

	Wednesday.SetID(MZ_IDC_WED);
	Wednesday.SetPos(320,0,160,MZM_HEIGHT_SUBJECT);
	Wednesday.SetText(L"周三");
	Wednesday.SetTextSize(25);
	AddUiWin(&Wednesday);

	Thursday.SetID(MZ_IDC_THURS);
	Thursday.SetPos(0,310,160,MZM_HEIGHT_SUBJECT);
	Thursday.SetText(L"周四");
	Thursday.SetTextSize(25);
	AddUiWin(&Thursday);

	Friday.SetID(MZ_IDC_FRI);
	Friday.SetPos(160,310,160,MZM_HEIGHT_SUBJECT);
	Friday.SetText(L"周五");
	Friday.SetTextSize(25);
	AddUiWin(&Friday);

	Saturday.SetID(MZ_IDC_SAT);
	Saturday.SetPos(320,310,160,MZM_HEIGHT_SUBJECT);
	Saturday.SetText(L"周末");
	Saturday.SetTextSize(25);
	AddUiWin(&Saturday);

	Sunday.SetID(MZ_IDC_SUN);
	Sunday.SetPos(320,470,160,MZM_HEIGHT_SUBJECT);
	Sunday.SetText(L"星期天");
	Sunday.SetTextSize(25);
//	AddUiWin(&Sunday);

	m_Bottom.SetID(MZ_IDC_BOTTOM );
	m_Bottom.SetPos(0,GetHeight()-MZM_HEIGHT_BOTTOM,GetWidth(),MZM_HEIGHT_BOTTOM);
	m_Bottom.SetButton(0,true,true,L"课程");
	m_Bottom.SetButton(1,true,true,L"编辑");
	m_Bottom.SetButton(2,true,true,L"退出");
//	m_Bottom.SetButton(3,true,true,L"日记");
	AddUiWin(&m_Bottom);

	for(int i=0;i<5;++i)
	{
		Mon[i].SetID(MZ_IDC_MON_1+i);
		Mon[i].SetPos(0,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		Mon[i].SetText(L"<无课>");
		AddUiWin(&Mon[i]);

		Tues[i].SetID(MZ_IDC_TUES_1+i);
		Tues[i].SetPos(160,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		Tues[i].SetText(L"<无课>");
		AddUiWin(&Tues[i]);

		Wed[i].SetID(MZ_IDC_WED_1+i);
		Wed[i].SetPos(320,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		Wed[i].SetText(L"<无课>");
		AddUiWin(&Wed[i]);

		Thurs[i].SetID(MZ_IDC_THURS_1+i);
		Thurs[i].SetPos(0,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		Thurs[i].SetText(L"<无课>");
		AddUiWin(&Thurs[i]);

		Fri[i].SetID(MZ_IDC_FRI_1+i);
		Fri[i].SetPos(160,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		Fri[i].SetText(L"<无课>");
		AddUiWin(&Fri[i]);

		Sat[i].SetID(MZ_IDC_SAT_1+i);
		Sat[i].SetPos(320,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		Sat[i].SetText(L"<无课>");
		AddUiWin(&Sat[i]);
	}



	//欢迎界面
	
	CSample1MainWnd welcome;
	RECT rcWork = MzGetWorkArea();
	welcome.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),
	m_hWnd, 0, WS_POPUP);
	welcome.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_PUSH);
	welcome.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);
//	welcome.DoModal();




           
 

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	case MZ_IDC_BOTTOM:
      {
		  int nIndex=lParam;
		  if(nIndex==2)
		  {
			  if(1 == MzMessageBoxEx(m_hWnd, L"你确定要退出?", L"Exit", MB_YESNO, false))
				PostQuitMessage(0);
		  }
		  if(nIndex==1)
		  {
			  ScheduleEditWnd editwnd;
			  RECT rcWork = MzGetWorkArea();
			  editwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
			  editwnd.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
			  editwnd.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);
			  editwnd.DoModal();
			 
			   
			  CppSQLite3DB db;
 			  CppSQLite3Query *pQuery;
		      db.open(L"Schedule.db");
			  CMzString date_today=M8Date::DateToday();
			  CMzString sql(200);
			  wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");

			  pQuery=db.execQuery(sql);
			  CMzString week_temp=pQuery->fieldValue(L"week");

			  wsprintf(sql.C_Str(),L"%s%s%s",L"select * from schedule where week='",week_temp.C_Str(),L"';");
			  pQuery=db.execQuery(sql);
			  

	
			  
			      
				  CMzString get_sub=pQuery->fieldValue(L"first_c");
				  this->Mon[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_c");
				  this->Mon[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_c");
				  this->Mon[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_c");
				  this->Mon[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_c");
				  this->Mon[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_c");
				  this->Tues[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_c");
				  this->Tues[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_c");
				  this->Tues[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_c");
				  this->Tues[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_c");
				  this->Tues[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_c");
				  this->Wed[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_c");
				  this->Wed[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_c");
				  this->Wed[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_c");
				  this->Wed[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_c");
				  this->Wed[4].SetText(get_sub);


				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_c");
				  this->Thurs[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_c");
				  this->Thurs[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_c");
				  this->Thurs[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_c");
				  this->Thurs[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_c");
				  this->Thurs[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_c");
				  this->Fri[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_c");
				  this->Fri[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_c");
				  this->Fri[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_c");
				  this->Fri[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_c");
				  this->Fri[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_c");
				  this->Sat[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_c");
				  this->Sat[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_c");
				  this->Sat[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_c");
				  this->Sat[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_c");
				  this->Sat[4].SetText(get_sub);



				  
				 
				  
				 

	
			  pQuery->finalize();
			  db.close();

		//    貌似不需要更新...........
		//	  Mon[0].Update();
		//	  Mon[1].Update();
		//    this->UpdateWindow();
			
		  }
      }
      break;

	}
  }
};

//MZ_IMPLEMENT_DYNAMIC(MainWnd)

// 从 CMzApp 派生的应用程序类
class MainApp: public CMzApp
{
public:
  // 应用程序的主窗口
  MainWnd m_MainWnd;
  

  // 应用程序的初始化
  virtual BOOL Init()
  {
              // 初始化 COM 组件
    CoInitializeEx(0, COINIT_MULTITHREADED);

              // 创建主窗口
    RECT rcWork = MzGetWorkArea();
    m_MainWnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),0, 0, 0);
    m_MainWnd.Show();

              // 成功则返回TRUE
    return TRUE;
  }
};

// 全局的应用程序对象
//MainApp theApp;
