#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <Sqlite/CppSQLite3U.h>
#include "define.h"





//����ȫ�ֱ���,������¼���ڼ�,��ʼʱ�������ʱ��
CMzString sls_timeB(20);
CMzString sls_timeE(20);
CMzString sls_week(20);

// �� CMzWndEx ��������������
class AddIntervalWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AddIntervalWnd);
public:
  // �����еİ�ť�ؼ�
  UiCaption AddInterval;
  UiButton sls_Time_Begin;
  UiButton sls_Time_End;
  UiButton sls_WeekBtn;
  UiToolbar_Text sls_bottom_add;
  UiStatic sls_addMsg[2];
  UiButton sls_Line[3];


  SYSTEMTIME m_sTime;


protected:
  // ���ڵĳ�ʼ��
  virtual BOOL OnInitDialog()
  {
    // �����ȵ��û���ĳ�ʼ��
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }
	GetLocalTime(&m_sTime);


    CMzString str(128);

              // ��ʼ�������еĿؼ�
	AddInterval.SetPos(0,0,480,50);
	AddInterval.SetText(L"��Ӿ�������");
	AddUiWin(&AddInterval);

	sls_addMsg[0].SetPos(0,190,240,100);
	sls_addMsg[0].SetText(L"��ʼʱ�䣺");
	AddUiWin(&sls_addMsg[0]);

	sls_addMsg[1].SetPos(0,290,240,100);
	sls_addMsg[1].SetText(L"����ʱ�䣺");
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
    sls_bottom_add.SetButton(0, true, true, L"����");
    sls_bottom_add.SetButton(1, true, true, L"����");
    sls_bottom_add.SetButton(2, true, true, L"ѡ��");
    sls_bottom_add.SetID(MZ_SLS_BOTTOM_ADD);
    AddUiWin(&sls_bottom_add);

	sls_WeekBtn.SetButtonType(MZC_BUTTON_GRAY);
    sls_WeekBtn.SetID(MZ_SLS_WEEK);
    sls_WeekBtn.SetPos(100, 70, 280, 100);
    sls_WeekBtn.SetText(sls_week);          //���޸�~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
    

              // �ѿؼ���ӵ�������
 

    return TRUE;
  }

  // ����������Ϣ�Ĵ�����
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
          
          // ���öԻ����ʼ��ʾ���ڵ���index��indexֵ��0��ʼ
		  setTimeDlg_Begin.m_InitData.iItem1Data = m_sTime.wHour;
		  setTimeDlg_Begin.m_InitData.iItem2Data = m_sTime.wMinute;
        

          setTimeDlg_Begin.m_InitData.sItem1 = L"ʱ";
          setTimeDlg_Begin.m_InitData.sItem2 = L"��";
          setTimeDlg_Begin.m_InitData.iItem1Width = setTimeDlg_Begin.m_InitData.iItem2Width = 210;
          setTimeDlg_Begin.EnableDisplayYearData(false);     //����������ʾ0ʱ0��
          setTimeDlg_Begin.SetEnableChangeItemData(false);

          // �����������öԻ���Ĵ���
          RECT rcWorkDate = MzGetWorkArea();
          setTimeDlg_Begin.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // ���ô��ڵ����Ķ���Ч��
          setTimeDlg_Begin.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setTimeDlg_Begin.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // ����Ի�������ȷ��������ʾ�Ի������õ�����
          if (ID_OK == setTimeDlg_Begin.DoModal())
          {
			  m_sTime.wHour = setTimeDlg_Begin.m_InitData.iItem1Data;
			  m_sTime.wMinute = setTimeDlg_Begin.m_InitData.iItem2Data;

//              CMzString str(128);
//			  wsprintf(str.C_Str(), L"%dʱ%d��", m_sTime.wHour, m_sTime.wMinute);
			  wsprintf(sls_timeB.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
//			  MzMessageBoxEx(m_hWnd, sls_timeB, L"����");
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
          
          // ���öԻ����ʼ��ʾ���ڵ���index��indexֵ��0��ʼ
		  setTimeDlg_End.m_InitData.iItem1Data = m_sTime.wHour;
		  setTimeDlg_End.m_InitData.iItem2Data = m_sTime.wMinute;
        

          setTimeDlg_End.m_InitData.sItem1 = L"ʱ";
          setTimeDlg_End.m_InitData.sItem2 = L"��";
          setTimeDlg_End.m_InitData.iItem1Width = setTimeDlg_End.m_InitData.iItem2Width = 210;
          setTimeDlg_End.EnableDisplayYearData(false);     //����������ʾ0ʱ0��
          setTimeDlg_End.SetEnableChangeItemData(false);

          // �����������öԻ���Ĵ���
          RECT rcWorkDate = MzGetWorkArea();
          setTimeDlg_End.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // ���ô��ڵ����Ķ���Ч��
          setTimeDlg_End.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setTimeDlg_End.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // ����Ի�������ȷ��������ʾ�Ի������õ�����
          if (ID_OK == setTimeDlg_End.DoModal())
          {
			  m_sTime.wHour = setTimeDlg_End.m_InitData.iItem1Data;
			  m_sTime.wMinute = setTimeDlg_End.m_InitData.iItem2Data;

//              CMzString str(128);
//			  wsprintf(str.C_Str(), L"%dʱ%d��", m_sTime.wHour, m_sTime.wMinute);
			  wsprintf(sls_timeE.C_Str(), L"%02d:%02d", m_sTime.wHour, m_sTime.wMinute);
//			  MzMessageBoxEx(m_hWnd, sls_timeE, L"����");
              sls_Time_End.SetText(sls_timeE.C_Str());
		  }

          break;   
      }
    case MZ_SLS_WEEK:
		{
			MzPopupMenu weekPopupMenu;
			weekPopupMenu.SetMenuTitle(L"��������");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"����һ");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"���ڶ�");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"������");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 4, L"������");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 5, L"������");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 6, L"������");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 7, L"������");

			int result = weekPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					sls_WeekBtn.SetText(L"����һ");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					sls_WeekBtn.SetText(L"���ڶ�");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					sls_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					sls_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					sls_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					sls_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 7:
				{
					sls_WeekBtn.SetText(L"������");
					break;
				}
			}
			sls_week=sls_WeekBtn.GetText();
		//	MzMessageBoxEx(m_hWnd, sls_week, L"����");
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
//			MzMessageBoxEx(m_hWnd, szsql, L"����");


		    db.close();
		}
	
	}





};

