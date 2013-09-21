#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <Sqlite/CppSQLite3U.h>
#include "define.h"





//三个全局变量,用来记录星期几,开始时间与结束时间
CMzString sls_timeB(20);
CMzString sls_timeE(20);
CMzString sls_week(20);

// 从 CMzWndEx 派生的主窗口类
class AddIntervalWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AddIntervalWnd);
public:
  // 窗口中的按钮控件
  UiCaption AddInterval;
  UiButton sls_Time_Begin;
  UiButton sls_Time_End;
  UiButton sls_WeekBtn;
  UiToolbar_Text sls_bottom_add;
  UiStatic sls_addMsg[2];
  UiButton sls_Line[3];


  SYSTEMTIME m_sTime;


protected:
  // 窗口的初始化
  virtual BOOL OnInitDialog()
  {
    // 必须先调用基类的初始化
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }
	GetLocalTime(&m_sTime);


    CMzString str(128);

              // 初始化窗口中的控件
	AddInterval.SetPos(0,0,480,50);
	AddInterval.SetText(L"添加静音区间");
	AddUiWin(&AddInterval);

	sls_addMsg[0].SetPos(0,190,240,100);
	sls_addMsg[0].SetText(L"开始时间：");
	AddUiWin(&sls_addMsg[0]);

	sls_addMsg[1].SetPos(0,290,240,100);
	sls_addMsg[1].SetText(L"结束时间：");
	AddUiWin(&sls_addMsg[1]);

	sls_Line[0].SetPos(0,190,480,3);
	sls_Line[0].SetButtonType(MZC_BUTTON_LINE_TOP);
	AddUiWin(&sls_Line[0]);

	sls_Line[1].SetPos(0,290,480,3);
	sls_Line[1].SetButtonType(MZC_BUTTON_LINE_TOP);
	AddUiWin(&sls_Line[1]);

	sls_Line[2].SetPos(0,390,480,3);
	sls_Line[2].SetButtonType(MZC_BUTTON_LINE_TOP);
	AddUiWin(&sls_Line[2]);


	sls_bottom_add.SetPos(0,GetHeight()-70,GetWidth(),70);
    sls_bottom_add.SetButton(0, true, true, L"返回");
    sls_bottom_add.SetButton(1, true, true, L"保存");
    sls_bottom_add.SetButton(2, true, true, L"选项");
    sls_bottom_add.SetID(MZ_SLS_BOTTOM_ADD);
    AddUiWin(&sls_bottom_add);

	sls_WeekBtn.SetButtonType(MZC_BUTTON_GRAY);
    sls_WeekBtn.SetID(MZ_SLS_WEEK);
    sls_WeekBtn.SetPos(100, 70, 280, 100);
    sls_WeekBtn.SetText(sls_week);          //待修改~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sls_WeekBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&sls_WeekBtn);

	sls_Time_Begin.SetButtonType(MZC_BUTTON_GRAY);
    sls_Time_Begin.SetID(MZ_SLS_BEGIN);
    sls_Time_Begin.SetPos(240, 190, 200, 100);
	wsprintf(str.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
	sls_timeB=str;
    sls_Time_Begin.SetText(str.C_Str());
    sls_Time_Begin.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&sls_Time_Begin);

	sls_Time_End.SetButtonType(MZC_BUTTON_GRAY);
    sls_Time_End.SetID(MZ_SLS_END);
    sls_Time_End.SetPos(240, 290, 200, 100);
	wsprintf(str.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
	sls_timeE=str;
    sls_Time_End.SetText(str.C_Str());
    sls_Time_End.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&sls_Time_End);
    

              // 把控件添加到窗口中
 

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	case MZ_SLS_BOTTOM_ADD:
		{
			int index=lParam;
			if(0==index)
			{
				EndModal(MZ_SLS_BOTTOM_ADD);
			}
			else if(1==index)
			{
				AddOneInterval();
				EndModal(MZ_SLS_BOTTOM_ADD);
			}
			break;
		}
    case MZ_SLS_BEGIN:
      {
		  MzSetDaily setTimeDlg_Begin;
          setTimeDlg_Begin.m_InitData.iItemCounter = 2;
          setTimeDlg_Begin.m_InitData.iItem1Max = 24; 
          setTimeDlg_Begin.m_InitData.iItem2Max = 60;
          
          // 设置对话框初始显示日期的项index，index值从0开始
		  setTimeDlg_Begin.m_InitData.iItem1Data = m_sTime.wHour;
		  setTimeDlg_Begin.m_InitData.iItem2Data = m_sTime.wMinute;
        

          setTimeDlg_Begin.m_InitData.sItem1 = L"时";
          setTimeDlg_Begin.m_InitData.sItem2 = L"分";
          setTimeDlg_Begin.m_InitData.iItem1Width = setTimeDlg_Begin.m_InitData.iItem2Width = 210;
          setTimeDlg_Begin.EnableDisplayYearData(false);     //这样才能显示0时0分
          setTimeDlg_Begin.SetEnableChangeItemData(false);

          // 创建日期设置对话框的窗口
          RECT rcWorkDate = MzGetWorkArea();
          setTimeDlg_Begin.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // 设置窗口淡出的动画效果
          setTimeDlg_Begin.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setTimeDlg_Begin.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // 如果对话框点击“确定”，显示对话框设置的日期
          if (ID_OK == setTimeDlg_Begin.DoModal())
          {
			  m_sTime.wHour = setTimeDlg_Begin.m_InitData.iItem1Data;
			  m_sTime.wMinute = setTimeDlg_Begin.m_InitData.iItem2Data;

//              CMzString str(128);
//			  wsprintf(str.C_Str(), L"%d时%d分", m_sTime.wHour, m_sTime.wMinute);
			  wsprintf(sls_timeB.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
//			  MzMessageBoxEx(m_hWnd, sls_timeB, L"提醒");
              sls_Time_Begin.SetText(sls_timeB.C_Str());
		  }

          break;   
      }
	case MZ_SLS_END:
      {
		  MzSetDaily setTimeDlg_End;
          setTimeDlg_End.m_InitData.iItemCounter = 2;
          setTimeDlg_End.m_InitData.iItem1Max = 24; 
          setTimeDlg_End.m_InitData.iItem2Max = 60;
          
          // 设置对话框初始显示日期的项index，index值从0开始
		  setTimeDlg_End.m_InitData.iItem1Data = m_sTime.wHour;
		  setTimeDlg_End.m_InitData.iItem2Data = m_sTime.wMinute;
        

          setTimeDlg_End.m_InitData.sItem1 = L"时";
          setTimeDlg_End.m_InitData.sItem2 = L"分";
          setTimeDlg_End.m_InitData.iItem1Width = setTimeDlg_End.m_InitData.iItem2Width = 210;
          setTimeDlg_End.EnableDisplayYearData(false);     //这样才能显示0时0分
          setTimeDlg_End.SetEnableChangeItemData(false);

          // 创建日期设置对话框的窗口
          RECT rcWorkDate = MzGetWorkArea();
          setTimeDlg_End.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // 设置窗口淡出的动画效果
          setTimeDlg_End.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setTimeDlg_End.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // 如果对话框点击“确定”，显示对话框设置的日期
          if (ID_OK == setTimeDlg_End.DoModal())
          {
			  m_sTime.wHour = setTimeDlg_End.m_InitData.iItem1Data;
			  m_sTime.wMinute = setTimeDlg_End.m_InitData.iItem2Data;

//              CMzString str(128);
//			  wsprintf(str.C_Str(), L"%d时%d分", m_sTime.wHour, m_sTime.wMinute);
			  wsprintf(sls_timeE.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
//			  MzMessageBoxEx(m_hWnd, sls_timeE, L"提醒");
              sls_Time_End.SetText(sls_timeE.C_Str());
		  }

          break;   
      }
    case MZ_SLS_WEEK:
		{
			MzPopupMenu weekPopupMenu;
			weekPopupMenu.SetMenuTitle(L"设置星期");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"星期一");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"星期二");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"星期三");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 4, L"星期四");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 5, L"星期五");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 6, L"星期六");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 7, L"星期天");

			int result = weekPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					sls_WeekBtn.SetText(L"星期一");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					sls_WeekBtn.SetText(L"星期二");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					sls_WeekBtn.SetText(L"星期三");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					sls_WeekBtn.SetText(L"星期四");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					sls_WeekBtn.SetText(L"星期五");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					sls_WeekBtn.SetText(L"星期六");
					break;
				}
			case MZV2_MID_MIN + 7:
				{
					sls_WeekBtn.SetText(L"星期天");
					break;
				}
			}
			sls_week=sls_WeekBtn.GetText();
		//	MzMessageBoxEx(m_hWnd, sls_week, L"提醒");
			break;
		}

	}
  }



