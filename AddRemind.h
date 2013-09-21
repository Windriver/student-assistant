#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <Sqlite/CppSQLite3U.h>
#include "define.h"
#include "AgendaRemind.h"




//ȫ�ֱ���
CMzString big_thing_now(100);


class AddSmallThing: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AddSmallThing);
public:
  // �����еİ�ť�ؼ�
  UiSingleLineEdit new_thing;
  UiCaption new_Caption;
  UiToolbar_Text new_bottom;
  UiStatic new_big_thing_now;

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
    new_thing.SetPos(100,156,280,70);
	new_thing.SetSipMode(IM_SIP_MODE_GEL_PY);
    AddUiWin(&new_thing);
	new_thing.SetFocus(true);

	CMzString new_thing_tip(100);
	wsprintf(new_thing_tip.C_Str(),L"%s%s%s",L"����Ϊ <",big_thing_now.C_Str(),L"> ��Ӵ��¼�");
	new_big_thing_now.SetPos(10,78,460,70);
	new_big_thing_now.SetText(new_thing_tip);
	AddUiWin(&new_big_thing_now);

	new_Caption.SetPos(0,0,480,70);
	new_Caption.SetText(L"����µĴ��¼�");
	AddUiWin(&new_Caption);

	new_bottom.SetID(MZ_AGA_BOTTOM_NEWTHING);
	new_bottom.SetPos(0,GetHeight()-70,480,70);
	new_bottom.SetButton(0,true,true,L"ȡ��");
    new_bottom.SetButton(2,true,true,L"����");
//	new_bottom.SetButton(2,true,true,L"���");
	AddUiWin(&new_bottom);
 

    return TRUE;
  }

  // ����������Ϣ�Ĵ�����
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
		//		  MzMessageBoxEx(m_hWnd, szsql, L"����");

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
  // �����еİ�ť�ؼ�
  UiSingleLineEdit new_thing;
  UiCaption new_Caption;
  UiToolbar_Text new_bottom;
  UiStatic new_big_thing_now;

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
    new_thing.SetPos(100,156,280,70);
	new_thing.SetSipMode(IM_SIP_MODE_GEL_PY);
    AddUiWin(&new_thing);
	new_thing.SetFocus(true);

	new_big_thing_now.SetPos(10,78,460,70);
	new_big_thing_now.SetText(L"���������¼�");
	AddUiWin(&new_big_thing_now);

	new_Caption.SetPos(0,0,480,70);
	new_Caption.SetText(L"����µ����¼�");
	AddUiWin(&new_Caption);

	new_bottom.SetID(MZ_AGA_BOTTOM_NEWBIGTHING);
	new_bottom.SetPos(0,GetHeight()-70,480,70);
	new_bottom.SetButton(0,true,true,L"ȡ��");
    new_bottom.SetButton(2,true,true,L"����");
