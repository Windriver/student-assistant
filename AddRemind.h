#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <Sqlite/CppSQLite3U.h>
#include "define.h"
#include "AgendaRemind.h"




//全局变量
CMzString big_thing_now(100);


class AddSmallThing: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AddSmallThing);
public:
  // 窗口中的按钮控件
  UiSingleLineEdit new_thing;
  UiCaption new_Caption;
  UiToolbar_Text new_bottom;
  UiStatic new_big_thing_now;

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
    new_thing.SetPos(100,156,280,70);
	new_thing.SetSipMode(IM_SIP_MODE_GEL_PY);
    AddUiWin(&new_thing);
	new_thing.SetFocus(true);

	CMzString new_thing_tip(100);
	wsprintf(new_thing_tip.C_Str(),L"%s%s%s",L"正在为 <",big_thing_now.C_Str(),L"> 添加从事件");
	new_big_thing_now.SetPos(10,78,460,70);
	new_big_thing_now.SetText(new_thing_tip);
	AddUiWin(&new_big_thing_now);

	new_Caption.SetPos(0,0,480,70);
	new_Caption.SetText(L"添加新的从事件");
	AddUiWin(&new_Caption);

	new_bottom.SetID(MZ_AGA_BOTTOM_NEWTHING);
	new_bottom.SetPos(0,GetHeight()-70,480,70);
	new_bottom.SetButton(0,true,true,L"取消");
    new_bottom.SetButton(2,true,true,L"保存");
//	new_bottom.SetButton(2,true,true,L"清空");
	AddUiWin(&new_bottom);
 

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_AGA_BOTTOM_NEWTHING:
      {   
		  int nIndex=lParam;
		  
		  if(0==nIndex)
		  {
			  EndModal(MZ_AGA_BOTTOM_NEWTHING);
		  }
		  if(2==nIndex)
		  {
		      CppSQLite3DB db;
		      db.open(L"Schedule.db"); 
		      if(!db.tableExists(L"thing"))
		      {
			      db.execDML(L"create table thing (bigthing char(50),smallthing char(100));");
		      }
			  if(!(big_thing_now.IsEmpty())&&!(this->new_thing.GetText().IsEmpty()))
			  {
				  CMzString szsql(200);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",big_thing_now.C_Str(),new_thing.GetText().C_Str(),L");");
		//		  MzMessageBoxEx(m_hWnd, szsql, L"提醒");

				  db.execDML(szsql);
				  db.close(); 
			  }
			  EndModal(MZ_AGA_BOTTOM_NEWTHING);
		  }
      }
      break;
    }
  }
};

MZ_IMPLEMENT_DYNAMIC(AddSmallThing)

class AddBigThing: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AddBigThing);
public:
  // 窗口中的按钮控件
  UiSingleLineEdit new_thing;
  UiCaption new_Caption;
  UiToolbar_Text new_bottom;
  UiStatic new_big_thing_now;

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
    new_thing.SetPos(100,156,280,70);
	new_thing.SetSipMode(IM_SIP_MODE_GEL_PY);
    AddUiWin(&new_thing);
	new_thing.SetFocus(true);

	new_big_thing_now.SetPos(10,78,460,70);
	new_big_thing_now.SetText(L"请输入主事件");
	AddUiWin(&new_big_thing_now);

	new_Caption.SetPos(0,0,480,70);
	new_Caption.SetText(L"添加新的主事件");
	AddUiWin(&new_Caption);

	new_bottom.SetID(MZ_AGA_BOTTOM_NEWBIGTHING);
	new_bottom.SetPos(0,GetHeight()-70,480,70);
	new_bottom.SetButton(0,true,true,L"取消");
    new_bottom.SetButton(2,true,true,L"保存");
//	new_bottom.SetButton(2,true,true,L"清空");
	AddUiWin(&new_bottom);
 

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_AGA_BOTTOM_NEWBIGTHING:
      {   
		  int nIndex=lParam;
		  
		  if(0==nIndex)
		  {
			  EndModal(MZ_AGA_BOTTOM_NEWBIGTHING);
		  }
		  if(2==nIndex)
		  {
		      CppSQLite3DB db;
		      db.open(L"Schedule.db"); 
		      if(!db.tableExists(L"thing"))
		      {
			      db.execDML(L"create table thing (bigthing char(50),smallthing char(100));");
		      }
			  if(!(this->new_thing.GetText().IsEmpty()))
			  {
				  CMzString szsql(200);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",new_thing.GetText().C_Str(),L"主事件",L");");
		//		  MzMessageBoxEx(m_hWnd, szsql, L"提醒");

				  db.execDML(szsql);
				  db.close(); 
			  }
			  EndModal(MZ_AGA_BOTTOM_NEWBIGTHING);
		  }
      }
      break;
    }
  }
};

MZ_IMPLEMENT_DYNAMIC(AddBigThing)




