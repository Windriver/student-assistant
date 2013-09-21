//包含MZFC库的头文件
#include <mzfc_inc.h>
#include "Welcome.h"
#include "Define.h"
#include "ScheduleEdit.h"
#include "AddRemind.h"
#include "SilenceSet.h"
#include "BlogDiary.h"
#include "MyUiList.h"
#include "resource.h"
#include "MyCareer.h"


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
  UiCaption m_Caption;
  UiStatic m_which_o[6];
  UiStatic m_which_u[6];
  UiButton m_Silence;
  UiButton m_Diary;
  UiButton m_Line[6];
  UiButton m_Lastweek,m_Nextweek;
  UiButton m_VertLine[3]; 
  UiCaption keci[2];
  UiButton m_ParaLine[2];
  UiButton_Image m_Mycareer;


  ImageContainer m_imgContainer;
  MzGridMenu begin_GridMenu;
  ImageContainer begin_imgContainer;


  CMzString week_temp;



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
	COLORREF clr = RGB(165 ,42, 42 );
	m_Caption.SetPos(0,0,480,MZM_HEIGHT_CAPTION+2);
	m_Caption.SetTextColor(clr);
	m_Caption.SetTextSize(25);
	AddUiWin(&m_Caption);

	for(int i=0;i<3;++i)
	{
		m_VertLine[i].SetPos(140*i,MZM_HEIGHT_CAPTION+2,60,MZM_HEIGHT_SUBJECT*10+MZM_HEIGHT_DAYINWEEK*2-2);
		m_VertLine[i].SetButtonType(MZC_BUTTON_LINE_RIGHT);
		AddUiWin(&m_VertLine[i]);
	}

	m_ParaLine[0].SetPos(0,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_SUBJECT,480,MZM_HEIGHT_SUBJECT*2);
	m_ParaLine[0].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&m_ParaLine[0]);

	m_ParaLine[1].SetPos(0,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK*2+MZM_HEIGHT_SUBJECT*6,480,MZM_HEIGHT_SUBJECT*2);
	m_ParaLine[1].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&m_ParaLine[1]);

	COLORREF clr1 = RGB(0 ,0 ,205 );
	m_Lastweek.SetPos(0,0,80,MZM_HEIGHT_CAPTION);
	m_Lastweek.SetID(MZ_IDC_LASTWEEK);
	m_Lastweek.SetTextColor(clr1);
	m_Lastweek.SetTextSize(22);
	m_Lastweek.SetText(L"上一周");	
	m_Lastweek.SetButtonType(MZC_BUTTON_RECT_NOFILL);
	AddUiWin(&m_Lastweek);

	m_Nextweek.SetPos(GetWidth()-80,0,80,MZM_HEIGHT_CAPTION);
	m_Nextweek.SetID(MZ_IDC_NEXTWEEK);
	m_Nextweek.SetTextColor(clr1);
	m_Nextweek.SetTextSize(22);
	m_Nextweek.SetText(L"下一周");
	m_Nextweek.SetButtonType(MZC_BUTTON_RECT_NOFILL);
	AddUiWin(&m_Nextweek);

	m_Line[0].SetPos(0,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK,480,MZM_HEIGHT_SUBJECT*2);
	m_Line[0].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&m_Line[0]);

	m_Line[1].SetPos(0,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_SUBJECT*4,480,MZM_HEIGHT_SUBJECT);
	m_Line[1].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&m_Line[1]);

	m_Line[2].SetPos(0,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK*2+MZM_HEIGHT_SUBJECT*5,480,MZM_HEIGHT_SUBJECT*2);
	m_Line[2].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&m_Line[2]);

	m_Line[3].SetPos(0,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK*2+MZM_HEIGHT_SUBJECT*9,480,MZM_HEIGHT_SUBJECT);
	m_Line[3].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&m_Line[3]);

	m_Line[4].SetPos(-100,MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_SUBJECT*5,680,MZM_HEIGHT_SUBJECT);
	m_Line[4].SetButtonType(MZC_GRIDLINE_SOLID_PRESSED);
	AddUiWin(&m_Line[4]);

	m_Line[5].SetPos(-100,MZM_HEIGHT_CAPTION,680,MZM_HEIGHT_SUBJECT);
	m_Line[5].SetButtonType(MZC_GRIDLINE_SOLID_PRESSED);
	AddUiWin(&m_Line[5]);

	keci[0].SetPos(0,MZM_HEIGHT_CAPTION+2,60,MZM_HEIGHT_SUBJECT);
	keci[0].SetText(L"课次");
	keci[1].SetPos(0,MZM_HEIGHT_CAPTION+2+MZM_HEIGHT_SUBJECT*5+MZM_HEIGHT_DAYINWEEK,60,MZM_HEIGHT_SUBJECT);
	keci[1].SetText(L"课次");
	AddUiWin(&keci[0]);
	AddUiWin(&keci[1]);

	for(int i=1;i<6;++i)
	{
		m_which_o[i].SetPos(0,(i-1)*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK,60,MZM_HEIGHT_SUBJECT);
		m_which_u[i].SetPos(0,(i+4)*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_CAPTION+MZM_HEIGHT_DAYINWEEK*2,60,MZM_HEIGHT_SUBJECT);
		if(i==1)
		{
			m_which_o[i].SetText(L"一");
			m_which_u[i].SetText(L"一");
		}
		else if(i==2)
		{
			m_which_o[i].SetText(L"二");
			m_which_u[i].SetText(L"二");
		}
		else if(i==4)
		{
			m_which_o[i].SetText(L"四");
			m_which_u[i].SetText(L"四");
		}
		else if(i==3)
		{
			m_which_o[i].SetText(L"三");
			m_which_u[i].SetText(L"三");
		}
		else if(i==5)
		{
			m_which_o[i].SetText(L"晚");
			m_which_u[i].SetText(L"晚");
		}
		AddUiWin(&m_which_o[i]);
		AddUiWin(&m_which_u[i]);
	}

	Monday.SetID(MZ_IDC_MON);
	Monday.SetPos(60,MZM_HEIGHT_CAPTION+2,140,MZM_HEIGHT_SUBJECT);
	Monday.SetText(L"周一");
	Monday.SetTextSize(25);
	AddUiWin(&Monday);

	Tuesday.SetID(MZ_IDC_TUES);
	Tuesday.SetPos(200,MZM_HEIGHT_CAPTION+2,140,MZM_HEIGHT_SUBJECT);
	Tuesday.SetText(L"周二");
	Tuesday.SetTextSize(25);
	AddUiWin(&Tuesday);

	Wednesday.SetID(MZ_IDC_WED);
	Wednesday.SetPos(340,MZM_HEIGHT_CAPTION+2,140,MZM_HEIGHT_SUBJECT);
	Wednesday.SetText(L"周三");
	Wednesday.SetTextSize(25);
	AddUiWin(&Wednesday);

	Thursday.SetID(MZ_IDC_THURS);
	Thursday.SetPos(60,MZM_HEIGHT_CAPTION+2+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_SUBJECT*5,140,MZM_HEIGHT_SUBJECT);
	Thursday.SetText(L"周四");
	Thursday.SetTextSize(25);
	AddUiWin(&Thursday);

	Friday.SetID(MZ_IDC_FRI);
	Friday.SetPos(200,MZM_HEIGHT_CAPTION+2+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_SUBJECT*5,140,MZM_HEIGHT_SUBJECT);
	Friday.SetText(L"周五");
	Friday.SetTextSize(25);
	AddUiWin(&Friday);

	Saturday.SetID(MZ_IDC_SAT);
	Saturday.SetPos(340,MZM_HEIGHT_CAPTION+2+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_SUBJECT*5,140,MZM_HEIGHT_SUBJECT);
	Saturday.SetText(L"周末");
	Saturday.SetTextSize(25);
	AddUiWin(&Saturday);

	Sunday.SetID(MZ_IDC_SUN);
	Sunday.SetPos(320,470,160,MZM_HEIGHT_SUBJECT);
	Sunday.SetText(L"星期天");
	Sunday.SetTextSize(25);
