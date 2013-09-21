 #include "WidgetTest.h"


#define MZ_IDC_TESTBTN1  101

void SHWidget::PaintWin( HDC hdcDst, RECT* prcWin, RECT* prcUpdate )
{
	COLORREF m_clrA = RGB(54, 54 ,54 );
    COLORREF clr = RGB(255,255,255);
    RECT rcWin = *prcWin;


	RECT rcBg = *prcWin;
	rcBg.top=rcBg.top+5;
	rcBg.bottom=rcBg.bottom-5;
    InflateRect(&rcBg, -15,-15);
	DrawRoundRect(hdcDst, &rcBg, 15, m_clrA, m_clrA);
   

	RECT under;
	under.bottom=rcBg.bottom-10;
	under.top=rcBg.top+50;
	under.left=rcBg.left+10;
	under.right=rcBg.right-10;
//	InflateRect(&under,-15,-15);
	DrawRoundRect_Bottom(hdcDst, &under, 5, clr, clr);  



    HFONT font = FontHelper::GetFont(22, FW_NORMAL,0,0,0,FONT_QUALITY_DEFAULT);
    HGDIOBJ oldfont = SelectObject(hdcDst, font);
	::SetTextColor(hdcDst, GetTextColor());
    ::SetBkMode(hdcDst, TRANSPARENT);

    CMzString strTime(MAX_PATH),dayWeek(5);
	wsprintf(strTime.C_Str(), L"%02u年%02u月%02u日", st.wYear, st.wMonth, st.wDay);
	wsprintf(dayWeek.C_Str(), L"星期%2u", st.wDayOfWeek);

    RECT rc = rcBg;
	rc.bottom=under.top-5;
	rc.top=rc.bottom-30;
	rc.left=rcBg.left-10;	
	rc.right=rc.left+210;
    MzDrawText(hdcDst, strTime.C_Str(), &rc, DT_VCENTER|DT_CENTER);
	rc.right=rcBg.right;
	rc.left=rc.right-100;
	if(1==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期一", &rc, DT_VCENTER|DT_CENTER);
	}
	else if(2==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期二", &rc, DT_VCENTER|DT_CENTER);
	}
	else if(3==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期三", &rc, DT_VCENTER|DT_CENTER);
	}
	else if(4==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期四", &rc, DT_VCENTER|DT_CENTER);
	}
	else if(5==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期五", &rc, DT_VCENTER|DT_CENTER);
	}
	else if(6==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期六", &rc, DT_VCENTER|DT_CENTER);
	}
	else if(0==st.wDayOfWeek)
	{
		MzDrawText(hdcDst, L"星期天", &rc, DT_VCENTER|DT_CENTER);
	}
	

//	wsprintf(strTime.C_Str(),L"%d",under.right-under.left);
//	MzMessageBoxEx(GetParentWnd(), strTime, L"提醒");


}         

int SHWidget::OnLButtonDown( UINT fwKeys, int xPos, int yPos )
{
    int iRet = UiWidget::OnLButtonDown(fwKeys, xPos, yPos);	
    return iRet;
}

int SHWidget::OnLButtonUp( UINT fwKeys, int xPos, int yPos )
{
    int iRet = UiWidget::OnLButtonUp(fwKeys, xPos, yPos);

    return iRet;
}

int SHWidget::OnMouseMove( UINT fwKeys, int xPos, int yPos )
{
    int iRet = UiWidget::OnMouseMove(fwKeys, xPos, yPos);

    return iRet;
}

int SHWidget::OnLButtonDblClk(UINT fwKeys, int xPos, int yPos)
{
    SHELLEXECUTEINFO shellInfo = { 0 };
    shellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellInfo.fMask = 0;
    shellInfo.hwnd = NULL;
    shellInfo.lpVerb = L"Open";
    shellInfo.lpFile = L"\\Program Files\\正在编写学生助理\\学生助理.exe"; 
    shellInfo.lpParameters = L""; 
    shellInfo.lpDirectory = NULL;
    shellInfo.nShow = SW_SHOW;
    shellInfo.hInstApp = NULL; 
    ShellExecuteEx(&shellInfo);
    return 0;
}


SHWidget::SHWidget()
{
    
}

SHWidget::~SHWidget()
{

}