class AddRemind: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AddRemind);
public:
  // 窗口中的按钮控件
  UiCaption aga_AddRemind;
  UiStatic  aga_Detail;
  UiStatic  aga_Vague;
  UiButton aga_DateBtn;
  UiButton aga_TimeBtn;
  UiButton aga_WeekThBtn;
  UiButton aga_WeekBtn;
  UiButton aga_AmPmBtn;
  UiButton aga_checkAll;
  UiStatic aga_static;
  UiSingleLineEdit aga_aga;
  UiCaption aga_caption_thing[2];
  UiList aga_List_big;
  UiList aga_List_small;
  UiButton aga_Line;


  MzGridMenu aga_GridMenu;
  ImageContainer aga_imgContainer;

  UiToolbar_Text aga_bottom_add;

  SYSTEMTIME m_sTime;

private:
  bool isToday;            //用来确定事件事件是否为今天
  bool isVague;           //用来确定是否用模糊模式表示时间



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
	
	aga_Line.SetPos(0,314,186,300);
	aga_Line.SetButtonType(MZC_BUTTON_LINE_RIGHT);
	AddUiWin(&aga_Line);

	aga_AddRemind.SetPos(0,0,480,45);
	aga_AddRemind.SetText(L"添加日程提醒");
	AddUiWin(&aga_AddRemind);

    GetLocalTime(&m_sTime);
	isVague=true;
    CMzString str(128);
    
	COLORREF clr = RGB(0 ,0 ,205 );
	COLORREF clr_Important = RGB(165 ,42, 42 );

	aga_Detail.SetPos(15,60,120,60);
	aga_Detail.SetTextColor(clr_Important);
	aga_Detail.SetTextSize(24);
	aga_Detail.SetDrawTextFormat(DT_LEFT|DT_VCENTER);
	aga_Detail.SetText(L"详细设时:");
	AddUiWin(&aga_Detail);

	aga_Vague.SetPos(15,210,120,60);
	aga_Vague.SetTextColor(clr);
	aga_Vague.SetTextSize(24);
	aga_Vague.SetDrawTextFormat(DT_LEFT|DT_VCENTER);
	aga_Vague.SetText(L"快捷设时:");
	AddUiWin(&aga_Vague);

    aga_DateBtn.SetButtonType(MZC_BUTTON_GRAY);
    aga_DateBtn.SetID(MZ_AGA_DATE_ADD);
    aga_DateBtn.SetPos(130, 60, 190, 60);
    wsprintf(str.C_Str(), L"%2d-%02d-%02d", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
    aga_DateBtn.SetText(str.C_Str());
    aga_DateBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&aga_DateBtn);
	
	aga_TimeBtn.SetButtonType(MZC_BUTTON_GRAY);
    aga_TimeBtn.SetID(MZ_AGA_TIME_ADD);
    aga_TimeBtn.SetPos(340, 60, 130, 60);
	wsprintf(str.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
    aga_TimeBtn.SetText(str.C_Str());
    aga_TimeBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&aga_TimeBtn);

	aga_WeekThBtn.SetButtonType(MZC_BUTTON_GRAY);
    aga_WeekThBtn.SetID(MZ_AGA_WEEKTH_ADD);
    aga_WeekThBtn.SetPos(130, 210, 100, 60);
    aga_WeekThBtn.SetText(L"本周");
    aga_WeekThBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&aga_WeekThBtn);

	CppSQLite3DB db;
 	CppSQLite3Query *weekpQuery;
	db.open(L"Schedule.db");
	CMzString date_today=M8Date::DateToday();
	CMzString weeksql(200);
	wsprintf(weeksql.C_Str(),L"%s%s%s",L"select * from schedule where date='",date_today.C_Str(),L"';");
	weekpQuery=db.execQuery(weeksql);
	CMzString week_temp=weekpQuery->fieldValue(L"dayweek");  
	int dayweek_today=_ttoi(week_temp);
	if(dayweek_today==1)
	{
		aga_WeekBtn.SetText(L"星期一");
	}
	else if(dayweek_today==2)
	{
		aga_WeekBtn.SetText(L"星期二");
	}
	else if(dayweek_today==3)
	{
		aga_WeekBtn.SetText(L"星期三");
	}
	else if(dayweek_today==4)
	{
		aga_WeekBtn.SetText(L"星期四");
	}
	else if(dayweek_today==5)
	{
		aga_WeekBtn.SetText(L"星期五");
	}
	else if(dayweek_today==6)
	{
		aga_WeekBtn.SetText(L"星期六");
	}
	else if(dayweek_today==7)
	{
		aga_WeekBtn.SetText(L"星期日");
	}