//	AddUiWin(&Sunday);

	ImagingHelper* imgNormal = m_imgContainer.LoadImage(MzGetInstanceHandle(), IDB_PNG2, true);
    ImagingHelper* imgPressed = m_imgContainer.LoadImage(MzGetInstanceHandle(), IDB_PNG3, true);


	m_Mycareer.SetID(MZ_IDC_CAREER);
    m_Mycareer.SetButtonType(MZC_BUTTON_NONE);
    m_Mycareer.SetPos(180,534,120,90);
	m_Mycareer.SetText(L"生涯");
    m_Mycareer.SetImage_Normal(imgNormal);
    m_Mycareer.SetImage_Pressed(imgPressed);
    m_Mycareer.SetMode(UI_BUTTON_IMAGE_MODE_NORMAL);
    m_Mycareer.SwapImageZOrder(true);
    m_Mycareer.SetTextColor(RGB(255,255,255));
    AddUiWin(&m_Mycareer);

	m_Silence.SetPos(10,545,170,64);
	m_Silence.SetID(MZ_IDC_SILENCE);
	m_Silence.SetText(L"静音设置");
	m_Silence.SetButtonType(MZC_BUTTON_GREEN);
	AddUiWin(&m_Silence); 

	m_Diary.SetPos(300,545,170,64);
	m_Diary.SetID(MZ_IDC_DIARY);
	m_Diary.SetText(L"日记微博");
	m_Diary.SetButtonType(MZC_BUTTON_ORANGE);
	AddUiWin(&m_Diary);

	m_Bottom.SetID(MZ_IDC_BOTTOM );
	m_Bottom.SetPos(0,GetHeight()-70,GetWidth(),70);  
	m_Bottom.SetButton(0,true,true,L"开始");
	m_Bottom.SetButton(1,true,true,L"日程提醒");
	m_Bottom.SetButton(2,true,true,L"退出");
	AddUiWin(&m_Bottom);

	ImagingHelper* m_selImg = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_selImgPrs = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_dImg = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_dImgPrs = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_celImg = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_celImgPrs = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);
    ImagingHelper* m_secImg = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_secImgPrs = begin_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);

        // 初始化 MzGridMenu 控件
    begin_GridMenu.AppendMenuItem(MZ_BEGIN_GRIDMENU_ITEM1, L"返回主页", m_selImg, m_selImgPrs);
    begin_GridMenu.AppendMenuItem(MZ_BEGIN_GRIDMENU_ITEM2, L"新建课程表", m_dImg, m_dImgPrs);
    begin_GridMenu.AppendMenuItem(MZ_BEGIN_GRIDMENU_ITEM3, L"查看教室", m_celImg, m_celImgPrs);
    begin_GridMenu.AppendMenuItem(MZ_BEGIN_GRIDMENU_ITEM4, L"编辑/查看", m_secImg, m_secImgPrs);


	for(int i=0;i<5;++i)
	{
		Mon[i].SetID(MZ_IDC_MON_1+i);
		Mon[i].SetPos(60,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_CAPTION,140,MZM_HEIGHT_SUBJECT);
		AddUiWin(&Mon[i]);

		Tues[i].SetID(MZ_IDC_TUES_1+i);
		Tues[i].SetPos(200,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_CAPTION,140,MZM_HEIGHT_SUBJECT);
		AddUiWin(&Tues[i]);

		Wed[i].SetID(MZ_IDC_WED_1+i);
		Wed[i].SetPos(340,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+MZM_HEIGHT_CAPTION,140,MZM_HEIGHT_SUBJECT);
		AddUiWin(&Wed[i]);

		Thurs[i].SetID(MZ_IDC_THURS_1+i);
		Thurs[i].SetPos(60,(i+5)*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK*2+MZM_HEIGHT_CAPTION,140,MZM_HEIGHT_SUBJECT);
		AddUiWin(&Thurs[i]);

		Fri[i].SetID(MZ_IDC_FRI_1+i);
		Fri[i].SetPos(200,(i+5)*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK*2+MZM_HEIGHT_CAPTION,140,MZM_HEIGHT_SUBJECT);
		AddUiWin(&Fri[i]);

		Sat[i].SetID(MZ_IDC_SAT_1+i);
		Sat[i].SetPos(340,(i+5)*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK*2+MZM_HEIGHT_CAPTION,140,MZM_HEIGHT_SUBJECT);
		AddUiWin(&Sat[i]);
	}

			  CppSQLite3DB db;
 			  CppSQLite3Query *pQuery;
		      db.open(L"Schedule.db");
			  CMzString date_today=M8Date::DateToday();
			  CMzString sql(200);
			  wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");

			  pQuery=db.execQuery(sql);
			  week_temp=pQuery->fieldValue(L"week");
			  pQuery->finalize();
			  db.close();

			  PrintSchedule();

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {		
	case MZ_IDC_LASTWEEK:
		{
			int lastweek=_ttoi(week_temp)-1;
			wsprintf(week_temp.C_Str(),L"%d",lastweek);
			PrintSchedule();
			this->Invalidate();
			this->UpdateWindow();
			break; 
		}
	case MZ_IDC_NEXTWEEK:
		{
			int nextweek=_ttoi(week_temp)+1;
			wsprintf(week_temp.C_Str(),L"%d",nextweek);
			PrintSchedule();
			this->Invalidate();
			this->UpdateWindow();
			break; 
		}
	case MZ_IDC_DIARY:
		{
			BlogDirayWnd blogdiraywnd;
			RECT rcWork = MzGetWorkArea();
			blogdiraywnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		    blogdiraywnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH);
			blogdiraywnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			blogdiraywnd.DoModal();
			break;   
		}
	case MZ_IDC_SILENCE:
		{
			SilenceWnd silencewnd;
			RECT rcWork = MzGetWorkArea();
			silencewnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		    silencewnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			silencewnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH);
			silencewnd.DoModal();
			break;
		}
	case MZ_IDC_CAREER:
		{
			MyCareerWnd mycareerwnd;
			RECT rcWork = MzGetWorkArea();
			mycareerwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		    mycareerwnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			mycareerwnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			mycareerwnd.DoModal();
			break;
		}

	case MZ_IDC_BOTTOM:
      {
		  int nIndex=lParam;
		  if(0==nIndex)
		  {
			  if (begin_GridMenu.IsContinue())
              {
                  begin_GridMenu.EndGridMenu();
              }
              else
              {
                    begin_GridMenu.TrackGridMenuDialog(m_hWnd, MZM_HEIGHT_TOOLBARPRO);
              }
		  }
		  if(nIndex==1)
		  {
			  if (begin_GridMenu.IsContinue())
              {
                    begin_GridMenu.EndGridMenu();
              }
			  else 
			  {
					AddRemind addremind;
					RECT rcWork = MzGetWorkArea();
					addremind.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
					addremind.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2 );
					addremind.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2 );
					addremind.DoModal();  
			  }