public:
	void AddOneInterval()
	{
		if(!(this->sls_Time_Begin.GetText()==this->sls_Time_End.GetText()))
		{
			CppSQLite3DB db;
		    db.open(L"Schedule.db"); 
		    if(!db.tableExists(L"silenceset"))
		    {
			    db.execDML(L"create table silenceset (dayweek char(20),begintime char(20),endtime char(20));");
		    }
		    CMzString szsql(200);
			wsprintf(szsql.C_Str(),L"%s'%s','%s','%s'%s",L"insert into silenceset values (",sls_week.C_Str(),sls_timeB.C_Str(),sls_timeE.C_Str(),L");");
		    db.execDML(szsql);
//			MzMessageBoxEx(m_hWnd, szsql, L"提醒");


		    db.close();
		}
	
	}





};

MZ_IMPLEMENT_DYNAMIC(AddIntervalWnd)






// 从 CMzWndEx 派生的主窗口类
class SilenceWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(SilenceWnd);
public:
  UiToolbar_Text sls_bottom;
  UiList_2 sls_List_1;
  UiList sls_List_2;
  UiCaption sls_caption_1,sls_caption_2;
  UiButton  sls_Line_1,sls_Line_2;
  UiStatic sls_Static;


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
	sls_caption_1.SetPos(0,0,200,44);
	sls_caption_1.SetText(L"星期");
	AddUiWin(&sls_caption_1);
	sls_caption_2.SetPos(200,0,280,44);
	sls_caption_2.SetText(L"静音区间");
	AddUiWin(&sls_caption_2);

	sls_Line_1.SetPos(5,44,200,485);
	sls_Line_1.SetButtonType(MZC_BUTTON_LINE_RIGHT);
	AddUiWin(&sls_Line_1);

	sls_Line_2.SetPos(0,42+70*7,480,4);
	sls_Line_2.SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&sls_Line_2);

	sls_Static.SetPos(0,42+70*7,480,80);
	sls_Static.SetTextColor( RGB(165 ,42, 42 ));
	sls_Static.SetText(L"请添加静音区间");
	SilenceCount();
	SetTimer(m_hWnd, 1, 500, NULL);
	AddUiWin(&sls_Static);

    sls_List_1.SetPos(0,44,200,490);
    sls_List_1.SetID(MZ_SLS_LIST_1);
	sls_List_1.SetItemHeight(70);
	
    sls_List_1.EnableScrollBarV(false);
    sls_List_1.EnableNotifyMessage(true);
    AddUiWin(&sls_List_1);

	sls_List_2.SetPos(207,44,275,490);
    sls_List_2.SetID(MZ_SLS_LIST_2);
	sls_List_2.SetItemHeight(70);
    sls_List_2.EnableScrollBarV(false);
    sls_List_2.EnableNotifyMessage(true);
    AddUiWin(&sls_List_2);

    // 往列表控件添加项
    ListItem dayweek;
	dayweek.Text=L"星期一";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"星期二";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"星期三";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"星期四";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"星期五";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"星期六";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"星期天";
	sls_List_1.AddItem(dayweek);

	SYSTEMTIME m_sTime;
	GetLocalTime(&m_sTime);

	if(m_sTime.wDayOfWeek==0)	
	{
		sls_List_1.SetSelectedIndex(6);
	}
	else
	{
		sls_List_1.SetSelectedIndex(m_sTime.wDayOfWeek-1);
	}
	sls_week=sls_List_1.GetItem(sls_List_1.GetSelectedIndex())->Text;

	ListItem interval;
	CppSQLite3DB db;
	CppSQLite3Query *pQuery;
	CMzString sql(200);
	CMzString begin(20),end(20),time_interval(50);
	db.open(L"Schedule.db"); 		
	if(db.tableExists(L"silenceset"))
	{
		wsprintf(sql.C_Str(),L"%s%s%s",L"select * from silenceset where dayweek='",sls_week.C_Str(),L"' order by begintime;");
		pQuery=db.execQuery(sql);
		while(!(pQuery->eof()))
		{              
			//MzMessageBoxEx(m_hWnd, sql, L"提醒");
			begin=pQuery->fieldValue(L"begintime");
			end=pQuery->fieldValue(L"endtime");
			wsprintf(time_interval.C_Str(),L"%s%s%s",begin.C_Str(),L" - ",end.C_Str());
					
			interval.Text=time_interval;
			sls_List_2.AddItem(interval);
			pQuery->nextRow();
		}
		pQuery->finalize();
	}
	db.close();
	sls_List_2.Invalidate();
    sls_List_2.Update();
	 

    sls_bottom.SetPos(0,GetHeight()-70,GetWidth(),70);
	sls_bottom.EnableLeftArrow(true);
    sls_bottom.SetButton(0, true, true, L"返回");
    sls_bottom.SetButton(1, true, true, L"添加");
    sls_bottom.SetButton(2, true, true, L"删除");
    sls_bottom.SetID(MZ_SLS_BOTTOM);
    AddUiWin(&sls_bottom);


    return TRUE;
  }

  // 重载 MZFC 的消息处理函数
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
        if (nID==MZ_SLS_LIST_1 && nNotify==MZ_MN_LBUTTONDOWN)
        {
          if (!sls_List_1.IsMouseDownAtScrolling() && !sls_List_1.IsMouseMoved())
          {
            int nIndex = sls_List_1.CalcIndexOfPos(x, y);
            sls_List_1.SetSelectedIndex(nIndex);
			switch(nIndex)
			{
			case 0:
				sls_week=L"星期一";
					break;
			case 1:
				sls_week=L"星期二";
					break;
			case 2:
				sls_week=L"星期三";
					break;
			case 3:
				sls_week=L"星期四";
					break;
			case 4:
				sls_week=L"星期五";
					break;
			case 5:
				sls_week=L"星期六";
					break;
			case 6:
				sls_week=L"星期天";
					break;
			}
            sls_List_1.Invalidate();
            sls_List_1.Update();
			sls_List_2.RemoveAll();
			
			ListItem interval;
			CppSQLite3DB db;
			CppSQLite3Query *pQuery;
			CMzString sql(200);
			CMzString begin(20),end(20),time_interval(50);
			db.open(L"Schedule.db"); 
			
			if(db.tableExists(L"silenceset"))
			{
				wsprintf(sql.C_Str(),L"%s%s%s",L"select * from silenceset where dayweek='",sls_week.C_Str(),L"' order by begintime;");
				pQuery=db.execQuery(sql);
				while(!(pQuery->eof()))
				{              
					//MzMessageBoxEx(m_hWnd, sql, L"提醒");
					begin=pQuery->fieldValue(L"begintime");
					end=pQuery->fieldValue(L"endtime");
					wsprintf(time_interval.C_Str(),L"%s%s%s",begin.C_Str(),L" - ",end.C_Str());
					
					interval.Text=time_interval;
					sls_List_2.AddItem(interval);
					pQuery->nextRow();
				}
			}
			pQuery->finalize();
			db.close();
			sls_List_2.Invalidate();
            sls_List_2.Update();
          }
          return 0;
        }
      
       
		if (nID==MZ_SLS_LIST_2 && nNotify==MZ_MN_LBUTTONDOWN)
        {
          if (!sls_List_2.IsMouseDownAtScrolling() && !sls_List_2.IsMouseMoved())
          {
            int nIndex = sls_List_2.CalcIndexOfPos(x, y);
            sls_List_2.SetSelectedIndex(nIndex);
            sls_List_2.Invalidate();
            sls_List_2.Update();
          }
          return 0;
        }
        if (nID==MZ_SLS_LIST_2 && nNotify==MZ_MN_MOUSEMOVE)
        {
			if(sls_List_2.GetSelectedIndex()!=-1)
            {
				sls_List_2.SetSelectedIndex(-1);
                sls_List_2.Invalidate();
                sls_List_2.Update();
            }
          return 0;
        }       
      }
      return 0;
    }
    return CMzWndEx::MzDefWndProc(message,wParam,lParam);
  }

  // 重载 MZFC 的命令消息处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_SLS_BOTTOM:
      {
        int nIndex = lParam;
        if (nIndex==0)
        {
          EndModal(MZ_SLS_BOTTOM);
          return;
        }
        if (nIndex==1)
        {
			AddIntervalWnd addinterval;
			RECT rcWork = MzGetWorkArea();
			addinterval.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
			addinterval.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
			addinterval.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			addinterval.DoModal();

			sls_List_2.RemoveAll();
			ListItem interval;
			CppSQLite3DB db;
			CppSQLite3Query *pQuery;
			CMzString sql(200);
			CMzString begin(20),end(20),time_interval(50);
			db.open(L"Schedule.db"); 
			
			if(db.tableExists(L"silenceset"))
			{
				wsprintf(sql.C_Str(),L"%s%s%s",L"select * from silenceset where dayweek='",sls_week.C_Str(),L"' order by begintime;");
				pQuery=db.execQuery(sql);
				while(!(pQuery->eof()))
				{              
					//MzMessageBoxEx(m_hWnd, sql, L"提醒");
					begin=pQuery->fieldValue(L"begintime");
					end=pQuery->fieldValue(L"endtime");
					wsprintf(time_interval.C_Str(),L"%s%s%s",begin.C_Str(),L" - ",end.C_Str());
					
					interval.Text=time_interval;
					sls_List_2.AddItem(interval);
					pQuery->nextRow();
				}
			}
			pQuery->finalize();
			db.close();
			sls_List_2.Invalidate();
            sls_List_2.Update();
			
			
		}
        if (nIndex==2)
        {
			
			DelOneInterval();
//			DelAllInterval();
          return;
        }
      }
      break;
    }
  }


  virtual void OnTimer(UINT_PTR nIDEvent)
	{
		if(nIDEvent==1)
		{
			SilenceCount();
			sls_Static.Invalidate();
			sls_Static.Update();
		}
	}