//	db.close();

	aga_WeekBtn.SetButtonType(MZC_BUTTON_GRAY);
    aga_WeekBtn.SetID(MZ_AGA_WEEK_ADD);
    aga_WeekBtn.SetPos(250, 210, 100, 60);    
    aga_WeekBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&aga_WeekBtn);

	aga_AmPmBtn.SetButtonType(MZC_BUTTON_GRAY);
    aga_AmPmBtn.SetID(MZ_AGA_AMPM_ADD);
    aga_AmPmBtn.SetPos(370, 210, 100, 60);
	if(m_sTime.wHour<12)
	{
		str=L"上午";
	}
	else if(m_sTime.wHour<18)
	{
		str=L"下午";
	}
	else
	{
		str=L"晚上";
	}
    aga_AmPmBtn.SetText(str.C_Str());
    aga_AmPmBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&aga_AmPmBtn);

	aga_static.SetPos(5,130,70,70);
	aga_static.SetText(L"事件:");
	AddUiWin(&aga_static);

	aga_aga.SetPos(80,130,220,70);
	AddUiWin(&aga_aga);

	aga_checkAll.SetID(MZ_AGA_CHECK_ALL);
	aga_checkAll.SetPos(GetWidth()-170,130,160,70);
	aga_checkAll.SetText(L"查看全部");
	aga_checkAll.SetButtonType(MZCV2_BUTTON_GREEN);
	AddUiWin(&aga_checkAll);




	aga_bottom_add.SetID(MZ_AGA_BOTTOM_ADD);
	aga_bottom_add.SetPos(0,GetHeight()-70,GetWidth(),70);
	aga_bottom_add.EnableLeftArrow(true);
	aga_bottom_add.SetButton(0,true,true,L"返回");
    aga_bottom_add.SetButton(1,true,true,L"保存");
    aga_bottom_add.SetButton(2,true,true,L"选项");
	AddUiWin(&aga_bottom_add);

	ImagingHelper* m_selImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_selImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_dImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_dImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_celImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_celImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);
    ImagingHelper* m_secImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_secImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);

        // 初始化 MzGridMenu 控件
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM11, L"删除主事件", m_selImg, m_selImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM22, L"删除从事件", m_dImg, m_dImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM33, L"添加主事件", m_celImg, m_celImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM44, L"添从从事件", m_secImg, m_secImgPrs);


	aga_caption_thing[0].SetPos(0,280,180,34);
	aga_caption_thing[0].SetText(L"主事件");
	AddUiWin(&aga_caption_thing[0]);

	aga_caption_thing[1].SetPos(180,280,300,34);
	aga_caption_thing[1].SetText(L"从事件");
	AddUiWin(&aga_caption_thing[1]);

	aga_List_big.SetPos(0,314,180,300);
    aga_List_big.SetID(MZ_AGA_LIST_1);
	aga_List_big.SetItemHeight(60);
    aga_List_big.EnableScrollBarV(false);
    aga_List_big.EnableNotifyMessage(true);
    AddUiWin(&aga_List_big);

	aga_List_small.SetPos(190,314,290,300);
    aga_List_small.SetID(MZ_AGA_LIST_2);
	aga_List_small.SetItemHeight(60);
    aga_List_small.EnableScrollBarV(false);
    aga_List_small.EnableNotifyMessage(true);
    AddUiWin(&aga_List_small);

//	CppSQLite3DB db;
//	db.open(L"Schedule.db");
	db.execDML(L"drop table thing;");
	if(!db.tableExists(L"thing"))
	{
			      db.execDML(L"create table thing (bigthing char(50),smallthing char(100));");
		      
			 
				  CMzString szsql(200);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"交作业",L"交高数作业",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"交作业",L"交软工上机报告",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"约会",L"与葛平会面",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"约会",L"与小红帽约会",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"喂猪",L"给小灰喂营养快线",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"喂猪",L"给肥肥做心理疏导",L");");
				  db.execDML(szsql);
				  db.close(); 
	}

	ListItem big_thing;
//	CppSQLite3DB db;
	CppSQLite3Query *pQuery;
	CMzString sql(200);
//	db.open(L"Schedule.db"); 		
	if(db.tableExists(L"thing"))
	{
		wsprintf(sql.C_Str(),L"%s",L"select distinct bigthing from thing;");
		pQuery=db.execQuery(sql);
		while(!(pQuery->eof()))
		{              		
			big_thing.Text=pQuery->fieldValue(L"bigthing");
			aga_List_big.AddItem(big_thing);
			pQuery->nextRow();
		}
		pQuery->finalize();
	}
//	db.close();
	aga_List_big.Invalidate();
    aga_List_big.Update();

	aga_List_big.SetSelectedIndex(0);
	big_thing_now=aga_List_big.GetItem(0)->Text;
	ListItem small_thing;