bool SHWidget::StartWidget()
{
    UINT id = SW_GetFreeID();
    if(id==0)
        return false;

	GetLocalTime(&st);

//	COLORREF coloer=RGB(255,255,255);
    SetID(id);
    SetTimer(GetParentWnd(), GetID(),  5000, 0);
	SetTimer(GetParentWnd(), 1,  10000, 0);
	
	
//	id = SW_GetFreeID();
//	mycareer.SetID(id);
//	mycareer.SetPos(16,232,432,30);
////	mycareer.SetPos(16,221,432,25);
//	AddChild(&mycareer);
//
//	id = SW_GetFreeID();
//	carMsg.SetID(id);
//	carMsg.SetPos(16,232,432,30);
//	carMsg.SetTextSize(18);
//	carMsg.SetText(L"本学期进度 62%       还有 56 天学期结束");
//	AddChild(&carMsg);

	id = SW_GetFreeID();
	a_List.SetID(id);
	a_List.SetPos(15+10+3,15+50+5,408,174);
//	a_List.SetPos(15+10+3,15+50,408,165);
	a_List.SetTextSize(19); 
	a_List.EnableDragModeH(false);
	a_List.EnableScrollOptimize(true);
	a_List.EnableScrollableParent(false);
    a_List.SetItemHeight(36);

	AddChild(&a_List);

	PrintAgenda();
//	PrintSchedule();

    return true;
}

void SHWidget::EndWidget()
{	 
	SW_ReleaseID(a_List.GetID());
//	SW_ReleaseID(dateToday.GetID());
    SW_ReleaseID(GetID());	
}

int SHWidget::OnTimer( UINT_PTR nIDEvent )
{
    if (nIDEvent==GetID())
    {

		PrintAgenda();
		SilenceSet();
		a_List.Invalidate();
		a_List.Update();
    }
	else if(nIDEvent==1)
	{
		CheckNotify();
	}

    return 0;
}

void SHWidget::OnCalcItemSize( __out int &xSize, __out int &ySize )
{
    xSize = 4;
    ySize = 2;
}




void SHWidget::CheckNotify()
{
			  CppSQLite3DB db;
			  CppSQLite3Query *pQuery;
			  db.open(L"Schedule.db");    	  

			  CMzString str(128);
			  CMzString date_today(20);
			  GetLocalTime(&st);
			  wsprintf(str.C_Str(), L"%2d-%02d-%02d %02d:%02d", st.wYear, st.wMonth, st.wDay,st.wHour,st.wMinute);
			  CMzString sql(200);
			
			  CMzString datetime(30),weektime(15),remind(50);
			  if(db.tableExists(L"agenda"))
			  {     
				 																	
				  wsprintf(sql.C_Str(),L"%s%s%s",L"select * from agenda where date_time >='",str.C_Str(),L"' order by date_time;");
				  pQuery=db.execQuery(sql); 
				  
				  while(!(pQuery->eof()))
				  {     
					  datetime = pQuery->fieldValue(L"date_time"); 
				  
					  weektime=pQuery->fieldValue(L"week_time");
					  if(weektime==L"下下周后")
					  {						 
						  break;
					  }
					  
				
					  remind = pQuery->fieldValue(L"remind");
					  

					   
					  if(str.Compare(datetime.C_Str())==0)
					  {
						    	 
							MZ_USER_NOTIFICATION notifyInfo = {0};
							notifyInfo.ActionFlags = MUN_VIBRATE;
							notifyInfo.dwVibratePeriod = 5; // 震动10秒
							hr = MzSetUserNotification(hr, &notifyInfo);
							MzMessageBoxEx(GetParentWnd(), remind, L"提醒");

					  }
					  				  
					  pQuery->nextRow();
				  }
				  pQuery->finalize();
			  }
			 
			  db.close();

}


void SHWidget::PrintAgenda()
{
			  a_List.RemoveAll();
			  CppSQLite3DB db;
			  CppSQLite3Query *pQuery;
			  db.open(L"Schedule.db");    
			  
			  

			  CMzString str(128);
			  CMzString date_today(20);
			  GetLocalTime(&st);
			  wsprintf(str.C_Str(), L"%2d-%02d-%02d 00:00", st.wYear, st.wMonth, st.wDay);
			  CMzString sql(200);

			  MyListItem *pmlid;
			  CMzString datetime(30),weektime(15);
			  ListItem li;
			  if(db.tableExists(L"agenda"))
			  {     
				 				 														
				  wsprintf(sql.C_Str(),L"%s%s%s",L"select * from agenda where date_time >='",str.C_Str(),L"' order by date_time;");
				  pQuery=db.execQuery(sql); 
				  
				  while(!(pQuery->eof()))
				  {     
					  datetime = pQuery->fieldValue(L"date_time"); 
				  
					  weektime=pQuery->fieldValue(L"week_time");
					  if(weektime==L"下下周后")
					  {						 
						  break;
					  }
					  
					  pmlid = new MyListItem;
					  pmlid->WeekTime = weektime;					  
					  pmlid->VagueTime = pQuery->fieldValue(L"vague_time");
					  pmlid->Remind = pQuery->fieldValue(L"remind");
					  
					  pmlid->DateTime = datetime.SubStr(5,5);

					   
					  if(str.SubStr(0,10).Compare(datetime.SubStr(0,10).C_Str())==0)
					  {
							pmlid->WeekTime=L"今天";
					  }
					  
					  li.Data=pmlid;
					  a_List.AddItem(li);
					  pQuery->nextRow();
				  }
				  pQuery->finalize();
			  }
			 
			  db.close();

}