MZ_IMPLEMENT_DYNAMIC(AddIntervalWnd)






// �� CMzWndEx ��������������
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
  // ���ڵĳ�ʼ��
  virtual BOOL OnInitDialog()
  {
    // �����ȵ��û���ĳ�ʼ��
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

              // ��ʼ�������еĿؼ�
	sls_caption_1.SetPos(0,0,200,44);
	sls_caption_1.SetText(L"����");
	AddUiWin(&sls_caption_1);
	sls_caption_2.SetPos(200,0,280,44);
	sls_caption_2.SetText(L"��������");
	AddUiWin(&sls_caption_2);

	sls_Line_1.SetPos(5,44,200,485);
	sls_Line_1.SetButtonType(MZC_BUTTON_LINE_RIGHT);
	AddUiWin(&sls_Line_1);

	sls_Line_2.SetPos(0,42+70*7,480,4);
	sls_Line_2.SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&sls_Line_2);

	sls_Static.SetPos(0,42+70*7,480,80);
	sls_Static.SetTextColor( RGB(165 ,42, 42 ));
	sls_Static.SetText(L"����Ӿ�������");
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

    // ���б�ؼ������
    ListItem dayweek;
	dayweek.Text=L"����һ";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"���ڶ�";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"������";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"������";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"������";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"������";
	sls_List_1.AddItem(dayweek);
	dayweek.Text=L"������";
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
			//MzMessageBoxEx(m_hWnd, sql, L"����");
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
    sls_bottom.SetButton(0, true, true, L"����");
    sls_bottom.SetButton(1, true, true, L"���");
    sls_bottom.SetButton(2, true, true, L"ɾ��");
    sls_bottom.SetID(MZ_SLS_BOTTOM);
    AddUiWin(&sls_bottom);


    return TRUE;
  }

  // ���� MZFC ����Ϣ������
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
				sls_week=L"����һ";
					break;
			case 1:
				sls_week=L"���ڶ�";
					break;
			case 2:
				sls_week=L"������";
					break;
			case 3:
				sls_week=L"������";
					break;
			case 4:
				sls_week=L"������";
					break;
			case 5:
				sls_week=L"������";
					break;
			case 6:
				sls_week=L"������";
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
					//MzMessageBoxEx(m_hWnd, sql, L"����");
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

  // ���� MZFC ��������Ϣ������
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
					//MzMessageBoxEx(m_hWnd, sql, L"����");
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
		if(1 == MzMessageBoxEx(m_hWnd, L"���Ҫ��վ���������?", L"Exit", MB_YESNO, false))
			{
				CppSQLite3DB db;
				db.open(L"Schedule.db");                        //���ݿ����ֺ��治��";"
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
//		MzMessageBoxEx(m_hWnd, szsql, L"����");
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
				//MzMessageBoxEx(m_hWnd, sql, L"����");
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
			day_week=L"����һ";
		}
		else if(2==st.wDayOfWeek)
		{
			day_week=L"���ڶ�";
		}
		else if(3==st.wDayOfWeek)
		{
			day_week=L"������";
		}
		else if(4==st.wDayOfWeek)
		{
			day_week=L"������";
		}
		else if(5==st.wDayOfWeek)
		{
			day_week=L"������";
		}
		else if(6==st.wDayOfWeek)
		{
			day_week=L"������";
		}
		else if(0==st.wDayOfWeek)
		{
			day_week=L"������";
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
		//	MzMessageBoxEx(this->m_hWnd, begin_time, L"����");
			if(!(time_now.Compare(begin_time.C_Str())<0)&&!(time_now.Compare(end_time.C_Str())>0))
			{   // MzMessageBoxEx(this->m_hWnd, L"����", L"����");

				//�趨��ʱΪ�����������������ٷ����߳�����
				wsprintf(min_between.C_Str(),L"%d",(_ttoi(end_time.SubStr(0,2))*60+_ttoi(end_time.SubStr(3,2)))-(_ttoi(time_now.SubStr(0,2))*60+_ttoi(time_now.SubStr(3,2))));				
				wsprintf(sls_between.C_Str(),L"������.. ���� %d �����뿪��������",_ttoi(min_between)+1);
				sls_Static.SetText(sls_between);
				if(min_between==L"0")
				{
					wsprintf(sls_between.C_Str(),L"������.. ���� %d ���뿪��������",60-st.wSecond);
				//	MzMessageBoxEx(this->m_hWnd, sls_between, L"����");
					sls_Static.SetText(sls_between);
				}
//				MzMessageBoxEx(GetParentWnd(), min_between, L"����");
				flag=false;
			}
			else if(time_now.Compare(begin_time)<0)
			{  // MzMessageBoxEx(this->m_hWnd, L"����", L"����");

				//�趨��ʱΪ�Ǿ��������㻹����ٷ��ӽ��뾲�� 
				wsprintf(min_between.C_Str(),L"%d",(_ttoi(begin_time.SubStr(0,2))*60+_ttoi(begin_time.SubStr(3,2)))-(_ttoi(time_now.SubStr(0,2))*60+_ttoi(time_now.SubStr(3,2))));			
				wsprintf(sls_between.C_Str(),L"�Ǿ�����.. ���� %s ���ӽ��뾲������",min_between.C_Str());
				sls_Static.SetText(sls_between);
				if(min_between==L"0")
				{
					wsprintf(sls_between.C_Str(),L"������.. ���� %d ����뾲������",60-st.wSecond);
					sls_Static.SetText(sls_between);
				}
				flag=false;
			}

			pQuery->nextRow();
		}
		if(flag==true)
		{
			sls_Static.SetText(L"�Ǿ�����...");
		}


		pQuery->finalize();
		db.close();

	}

};

MZ_IMPLEMENT_DYNAMIC(SilenceWnd)