//	db.open(L"Schedule.db"); 		
	if(db.tableExists(L"thing"))
	{
		wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'主事件';");
		pQuery=db.execQuery(sql);
		while(!(pQuery->eof()))
		{              
			//MzMessageBoxEx(m_hWnd, sql, L"提醒");
			
			small_thing.Text=pQuery->fieldValue(L"smallthing");
			aga_List_small.AddItem(small_thing);
			pQuery->nextRow();
		}
		pQuery->finalize();
	}
	db.close();
	aga_List_small.Invalidate();
    aga_List_small.Update();

           

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	case MZ_AGA_CHECK_ALL:
		{
			AgendaRemind agendaremind;
     		RECT rcWork_1 = MzGetWorkArea();
			agendaremind.Create(rcWork_1.left,rcWork_1.top,RECT_WIDTH(rcWork_1),RECT_HEIGHT(rcWork_1),m_hWnd, 0, WS_POPUP);
			agendaremind.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH);
			agendaremind.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			agendaremind.DoModal(); 
			break;   
		}

    case MZ_AGA_DATE_ADD:
      {
		  MzSetDaily setDateDlg;
          setDateDlg.m_InitData.iItemCounter = 3;
          setDateDlg.m_InitData.iItem1Max = 2021 - 1923; // 年份是从1923年开始计算的
          setDateDlg.m_InitData.iItem2Max = 12;
          setDateDlg.m_InitData.iItem3Max = setDateDlg.MaxDaysInMonth(m_sTime.wMonth, m_sTime.wYear);

          // 设置对话框初始显示日期的项index，index值从0开始
          setDateDlg.m_InitData.iItem1Data = m_sTime.wYear - 1923;
          setDateDlg.m_InitData.iItem2Data = m_sTime.wMonth - 1;
          setDateDlg.m_InitData.iItem3Data = m_sTime.wDay - 1;

          setDateDlg.m_InitData.sItem1 = L"年";
          setDateDlg.m_InitData.sItem2 = L"月";
          setDateDlg.m_InitData.sItem3 = L"日";
          setDateDlg.m_InitData.iItem1Width = setDateDlg.m_InitData.iItem2Width = setDateDlg.m_InitData.iItem3Width = 140;
          setDateDlg.EnableDisplayYearData(true);
          setDateDlg.SetEnableChangeItemData(true);

          // 创建日期设置对话框的窗口
          RECT rcWorkDate = MzGetWorkArea();
          setDateDlg.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // 设置窗口淡出的动画效果
          setDateDlg.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setDateDlg.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // 如果对话框点击“确定”，显示对话框设置的日期
          if (ID_OK == setDateDlg.DoModal())
          {
              m_sTime.wYear = setDateDlg.m_InitData.iItem1Data;
              m_sTime.wMonth = setDateDlg.m_InitData.iItem2Data;
              m_sTime.wDay = setDateDlg.m_InitData.iItem3Data;

              CMzString str(128);
              wsprintf(str.C_Str(), L"%2d-%02d-%02d", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
              aga_DateBtn.SetText(str.C_Str());
			  PreciseToVague();
		  }

          break;   
      }

	case MZ_AGA_TIME_ADD:
      {
		  MzSetDaily setTimeDlg;
          setTimeDlg.m_InitData.iItemCounter = 2;
          setTimeDlg.m_InitData.iItem1Max = 24; 
          setTimeDlg.m_InitData.iItem2Max = 60;
          
          // 设置对话框初始显示日期的项index，index值从0开始
		  setTimeDlg.m_InitData.iItem1Data = m_sTime.wHour;
		  setTimeDlg.m_InitData.iItem2Data = m_sTime.wMinute;
        

          setTimeDlg.m_InitData.sItem1 = L"时";
          setTimeDlg.m_InitData.sItem2 = L"分";
          setTimeDlg.m_InitData.iItem1Width = setTimeDlg.m_InitData.iItem2Width = 210;
          setTimeDlg.EnableDisplayYearData(false);     //这样才能显示0时0分
          setTimeDlg.SetEnableChangeItemData(false);

          // 创建日期设置对话框的窗口
          RECT rcWorkDate = MzGetWorkArea();
          setTimeDlg.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // 设置窗口淡出的动画效果
          setTimeDlg.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setTimeDlg.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // 如果对话框点击“确定”，显示对话框设置的日期
          if (ID_OK == setTimeDlg.DoModal())
          {
			  m_sTime.wHour = setTimeDlg.m_InitData.iItem1Data;
			  m_sTime.wMinute = setTimeDlg.m_InitData.iItem2Data;

              CMzString str(128);
			  wsprintf(str.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
              aga_TimeBtn.SetText(str.C_Str());
			  PreciseToVague_1();
		  }

          break;   
      }

	case MZ_AGA_WEEKTH_ADD:
		{
			MzPopupMenu weekthPopupMenu;
			weekthPopupMenu.SetMenuTitle(L"设置周次");
			weekthPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"本周");
			weekthPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"下周");
            weekthPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"下下周");

			int result = weekthPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					aga_WeekThBtn.SetText(L"本周");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					aga_WeekThBtn.SetText(L"下周");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					aga_WeekThBtn.SetText(L"下下周");
					break;
				}
			}
			VagueToPrecise();                             //更新数据!
			break;
		}

	case MZ_AGA_WEEK_ADD:
		{
			MzPopupMenu weekPopupMenu;
			weekPopupMenu.SetMenuTitle(L"设置星期");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"星期一");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"星期二");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"星期三");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 4, L"星期四");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 5, L"星期五");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 6, L"星期六");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 7, L"星期日");

			int result = weekPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					aga_WeekBtn.SetText(L"星期一");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					aga_WeekBtn.SetText(L"星期二");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					aga_WeekBtn.SetText(L"星期三");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					aga_WeekBtn.SetText(L"星期四");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					aga_WeekBtn.SetText(L"星期五");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					aga_WeekBtn.SetText(L"星期六");
					break;
				}
			case MZV2_MID_MIN + 7:
				{
					aga_WeekBtn.SetText(L"星期日");
					break;
				}
			}
			VagueToPrecise();                             //更新数据!
			break;
		}
	case MZ_AGA_AMPM_ADD:
		{
			MzPopupMenu ampmPopupMenu;
			ampmPopupMenu.SetMenuTitle(L"设置时间段");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"早晨");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"上午");
            ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"中午");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 4, L"下午");
            ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 5, L"晚上");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 6, L"深夜");

			int result = ampmPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					aga_AmPmBtn.SetText(L"早晨");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					aga_AmPmBtn.SetText(L"上午");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					aga_AmPmBtn.SetText(L"中午");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					aga_AmPmBtn.SetText(L"下午");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					aga_AmPmBtn.SetText(L"晚上");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					aga_AmPmBtn.SetText(L"深夜");
					break;
				}
			}
			//VagueToPrecise();                             //更新数据!
			VagueToPrecise_1();
			break;
		}

	case MZ_AGA_BOTTOM_ADD:
		{
			int index=lParam;
			if(1==index)
			{
				if (aga_GridMenu.IsContinue())
                {
                    aga_GridMenu.EndGridMenu();
                }
				else 
				{
					if(!(this->aga_aga.GetText().IsEmpty()))
					{
						CMzString configure;
						wsprintf(configure.C_Str(),L"你确定要添加 <%s> ?",this->aga_aga.GetText().C_Str());
						if(1 == MzMessageBoxEx(m_hWnd, configure, L"确认", MB_YESNO, false))
						{
							AddOneRemind();				
						}
					}
				}
			}
			if(0==index)
			{
				if (aga_GridMenu.IsContinue())
                {
                    aga_GridMenu.EndGridMenu();
                }
				else
				{
					EndModal(MZ_AGA_BOTTOM_ADD);
				}
			}
			if(2==index)
			{
				if (aga_GridMenu.IsContinue())
                {
                    aga_GridMenu.EndGridMenu();
                }
                else
                {
					this->aga_aga.SetFocus(false);
                    aga_GridMenu.TrackGridMenuDialog(m_hWnd, MZM_HEIGHT_TOOLBARPRO);
                }
			}
			break;
		}
		case MZ_AGA_GRIDMENU_ITEM11:
			{
                CppSQLite3DB db;
				db.open(L"Schedule.db"); 
				CMzString szsql(200);  
				wsprintf(szsql.C_Str(),L"%s%s%s",L"delete from thing where bigthing ='",aga_List_big.GetItem((aga_List_big.GetSelectedIndex()))->Text.C_Str(),L"';");
				db.execDML(szsql); 
				aga_List_big.RemoveAll();
				aga_List_small.RemoveAll();  
				ListItem big_thing;
				CppSQLite3Query *pQuery;
				CMzString sql(200);
				db.open(L"Schedule.db"); 
				if(db.tableExists(L"thing"))
				{
					wsprintf(sql.C_Str(),L"%s",L"select distinct bigthing from thing;");
					pQuery=db.execQuery(sql);
					while(!(pQuery->eof()))
					{              
						//  
						
						big_thing.Text=pQuery->fieldValue(L"bigthing");
						aga_List_big.AddItem(big_thing);
						pQuery->nextRow();
					}
				}
				pQuery->finalize();
				db.close();
				aga_List_big.Invalidate();
		        aga_List_big.Update();

				if(aga_List_big.GetItemCount())
				{     
					aga_List_big.SetSelectedIndex(0);  
					big_thing_now=aga_List_big.GetItem(0)->Text;   
					ListItem small_thing;
					db.open(L"Schedule.db"); 		
					if(db.tableExists(L"thing"))
					{
						wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'主事件';");
						pQuery=db.execQuery(sql);
						while(!(pQuery->eof()))
						{              
							//MzMessageBoxEx(m_hWnd, sql, L"提醒");
							small_thing.Text=pQuery->fieldValue(L"smallthing");
							aga_List_small.AddItem(small_thing);
							pQuery->nextRow();
						}
						pQuery->finalize();
					}
					db.close();
					aga_List_small.Invalidate();
				  aga_List_small.Update();
				}
				else
				{
					aga_List_small.RemoveAll();
					aga_List_small.Invalidate();
				    aga_List_small.Update();

				}

                break;
            }
        case MZ_AGA_GRIDMENU_ITEM22:
            {
                CppSQLite3DB db;
				db.open(L"Schedule.db"); 
				CMzString szsql(200);  
				wsprintf(szsql.C_Str(),L"%s%s%s%s%s",L"delete from thing where bigthing ='",big_thing_now.C_Str(),L"' and smallthing ='",aga_List_small.GetItem(aga_List_small.GetSelectedIndex())->Text.C_Str(),L"';");
				db.execDML(szsql);    
				aga_List_small.RemoveAll();
				ListItem small_thing;
				CppSQLite3Query *pQuery;
				CMzString sql(200);
				if(db.tableExists(L"thing"))
				{
					wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'主事件';");
					pQuery=db.execQuery(sql); 
					while(!(pQuery->eof()))
					{              
				//		MzMessageBoxEx(m_hWnd, sql, L"提醒");
						small_thing.Text=pQuery->fieldValue(L"smallthing");
						aga_List_small.AddItem(small_thing);
						pQuery->nextRow();
					}
				}
				pQuery->finalize();
				db.close();
				aga_List_small.Invalidate();
			    aga_List_small.Update();

                break;
            }
        case MZ_AGA_GRIDMENU_ITEM33:              //待改动
            {
                AddBigThing addbigthing;
				RECT rcWork = MzGetWorkArea();
				addbigthing.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
				addbigthing.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
				addbigthing.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
				addbigthing.DoModal();
				aga_List_big.RemoveAll();
				ListItem big_thing;
				CppSQLite3DB db;
				CppSQLite3Query *pQuery;
				CMzString sql(200);
				db.open(L"Schedule.db"); 
				if(db.tableExists(L"thing"))
				{
					wsprintf(sql.C_Str(),L"%s",L"select distinct bigthing from thing;");
					pQuery=db.execQuery(sql);
					while(!(pQuery->eof()))
					{              
						//MzMessageBoxEx(m_hWnd, sql, L"提醒");
						big_thing.Text=pQuery->fieldValue(L"bigthing");
						aga_List_big.AddItem(big_thing);
						pQuery->nextRow();
					}
				}
				pQuery->finalize();
				db.close();
				aga_List_big.SetSelectedIndex(0);
				big_thing_now=aga_List_big.GetItem(0)->Text;
				aga_List_big.Invalidate();
			    aga_List_big.Update();

				ListItem small_thing;
				aga_List_small.RemoveAll();
				if(db.tableExists(L"thing"))
				{
					wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'主事件';");
					pQuery=db.execQuery(sql); 
					while(!(pQuery->eof()))
					{              
				//		MzMessageBoxEx(m_hWnd, sql, L"提醒");
						small_thing.Text=pQuery->fieldValue(L"smallthing");
						aga_List_small.AddItem(small_thing);
						pQuery->nextRow();
					}
				}
				pQuery->finalize();
				db.close();
				aga_List_small.Invalidate();
			    aga_List_small.Update();

                break;
                                          }
        case MZ_AGA_GRIDMENU_ITEM44:
            {
                AddSmallThing addsmallthing;
				RECT rcWork = MzGetWorkArea();
				addsmallthing.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
				addsmallthing.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
				addsmallthing.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
				addsmallthing.DoModal();
				aga_List_small.RemoveAll();
				ListItem small_thing;
				CppSQLite3DB db;
				CppSQLite3Query *pQuery;
				CMzString sql(200);
				db.open(L"Schedule.db"); 
			
				if(db.tableExists(L"thing"))
				{
					wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'主事件';");
					pQuery=db.execQuery(sql);
					while(!(pQuery->eof()))
					{              
						//MzMessageBoxEx(m_hWnd, sql, L"提醒");
						small_thing.Text=pQuery->fieldValue(L"smallthing");
						aga_List_small.AddItem(small_thing);
						pQuery->nextRow();
					}
				}
				pQuery->finalize();
				db.close();
				aga_List_small.Invalidate();
			    aga_List_small.Update();

                break;
            }
		

      
	}
  }

  void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
  {
	  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
      {
		  this->aga_aga.SetFocus(false);
          if (aga_GridMenu.IsContinue())
          {
              aga_GridMenu.EndGridMenu();
          }
      }
  }


  LRESULT MzDefWndProc(UINT message, WPARAM wParam, LPARAM lParam)
  {
    switch(message)
    {
    case MZ_WM_MOUSE_NOTIFY:
      {
        int nID = LOWORD(wParam);
        int nNotify = HIWORD(wParam);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (nID==MZ_AGA_LIST_1 && nNotify==MZ_MN_LBUTTONDOWN)
        {
          if (!aga_List_big.IsMouseDownAtScrolling() && !aga_List_big.IsMouseMoved())
          {
            int nIndex = aga_List_big.CalcIndexOfPos(x, y);
            aga_List_big.SetSelectedIndex(nIndex);
			big_thing_now=aga_List_big.GetItem(nIndex)->Text;
            aga_List_big.Invalidate();
            aga_List_big.Update();
			this->aga_aga.SetText(aga_List_big.GetItem(nIndex)->Text);
			aga_aga.Invalidate();
			aga_aga.Update();

			aga_List_small.RemoveAll();
			
			ListItem small_thing;
			CppSQLite3DB db;
			CppSQLite3Query *pQuery;
			CMzString sql(200);
			db.open(L"Schedule.db"); 
			
			if(db.tableExists(L"thing"))
			{
				wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'主事件';");
				pQuery=db.execQuery(sql);
				while(!(pQuery->eof()))
				{              
					//MzMessageBoxEx(m_hWnd, sql, L"提醒");
					small_thing.Text=pQuery->fieldValue(L"smallthing");
					aga_List_small.AddItem(small_thing);
					pQuery->nextRow();
				}
			}
			pQuery->finalize();
			db.close();
			aga_List_small.Invalidate();
            aga_List_small.Update();
		  }
          return 0;
        }
        if (nID==MZ_AGA_LIST_1 && nNotify==MZ_MN_MOUSEMOVE)
        {
			if(aga_List_big.GetSelectedIndex()!=-1)
            {
				aga_List_big.SetSelectedIndex(-1);
                aga_List_big.Invalidate();
                aga_List_big.Update();
            }
          return 0;
        } 
       
		if (nID==MZ_AGA_LIST_2 && nNotify==MZ_MN_LBUTTONDOWN)
        {
          if (!aga_List_small.IsMouseDownAtScrolling() && !aga_List_small.IsMouseMoved())
          {
            int nIndex = aga_List_small.CalcIndexOfPos(x, y);
            aga_List_small.SetSelectedIndex(nIndex);
            aga_List_small.Invalidate();
            aga_List_small.Update();
			this->aga_aga.SetText(aga_List_small.GetItem(nIndex)->Text);
			aga_aga.Invalidate();
			aga_aga.Update();
          }
          return 0;
        }
        if (nID==MZ_AGA_LIST_2 && nNotify==MZ_MN_MOUSEMOVE)
        {
			if(aga_List_small.GetSelectedIndex()!=-1)
            {
				aga_List_small.SetSelectedIndex(-1);
                aga_List_small.Invalidate();
                aga_List_small.Update();
            }
          return 0;
        }       
      }
      return 0;
    }
    return CMzWndEx::MzDefWndProc(message,wParam,lParam);
  }
  