public:
	void DelAllInterval()
	{
		if(1 == MzMessageBoxEx(m_hWnd, L"真的要清空静音区间吗?", L"Exit", MB_YESNO, false))
			{
				CppSQLite3DB db;
				db.open(L"Schedule.db");                        //数据库名字后面不带";"
	            db.execDML(L"drop table silenceset");
				db.close();
				sls_List_2.RemoveAll();
			}
	}

	void DelOneInterval()
	{
		int nIndex=sls_List_2.GetSelectedIndex();
		CMzString val_time=sls_List_2.GetItem(nIndex)->Text;
		CMzString val_begin=val_time.SubStr(0,5);
		CMzString val_end=val_time.SubStr(8,5);
//		MzMessageBoxEx(m_hWnd, szsql, L"提醒");
		CppSQLite3DB db;
		db.open(L"Schedule.db"); 
		CMzString szsql(200);  
		wsprintf(szsql.C_Str(),L"%s%s%s%s%s",L"delete from silenceset where begintime ='",val_begin.C_Str(),L"' and endtime ='",val_end.C_Str(),L"';");
		db.execDML(szsql); 
		sls_List_2.RemoveAll();
		ListItem interval;
		CppSQLite3Query *pQuery;
		CMzString sql(200);
		CMzString begin(20),end(20),time_interval(50);
		db.open(L"Schedule.db"); 
			
		if(db.tableExists(L"silenceset"))
		{
			wsprintf(sql.C_Str(),L"%s%s%s",L"select * from silenceset where dayweek='",sls_week.C_Str(),L"' order by begintime;");
			pQuery=db.execQuery(sql);
			while(!(pQuery->eof()))
			{              
				//MzMessageBoxEx(m_hWnd, sql, L"提醒");
				begin=pQuery->fieldValue(L"begintime");
				end=pQuery->fieldValue(L"endtime");
				wsprintf(time_interval.C_Str(),L"%s%s%s",begin.C_Str(),L" - ",end.C_Str());
					
				interval.Text=time_interval;
				sls_List_2.AddItem(interval);
				pQuery->nextRow();
			}
		}
		pQuery->finalize();
		db.close();
		sls_List_2.Invalidate();
        sls_List_2.Update();

	}

	void SilenceCount()
	{
		CppSQLite3DB db;
		CppSQLite3Query *pQuery;
		db.open(L"Schedule.db");   
		
		SYSTEMTIME st;
		CMzString day_week(10),time_now(10);
		GetLocalTime(&st);
		wsprintf(time_now.C_Str(),L"%02d:%02d",st.wHour,st.wMinute);
		
		if(1==st.wDayOfWeek)
		{
			day_week=L"星期一";
		}
		else if(2==st.wDayOfWeek)
		{
			day_week=L"星期二";
		}
		else if(3==st.wDayOfWeek)
		{
			day_week=L"星期三";
		}
		else if(4==st.wDayOfWeek)
		{
			day_week=L"星期四";
		}
		else if(5==st.wDayOfWeek)
		{
			day_week=L"星期五";
		}
		else if(6==st.wDayOfWeek)
		{
			day_week=L"星期六";
		}
		else if(0==st.wDayOfWeek)
		{
			day_week=L"星期天";
		}

		CMzString sql(100);
		wsprintf(sql.C_Str(),L"select * from silenceset where dayweek = '%s' order by begintime;" ,day_week.C_Str());
		pQuery=db.execQuery(sql);
		
		

		CMzString begin_time(10),end_time(10),min_between(10),sls_between(100);
		bool flag=true;
		while(flag && (!pQuery->eof()))
		{
			begin_time=pQuery->fieldValue(L"begintime");
			end_time=pQuery->fieldValue(L"endtime");
		//	MzMessageBoxEx(this->m_hWnd, begin_time, L"提醒");
			if(!(time_now.Compare(begin_time.C_Str())<0)&&!(time_now.Compare(end_time.C_Str())>0))
			{   // MzMessageBoxEx(this->m_hWnd, L"哈哈", L"提醒");

				//设定此时为静音并计算出还差多少分钟走出静音
				wsprintf(min_between.C_Str(),L"%d",(_ttoi(end_time.SubStr(0,2))*60+_ttoi(end_time.SubStr(3,2)))-(_ttoi(time_now.SubStr(0,2))*60+_ttoi(time_now.SubStr(3,2))));				
				wsprintf(sls_between.C_Str(),L"静音中.. 还差 %d 分钟离开静音区间",_ttoi(min_between)+1);
				sls_Static.SetText(sls_between);
				if(min_between==L"0")
				{
					wsprintf(sls_between.C_Str(),L"静音中.. 还差 %d 秒离开静音区间",60-st.wSecond);
				//	MzMessageBoxEx(this->m_hWnd, sls_between, L"提醒");
					sls_Static.SetText(sls_between);
				}
//				MzMessageBoxEx(GetParentWnd(), min_between, L"提醒");
				flag=false;
			}
			else if(time_now.Compare(begin_time)<0)
			{  // MzMessageBoxEx(this->m_hWnd, L"哈哈", L"提醒");

				//设定此时为非静音并计算还差多少分钟进入静音 
				wsprintf(min_between.C_Str(),L"%d",(_ttoi(begin_time.SubStr(0,2))*60+_ttoi(begin_time.SubStr(3,2)))-(_ttoi(time_now.SubStr(0,2))*60+_ttoi(time_now.SubStr(3,2))));			
				wsprintf(sls_between.C_Str(),L"非静音中.. 还差 %s 分钟进入静音区间",min_between.C_Str());
				sls_Static.SetText(sls_between);
				if(min_between==L"0")
				{
					wsprintf(sls_between.C_Str(),L"静音中.. 还差 %d 秒进入静音区间",60-st.wSecond);
					sls_Static.SetText(sls_between);
				}
				flag=false;
			}

			pQuery->nextRow();
		}
		if(flag==true)
		{
			sls_Static.SetText(L"非静音中...");
		}


		pQuery->finalize();
		db.close();

	}

};

MZ_IMPLEMENT_DYNAMIC(SilenceWnd)