/*			  AgendaRemind agendaremind;
			  RECT rcWork_1 = MzGetWorkArea();
			  agendaremind.Create(rcWork_1.left,rcWork_1.top,RECT_WIDTH(rcWork_1),RECT_HEIGHT(rcWork_1),m_hWnd, 0, WS_POPUP);
			  agendaremind.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_PUSH);
			  agendaremind.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			  agendaremind.DoModal();    */
		  } 
		  if(nIndex==2)
		  {
			  if (begin_GridMenu.IsContinue())
              {
                    begin_GridMenu.EndGridMenu();
              }
			  else 
			  {
				  if(1 == MzMessageBoxEx(m_hWnd, L"你确定要退出吗?", L"Exit", MB_YESNO, false))
					PostQuitMessage(0);

			  }
		  }
		  break;
	  }
	  case MZ_BEGIN_GRIDMENU_ITEM4:
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
			  pQuery->finalize();
			  db.close();

			  PrintSchedule();
			  this->Invalidate();
			  this->UpdateWindow();
			  break;

		  

		//    貌似不需要更新...........
		//	  Mon[0].Update();
		//	  Mon[1].Update();
		//    this->UpdateWindow();     

		  }
	 case MZ_BEGIN_GRIDMENU_ITEM2:
		 {
			  IniSchedule begininit;
			  RECT rcWork = MzGetWorkArea();
			  begininit.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
			  begininit.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			  begininit.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
			  begininit.DoModal();

			  CppSQLite3DB db;
 			  CppSQLite3Query *pQuery;
			  db.open(L"Schedule.db");
			  CMzString date_today=M8Date::DateToday();
			  CMzString sql(200);
			  wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");

	   		  pQuery=db.execQuery(sql);
			  CMzString week_temp=pQuery->fieldValue(L"week");
			  pQuery->finalize();
			  db.close();

			  PrintSchedule();
			  this->Invalidate();
			  this->UpdateWindow();
			  break;
		 }
	 case MZ_BEGIN_GRIDMENU_ITEM3:
		 {
			 PrintClassroom();
			 this->Invalidate();
			 this->UpdateWindow();
			 break;
		 }
	 case MZ_BEGIN_GRIDMENU_ITEM1:
		 {
			 CppSQLite3DB db;
 			  CppSQLite3Query *pQuery;
		      db.open(L"Schedule.db");
			  CMzString date_today=M8Date::DateToday();
			  CMzString sql(200);
			  wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");

			  pQuery=db.execQuery(sql);
			  week_temp=pQuery->fieldValue(L"week");
			  pQuery->finalize();
			  db.close();

			  PrintSchedule();
			  this->Invalidate();
			  this->UpdateWindow();
			  break;
		 }
      

	}
  }

  void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
  {
	  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
      {
          if (begin_GridMenu.IsContinue())
          {
              begin_GridMenu.EndGridMenu();
          }
      }
  }

  void PrintSchedule()
  {
	  
			  CppSQLite3DB db;
 			  CppSQLite3Query *pQuery;
		      db.open(L"Schedule.db");
			  CMzString sql(200);
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

			  
			  SYSTEMTIME m_sTime;
			  GetLocalTime(&m_sTime);
			  CMzString msg_today;
			  wsprintf(msg_today.C_Str(),L"%d年 第 %s 教学周",m_sTime.wYear,week_temp.C_Str());
			  m_Caption.SetText(msg_today);

  }
  void PrintClassroom()
  {
			  CppSQLite3DB db;
 			  CppSQLite3Query *pQuery;
		      db.open(L"Schedule.db");
			  CMzString sql(200);
			  wsprintf(sql.C_Str(),L"%s%s%s",L"select * from schedule where week='",week_temp.C_Str(),L"';");
			  pQuery=db.execQuery(sql);
			//   MzMessageBoxEx(m_hWnd, msg_today, L"提醒");
			  						      
				  CMzString get_sub=pQuery->fieldValue(L"first_r");
				  this->Mon[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_r");
				  this->Mon[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_r");
				  this->Mon[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_r");
				  this->Mon[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_r");
				  this->Mon[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_r");
				  this->Tues[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_r");
				  this->Tues[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_r");
				  this->Tues[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_r");
				  this->Tues[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_r");
				  this->Tues[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_r");
				  this->Wed[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_r");
				  this->Wed[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_r");
				  this->Wed[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_r");
				  this->Wed[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_r");
				  this->Wed[4].SetText(get_sub);


				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_r");
				  this->Thurs[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_r");
				  this->Thurs[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_r");
				  this->Thurs[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_r");
				  this->Thurs[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_r");
				  this->Thurs[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_r");
				  this->Fri[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_r");
				  this->Fri[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_r");
				  this->Fri[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_r");
				  this->Fri[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_r");
				  this->Fri[4].SetText(get_sub);

				  pQuery->nextRow();
				  get_sub=pQuery->fieldValue(L"first_r");
				  this->Sat[0].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"second_r");
				  this->Sat[1].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"third_r");
				  this->Sat[2].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fouth_r");
				  this->Sat[3].SetText(get_sub);
				  get_sub=pQuery->fieldValue(L"fifth_r");
				  this->Sat[4].SetText(get_sub);
	
			  pQuery->finalize();
			  db.close();

			  
			 
			  CMzString msg_today;
			  wsprintf(msg_today.C_Str(),L"第 %s 教学周",week_temp.C_Str());
			  m_Caption.SetText(msg_today);
			  

  }
};

MZ_IMPLEMENT_DYNAMIC(MainWnd)

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
MainApp theApp;