public:
	void AddOneRemind()
	{
		if(!this->aga_aga.GetText().IsEmpty())
		{
			CppSQLite3DB db;
		    db.open(L"Schedule.db"); 
		    if(!db.tableExists(L"agenda"))
		    {
			    db.execDML(L"create table agenda (date_time char(50),week_time char(50),vague_time char(10),remind char(100));");
		    }

			CMzString date_time(50),vague; 
			if(this->isVague==false)
			{
				wsprintf(date_time.C_Str(),L"%s %s",this->aga_DateBtn.GetText().C_Str(),this->aga_TimeBtn.GetText().C_Str());
			}
			else
			{
					if(aga_AmPmBtn.GetText()==L"早晨")
					{
						vague=L"07:00";
					}
					else if(aga_AmPmBtn.GetText()==L"上午")
					{
						vague=L"10:00";
					}
					else if(aga_AmPmBtn.GetText()==L"中午")
					{
						vague=L"12:00";
					}
					else if(aga_AmPmBtn.GetText()==L"下午")
					{
						vague=L"15:00";
					}
					else if(aga_AmPmBtn.GetText()==L"晚上")
					{
						vague=L"19:00";
					}
					else if(aga_AmPmBtn.GetText()==L"深夜")
					{
						vague=L"22:00";
					}
					wsprintf(date_time.C_Str(),L"%s %s",this->aga_DateBtn.GetText().C_Str(),vague.C_Str());
			//		MzMessageBoxEx(m_hWnd, date_time, L"提醒");
			}

		    CMzString week_time(50);
			if(this->aga_WeekThBtn.GetText()==L"本周之前")
			{
				week_time=L"本周之前";
			}
			else if(this->aga_WeekThBtn.GetText()==L"下下周后")
			{
				week_time=L"下下周后";
			}
			else if(this->aga_WeekThBtn.GetText()==L"本周")
			{
				wsprintf(week_time.C_Str(),L"周%s",this->aga_WeekBtn.GetText().SubStr(2,1).C_Str());
			}
			else
			{
				wsprintf(week_time.C_Str(),L"%s%s",this->aga_WeekThBtn.GetText().C_Str(),this->aga_WeekBtn.GetText().SubStr(2,1).C_Str());
			}

			

			CMzString vague_time(10);
			if(isVague)
			{
				vague_time=this->aga_AmPmBtn.GetText();
			}
			else
			{
				vague_time=date_time.SubStr(11,5);
			}			

			CMzString szsql(200);
			wsprintf(szsql.C_Str(),L"insert into agenda values ('%s','%s','%s','%s');",date_time.C_Str(),week_time.C_Str(),vague_time.C_Str(),this->aga_aga.GetText().C_Str());
		    db.execDML(szsql);
		    db.close();
		}
	}



	void PreciseToVague()
	{
		CppSQLite3DB db;
 		CppSQLite3Query *pQuery;
		db.open(L"Schedule.db");
		CMzString date_today=M8Date::DateToday();
	    CMzString sql(200);
		wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");
		pQuery=db.execQuery(sql);
		CMzString week_temp=pQuery->fieldValue(L"week");  
		int weekth_today=_ttoi(week_temp);

		CMzString date_thatday(40),year_temp(20),month_temp(10),day_temp(10);
		date_thatday=this->aga_DateBtn.GetText();
		year_temp=date_thatday.SubStr(0,4);
		month_temp=date_thatday.SubStr(5,2);
		day_temp=date_thatday.SubStr(8,2); 
		wsprintf(date_thatday.C_Str(),L"%s%s%s",year_temp.C_Str(),month_temp.C_Str(),day_temp.C_Str());
		wsprintf(sql.C_Str(),L"%s%s%s",L"select * from schedule where date='",date_thatday.C_Str(),L"';");
		pQuery=db.execQuery(sql);
		CMzString weekth_thatday_s=pQuery->fieldValue(L"week");
		CMzString dayweek_thatday_s=pQuery->fieldValue(L"dayweek"); 
		int weekth_thatday=_ttoi(weekth_thatday_s);
		int dayweek_thatday=_ttoi(dayweek_thatday_s);
		if(weekth_thatday==0)
		{
			weekth_thatday=100;
		}

		if(weekth_thatday<weekth_today)
		{
			this->aga_WeekThBtn.SetText(L"本周之前");
		}
		else if(weekth_thatday==weekth_today)
		{
			this->aga_WeekThBtn.SetText(L"本周");
		}
		else if(weekth_thatday==(weekth_today+1))
		{
			this->aga_WeekThBtn.SetText(L"下周");
		}
		else if(weekth_thatday==(weekth_today+2))
		{
			this->aga_WeekThBtn.SetText(L"下下周");
		}
		else
		{
			this->aga_WeekThBtn.SetText(L"下下周后");
		}

		if(dayweek_thatday==1)
		{
			this->aga_WeekBtn.SetText(L"星期一");
		}
		else if(dayweek_thatday==2)
		{
			this->aga_WeekBtn.SetText(L"星期二");
		}
		else if(dayweek_thatday==3)
		{
			this->aga_WeekBtn.SetText(L"星期三");
		}
		else if(dayweek_thatday==4)
		{
			this->aga_WeekBtn.SetText(L"星期四");
		}
		else if(dayweek_thatday==5)
		{
			this->aga_WeekBtn.SetText(L"星期五");
		}
		else if(dayweek_thatday==6)
		{
			this->aga_WeekBtn.SetText(L"星期六");
		}
		else if(dayweek_thatday==7)
		{
			this->aga_WeekBtn.SetText(L"星期日");
		}
	}

	void PreciseToVague_1()
	{
		this->aga_AmPmBtn.SetText(L"同上");
		isVague=false;
	}

	void VagueToPrecise_1()
	{
		CMzString vague(20);
		vague=this->aga_AmPmBtn.GetText();
		if(vague==L"早晨")
		{
			this->aga_TimeBtn.SetText(L"07:00");
		}
		else if(vague==L"上午")
		{
			this->aga_TimeBtn.SetText(L"10:00");
		}
		else if(vague==L"中午")
		{
			this->aga_TimeBtn.SetText(L"12:00");
		}
		else if(vague==L"下午")
		{
			this->aga_TimeBtn.SetText(L"15:00");
		}
		else if(vague==L"晚上")
		{
			this->aga_TimeBtn.SetText(L"19:00");
		}
		else if(vague==L"深夜")
		{
			this->aga_TimeBtn.SetText(L"22:00");
		}
		isVague=true;
	}

	void VagueToPrecise()
	{
		CppSQLite3DB db;
 		CppSQLite3Query *pQuery;
		db.open(L"Schedule.db");
		CMzString date_today=M8Date::DateToday();     //奇幻！！！！！！！！！！！！！！！！
		date_today=date_today.SubStr(0,date_today.Length());
//		date_today=L"20101015";
//		MzMessageBoxEx(m_hWnd, date_today, L"提醒");
	    CMzString sql(200);
		wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");
		pQuery=db.execQuery(sql);
		CMzString week_temp=pQuery->fieldValue(L"week");  
		int weekth_today=_ttoi(week_temp);
		CMzString dayweek_btn(20);
		dayweek_btn=this->aga_WeekBtn.GetText();
		int dayweek;
		if(dayweek_btn==L"星期一")
		{
			dayweek=1;
		}
		else if(dayweek_btn==L"星期二")
		{
			dayweek=2;
		}
		else if(dayweek_btn==L"星期三")
		{
			dayweek=3;
		}
		else if(dayweek_btn==L"星期四")
		{
			dayweek=4;
		}
		else if(dayweek_btn==L"星期五")
		{
			dayweek=5;
		}
		else if(dayweek_btn==L"星期六")
		{
			dayweek=6;
		}
		else if(dayweek_btn==L"星期日")
		{
			dayweek=7;
		}

		CMzString weekth_btn(20);
		weekth_btn=this->aga_WeekThBtn.GetText();
		if(weekth_btn==L"本周")
		{
			weekth_today=weekth_today+0;
		}
		else if(weekth_btn==L"下周")
		{
			weekth_today=weekth_today+1;
		}

		else if(weekth_btn==L"下下周")
		{
			weekth_today=weekth_today+2;
		}
		wsprintf(sql.C_Str(),L"%s%d%s%d%s",L"select * from schedule where week='",weekth_today,L"'and dayweek=",dayweek,L";");
		pQuery=db.execQuery(sql);    
//		MzMessageBoxEx(m_hWnd, sql, L"提醒");
		date_today=pQuery->fieldValue(L"date");
		CMzString year_temp(20),month_temp(10),day_temp(10);
		year_temp=date_today.SubStr(0,4);
		month_temp=date_today.SubStr(4,2);
		day_temp=date_today.SubStr(6,2);
		wsprintf(date_today.C_Str(),L"%s%s%s%s%s",year_temp.C_Str(),L"-",month_temp.C_Str(),L"-",day_temp.C_Str());
		

		pQuery->finalize();
		db.close();
		this->aga_DateBtn.SetText(date_today);


	}
};

MZ_IMPLEMENT_DYNAMIC(AddRemind)