void SHWidget::SilenceSet()
{
		CppSQLite3DB db;
		CppSQLite3Query *pQuery;
		db.open(L"Schedule.db");   

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
		

		CMzString begin_time(10),end_time(10),min_between(10);
		bool flag=true;
		bool should=false;
		while(flag && (!pQuery->eof()))
		{
			begin_time=pQuery->fieldValue(L"begintime");
			end_time=pQuery->fieldValue(L"endtime");
			if(!(time_now.Compare(begin_time.C_Str())<0)&&!(time_now.Compare(end_time.C_Str())>0))
			{
				//设定此时为静音并计算出还差多少分钟走出静音
				wsprintf(min_between.C_Str(),L"%d",(_ttoi(end_time.SubStr(0,2))*60+_ttoi(end_time.SubStr(3,2)))-(_ttoi(time_now.SubStr(0,2))*60+_ttoi(time_now.SubStr(3,2))));				
				should=true;
//				MzMessageBoxEx(GetParentWnd(), min_between, L"提醒");
				flag=false;
			}
			else if(time_now.Compare(begin_time)<0)
			{
				//设定此时为非静音并计算还差多少分钟进入静音
				wsprintf(min_between.C_Str(),L"%d",(_ttoi(begin_time.SubStr(0,2))*60+_ttoi(begin_time.SubStr(3,2)))-(_ttoi(time_now.SubStr(0,2))*60+_ttoi(time_now.SubStr(3,2))));			
				should=false;
//				MzMessageBoxEx(GetParentWnd(), min_between, L"提醒");
				flag=false;
			}
			else
			{
				should=false;
			}

			pQuery->nextRow();
		}
		if(should)
		{
//			BeSilent();
	//		IMixer::SetSpeakerVolume(0);
		
			SilenceSendMsgToShell(true);
		}
		else
		{
//			BeSilent();
			SilenceSendMsgToShell(false);
		}

		pQuery->finalize();
		db.close();

}

BOOL SHWidget::SilenceSendMsgToShell(BOOL bSilence)

{

		MSGQUEUEOPTIONS sOptions;
		sOptions.dwSize     = sizeof(MSGQUEUEOPTIONS);
		sOptions.dwFlags    = MSGQUEUE_ALLOW_BROKEN;
		sOptions.dwMaxMessages   = 8;
		sOptions.cbMaxMessage   = sizeof(DIALTOSHELLINFOR);
		sOptions.bReadAccess   = FALSE;  

		//获得呼叫消息队列的HANDLE
		HANDLE hMsgQueue = CreateMsgQueue(DIAL_TO_SHELL_INFOR, &sOptions);

		if(!hMsgQueue)
		{
			RETAILMSG(1,(TEXT("Don't open the message queue\n")));
			return FALSE;
		}
		else
		{
			DIALTOSHELLINFOR  dialNotifyMsg;
			ZeroMemory(&dialNotifyMsg, sizeof(DIALTOSHELLINFOR));

			//TODO:填充该结构
			dialNotifyMsg.parameterVaildMark = SILENT_VALID;

			if(bSilence)
			{
				dialNotifyMsg.SilentStatus = SILENT_STATUS_SILENCE;
			}
			else 
			{
				dialNotifyMsg.SilentStatus = SILENT_STATUS_UNKNOWN;
			}

			WriteMsgQueue(hMsgQueue,&dialNotifyMsg,sizeof(DIALTOSHELLINFOR),0x0,0x0);
		}

		CloseMsgQueue(hMsgQueue);

		return TRUE;
}

//void SHWidget::BeSilent()
//{
//		HKEY hKey = NULL;
//
//		DWORD dwValue = 1;
//		long ret = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("ControlPanel\\Volume"), 0, KEY_WRITE|KEY_READ, &hKey);
//
//		if (ret == ERROR_SUCCESS)
//		{
//	//		MzMessageBoxEx(GetParentWnd(), L"234", L"提醒");
//			if (RegSetValueEx(hKey, TEXT("Silence"), NULL, REG_DWORD, (BYTE*)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
//			{
//				
//				waveOutSetVolume(0,0);
//			}
//		}
//		RegCloseKey(hKey);
//
//}
//