//	new_bottom.SetButton(2,true,true,L"���");
	AddUiWin(&new_bottom);
 

    return TRUE;
  }

  // ����������Ϣ�Ĵ�����
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
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",new_thing.GetText().C_Str(),L"���¼�",L");");
		//		  MzMessageBoxEx(m_hWnd, szsql, L"����");

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
  // �����еİ�ť�ؼ�
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
  bool isToday;            //����ȷ���¼��¼��Ƿ�Ϊ����
  bool isVague;           //����ȷ���Ƿ���ģ��ģʽ��ʾʱ��



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
	
	aga_Line.SetPos(0,314,186,300);
	aga_Line.SetButtonType(MZC_BUTTON_LINE_RIGHT);
	AddUiWin(&aga_Line);

	aga_AddRemind.SetPos(0,0,480,45);
	aga_AddRemind.SetText(L"����ճ�����");
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
	aga_Detail.SetText(L"��ϸ��ʱ:");
	AddUiWin(&aga_Detail);

	aga_Vague.SetPos(15,210,120,60);
	aga_Vague.SetTextColor(clr);
	aga_Vague.SetTextSize(24);
	aga_Vague.SetDrawTextFormat(DT_LEFT|DT_VCENTER);
	aga_Vague.SetText(L"�����ʱ:");
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
    aga_WeekThBtn.SetText(L"����");
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
		aga_WeekBtn.SetText(L"����һ");
	}
	else if(dayweek_today==2)
	{
		aga_WeekBtn.SetText(L"���ڶ�");
	}
	else if(dayweek_today==3)
	{
		aga_WeekBtn.SetText(L"������");
	}
	else if(dayweek_today==4)
	{
		aga_WeekBtn.SetText(L"������");
	}
	else if(dayweek_today==5)
	{
		aga_WeekBtn.SetText(L"������");
	}
	else if(dayweek_today==6)
	{
		aga_WeekBtn.SetText(L"������");
	}
	else if(dayweek_today==7)
	{
		aga_WeekBtn.SetText(L"������");
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
		str=L"����";
	}
	else if(m_sTime.wHour<18)
	{
		str=L"����";
	}
	else
	{
		str=L"����";
	}
    aga_AmPmBtn.SetText(str.C_Str());
    aga_AmPmBtn.SetTextColor(RGB(0, 0, 0));
    AddUiWin(&aga_AmPmBtn);

	aga_static.SetPos(5,130,70,70);
	aga_static.SetText(L"�¼�:");
	AddUiWin(&aga_static);

	aga_aga.SetPos(80,130,220,70);
	AddUiWin(&aga_aga);

	aga_checkAll.SetID(MZ_AGA_CHECK_ALL);
	aga_checkAll.SetPos(GetWidth()-170,130,160,70);
	aga_checkAll.SetText(L"�鿴ȫ��");
	aga_checkAll.SetButtonType(MZCV2_BUTTON_GREEN);
	AddUiWin(&aga_checkAll);




	aga_bottom_add.SetID(MZ_AGA_BOTTOM_ADD);
	aga_bottom_add.SetPos(0,GetHeight()-70,GetWidth(),70);
	aga_bottom_add.EnableLeftArrow(true);
	aga_bottom_add.SetButton(0,true,true,L"����");
    aga_bottom_add.SetButton(1,true,true,L"����");
    aga_bottom_add.SetButton(2,true,true,L"ѡ��");
	AddUiWin(&aga_bottom_add);

	ImagingHelper* m_selImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_selImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_dImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_dImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_celImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_celImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);
    ImagingHelper* m_secImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_secImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);

        // ��ʼ�� MzGridMenu �ؼ�
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM11, L"ɾ�����¼�", m_selImg, m_selImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM22, L"ɾ�����¼�", m_dImg, m_dImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM33, L"������¼�", m_celImg, m_celImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM44, L"��Ӵ��¼�", m_secImg, m_secImgPrs);


	aga_caption_thing[0].SetPos(0,280,180,34);
	aga_caption_thing[0].SetText(L"���¼�");
	AddUiWin(&aga_caption_thing[0]);

	aga_caption_thing[1].SetPos(180,280,300,34);
	aga_caption_thing[1].SetText(L"���¼�");
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
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"����ҵ",L"��������ҵ",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"����ҵ",L"�����ϻ�����",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"Լ��",L"���ƽ����",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"Լ��",L"��С��ñԼ��",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"ι��",L"��С��ιӪ������",L");");
				  db.execDML(szsql);
				  wsprintf(szsql.C_Str(),L"%s'%s','%s'%s",L"insert into thing values (",L"ι��",L"���ʷ��������赼",L");");
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
		wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'���¼�';");
		pQuery=db.execQuery(sql);
		while(!(pQuery->eof()))
		{              
			//MzMessageBoxEx(m_hWnd, sql, L"����");
			
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

  // ����������Ϣ�Ĵ�����
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
          setDateDlg.m_InitData.iItem1Max = 2021 - 1923; // ����Ǵ�1923�꿪ʼ�����
          setDateDlg.m_InitData.iItem2Max = 12;
          setDateDlg.m_InitData.iItem3Max = setDateDlg.MaxDaysInMonth(m_sTime.wMonth, m_sTime.wYear);

          // ���öԻ����ʼ��ʾ���ڵ���index��indexֵ��0��ʼ
          setDateDlg.m_InitData.iItem1Data = m_sTime.wYear - 1923;
          setDateDlg.m_InitData.iItem2Data = m_sTime.wMonth - 1;
          setDateDlg.m_InitData.iItem3Data = m_sTime.wDay - 1;

          setDateDlg.m_InitData.sItem1 = L"��";
          setDateDlg.m_InitData.sItem2 = L"��";
          setDateDlg.m_InitData.sItem3 = L"��";
          setDateDlg.m_InitData.iItem1Width = setDateDlg.m_InitData.iItem2Width = setDateDlg.m_InitData.iItem3Width = 140;
          setDateDlg.EnableDisplayYearData(true);
          setDateDlg.SetEnableChangeItemData(true);

          // �����������öԻ���Ĵ���
          RECT rcWorkDate = MzGetWorkArea();
          setDateDlg.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // ���ô��ڵ����Ķ���Ч��
          setDateDlg.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setDateDlg.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // ����Ի�������ȷ��������ʾ�Ի������õ�����
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
          
          // ���öԻ����ʼ��ʾ���ڵ���index��indexֵ��0��ʼ
		  setTimeDlg.m_InitData.iItem1Data = m_sTime.wHour;
		  setTimeDlg.m_InitData.iItem2Data = m_sTime.wMinute;
        

          setTimeDlg.m_InitData.sItem1 = L"ʱ";
          setTimeDlg.m_InitData.sItem2 = L"��";
          setTimeDlg.m_InitData.iItem1Width = setTimeDlg.m_InitData.iItem2Width = 210;
          setTimeDlg.EnableDisplayYearData(false);     //����������ʾ0ʱ0��
          setTimeDlg.SetEnableChangeItemData(false);

          // �����������öԻ���Ĵ���
          RECT rcWorkDate = MzGetWorkArea();
          setTimeDlg.Create(rcWorkDate.left, rcWorkDate.top, RECT_WIDTH(rcWorkDate), RECT_HEIGHT(rcWorkDate), m_hWnd, 0, WS_POPUP);
          // ���ô��ڵ����Ķ���Ч��
          setTimeDlg.SetAnimateType_Show(MZ_ANIMTYPE_FADE);
          setTimeDlg.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);

          // ����Ի�������ȷ��������ʾ�Ի������õ�����
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
			weekthPopupMenu.SetMenuTitle(L"�����ܴ�");
			weekthPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"����");
			weekthPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"����");
            weekthPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"������");

			int result = weekthPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					aga_WeekThBtn.SetText(L"����");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					aga_WeekThBtn.SetText(L"����");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					aga_WeekThBtn.SetText(L"������");
					break;
				}
			}
			VagueToPrecise();                             //��������!
			break;
		}

	case MZ_AGA_WEEK_ADD:
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
					aga_WeekBtn.SetText(L"����һ");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					aga_WeekBtn.SetText(L"���ڶ�");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					aga_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					aga_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					aga_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					aga_WeekBtn.SetText(L"������");
					break;
				}
			case MZV2_MID_MIN + 7:
				{
					aga_WeekBtn.SetText(L"������");
					break;
				}
			}
			VagueToPrecise();                             //��������!
			break;
		}
	case MZ_AGA_AMPM_ADD:
		{
			MzPopupMenu ampmPopupMenu;
			ampmPopupMenu.SetMenuTitle(L"����ʱ���");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"�糿");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"����");
            ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"����");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 4, L"����");
            ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 5, L"����");
			ampmPopupMenu.AppendMenuItem(MZV2_MID_MIN + 6, L"��ҹ");

			int result = ampmPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					aga_AmPmBtn.SetText(L"�糿");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					aga_AmPmBtn.SetText(L"����");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					aga_AmPmBtn.SetText(L"����");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					aga_AmPmBtn.SetText(L"����");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					aga_AmPmBtn.SetText(L"����");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					aga_AmPmBtn.SetText(L"��ҹ");
					break;
				}
			}
			//VagueToPrecise();                             //��������!
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
						wsprintf(configure.C_Str(),L"��ȷ��Ҫ��� <%s> ?",this->aga_aga.GetText().C_Str());
						if(1 == MzMessageBoxEx(m_hWnd, configure, L"ȷ��", MB_YESNO, false))
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
						wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'���¼�';");
						pQuery=db.execQuery(sql);
						while(!(pQuery->eof()))
						{              
							//MzMessageBoxEx(m_hWnd, sql, L"����");
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
					wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'���¼�';");
					pQuery=db.execQuery(sql); 
					while(!(pQuery->eof()))
					{              
				//		MzMessageBoxEx(m_hWnd, sql, L"����");
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
        case MZ_AGA_GRIDMENU_ITEM33:              //���Ķ�
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
						//MzMessageBoxEx(m_hWnd, sql, L"����");
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
					wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'���¼�';");
					pQuery=db.execQuery(sql); 
					while(!(pQuery->eof()))
					{              
				//		MzMessageBoxEx(m_hWnd, sql, L"����");
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
					wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'���¼�';");
					pQuery=db.execQuery(sql);
					while(!(pQuery->eof()))
					{              
						//MzMessageBoxEx(m_hWnd, sql, L"����");
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
				wsprintf(sql.C_Str(),L"%s%s%s",L"select * from thing where bigthing='",big_thing_now.C_Str(),L"' and smallthing<>'���¼�';");
				pQuery=db.execQuery(sql);
				while(!(pQuery->eof()))
				{              
					//MzMessageBoxEx(m_hWnd, sql, L"����");
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
					if(aga_AmPmBtn.GetText()==L"�糿")
					{
						vague=L"07:00";
					}
					else if(aga_AmPmBtn.GetText()==L"����")
					{
						vague=L"10:00";
					}
					else if(aga_AmPmBtn.GetText()==L"����")
					{
						vague=L"12:00";
					}
					else if(aga_AmPmBtn.GetText()==L"����")
					{
						vague=L"15:00";
					}
					else if(aga_AmPmBtn.GetText()==L"����")
					{
						vague=L"19:00";
					}
					else if(aga_AmPmBtn.GetText()==L"��ҹ")
					{
						vague=L"22:00";
					}
					wsprintf(date_time.C_Str(),L"%s %s",this->aga_DateBtn.GetText().C_Str(),vague.C_Str());
			//		MzMessageBoxEx(m_hWnd, date_time, L"����");
			}

		    CMzString week_time(50);
			if(this->aga_WeekThBtn.GetText()==L"����֮ǰ")
			{
				week_time=L"����֮ǰ";
			}
			else if(this->aga_WeekThBtn.GetText()==L"�����ܺ�")
			{
				week_time=L"�����ܺ�";
			}
			else if(this->aga_WeekThBtn.GetText()==L"����")
			{
				wsprintf(week_time.C_Str(),L"��%s",this->aga_WeekBtn.GetText().SubStr(2,1).C_Str());
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
			this->aga_WeekThBtn.SetText(L"����֮ǰ");
		}
		else if(weekth_thatday==weekth_today)
		{
			this->aga_WeekThBtn.SetText(L"����");
		}
		else if(weekth_thatday==(weekth_today+1))
		{
			this->aga_WeekThBtn.SetText(L"����");
		}
		else if(weekth_thatday==(weekth_today+2))
		{
			this->aga_WeekThBtn.SetText(L"������");
		}
		else
		{
			this->aga_WeekThBtn.SetText(L"�����ܺ�");
		}

		if(dayweek_thatday==1)
		{
			this->aga_WeekBtn.SetText(L"����һ");
		}
		else if(dayweek_thatday==2)
		{
			this->aga_WeekBtn.SetText(L"���ڶ�");
		}
		else if(dayweek_thatday==3)
		{
			this->aga_WeekBtn.SetText(L"������");
		}
		else if(dayweek_thatday==4)
		{
			this->aga_WeekBtn.SetText(L"������");
		}
		else if(dayweek_thatday==5)
		{
			this->aga_WeekBtn.SetText(L"������");
		}
		else if(dayweek_thatday==6)
		{
			this->aga_WeekBtn.SetText(L"������");
		}
		else if(dayweek_thatday==7)
		{
			this->aga_WeekBtn.SetText(L"������");
		}
	}

	void PreciseToVague_1()
	{
		this->aga_AmPmBtn.SetText(L"ͬ��");
		isVague=false;
	}

	void VagueToPrecise_1()
	{
		CMzString vague(20);
		vague=this->aga_AmPmBtn.GetText();
		if(vague==L"�糿")
		{
			this->aga_TimeBtn.SetText(L"07:00");
		}
		else if(vague==L"����")
		{
			this->aga_TimeBtn.SetText(L"10:00");
		}
		else if(vague==L"����")
		{
			this->aga_TimeBtn.SetText(L"12:00");
		}
		else if(vague==L"����")
		{
			this->aga_TimeBtn.SetText(L"15:00");
		}
		else if(vague==L"����")
		{
			this->aga_TimeBtn.SetText(L"19:00");
		}
		else if(vague==L"��ҹ")
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
		CMzString date_today=M8Date::DateToday();     //��ã�������������������������������
		date_today=date_today.SubStr(0,date_today.Length());
//		date_today=L"20101015";
//		MzMessageBoxEx(m_hWnd, date_today, L"����");
	    CMzString sql(200);
		wsprintf(sql.C_Str(),L"%s%s%s",L"select week from schedule where date='",date_today.C_Str(),L"';");
		pQuery=db.execQuery(sql);
		CMzString week_temp=pQuery->fieldValue(L"week");  
		int weekth_today=_ttoi(week_temp);
		CMzString dayweek_btn(20);
		dayweek_btn=this->aga_WeekBtn.GetText();
		int dayweek;
		if(dayweek_btn==L"����һ")
		{
			dayweek=1;
		}
		else if(dayweek_btn==L"���ڶ�")
		{
			dayweek=2;
		}
		else if(dayweek_btn==L"������")
		{
			dayweek=3;
		}
		else if(dayweek_btn==L"������")
		{
			dayweek=4;
		}
		else if(dayweek_btn==L"������")
		{
			dayweek=5;
		}
		else if(dayweek_btn==L"������")
		{
			dayweek=6;
		}
		else if(dayweek_btn==L"������")
		{
			dayweek=7;
		}

		CMzString weekth_btn(20);
		weekth_btn=this->aga_WeekThBtn.GetText();
		if(weekth_btn==L"����")
		{
			weekth_today=weekth_today+0;
		}
		else if(weekth_btn==L"����")
		{
			weekth_today=weekth_today+1;
		}

		else if(weekth_btn==L"������")
		{
			weekth_today=weekth_today+2;
		}
		wsprintf(sql.C_Str(),L"%s%d%s%d%s",L"select * from schedule where week='",weekth_today,L"'and dayweek=",dayweek,L";");
		pQuery=db.execQuery(sql);    
//		MzMessageBoxEx(m_hWnd, sql, L"����");
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