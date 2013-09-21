class M8Date
{
private:
	int year;
	int month;
	int day;
	int week;
	int dayweek;

public:
	M8Date(int year_first,int month_first,int day_first,int dayweek_first)
	{
		this->year=year_first;
		this->month=month_first;
		this->day=day_first;
		this->dayweek=dayweek_first;
		this->week=1;
	}

	M8Date NextDay(M8Date &mdate)
	{
		if(((mdate.month==1)||(mdate.month==3)||(mdate.month==5)||(mdate.month==7)||(mdate.month==8)||(mdate.month==10)||(mdate.month==12))&&(mdate.day<31))
		{
			mdate.dayweek=(mdate.dayweek%7)+1;
			mdate.week+=(mdate.dayweek==1);
			mdate.day+=1;
			return mdate;
		}
		else if(((mdate.month==4)||(mdate.month==6)||(mdate.month==9)||(mdate.month==11))&&(mdate.day<30))
		{
			mdate.dayweek=(mdate.dayweek%7)+1;
			mdate.week+=(mdate.dayweek==1);
			mdate.day+=1;
			return mdate;
		}
		else if((mdate.month==2)&&(mdate.day<(28+((mdate.year%4==0)&&(mdate.year%100!=0)||(mdate.year%400==0)))))
		{
			mdate.dayweek=(mdate.dayweek%7)+1;
			mdate.week+=(mdate.dayweek==1);
			mdate.day+=1;
			return mdate;
		}
		else 
		{
			if(mdate.month<12)
			{
				mdate.dayweek=(mdate.dayweek%7)+1;
				mdate.week+=(mdate.dayweek==1);
				mdate.day=1;
				mdate.month+=1;
				return mdate;
			}
			else if(mdate.month==12)
			{
				mdate.dayweek=(mdate.dayweek%7)+1;
				mdate.week+=(mdate.dayweek==1);
				mdate.day=1;
				mdate.month=1;
				mdate.year+=1;
				return mdate;
			}
		}
	}

	int Getyear()
	{
		return this->year;
	}

	int Getmonth()
	{
		return this->month;
	}

	int Getday()
	{
		return this->day;
	}

	int Getweek()
	{
		return this->week;
	}

	int Getdayweek()
	{
		return this->dayweek;
	}

	//������һ����̬���еĺ�����Ա,�Ի�õ�ǰ����
	static CMzString DateToday()
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		CMzString sDate;
		wsprintf(sDate.C_Str(), L"%4d%02d%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);    
		
		return sDate;
	}


};


//����ȫ�ֱ�����¼�˴��༭�γ̵������ܺ������ڼ��ڿ�
extern int weekEdit,classEdit;


//��ʼ����༭�γ�ʱ�Ĵ���
class BeginEdit: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(BeginEdit);
public:
  // �����еİ�ť�ؼ�
  UiCaption EditCaption;
  UiToolbar_Text m_Bottom_Edit_1;

  UiSingleLineEdit m_edit_begweek;
  UiSingleLineEdit m_edit_endweek;
  UiSingleLineEdit m_edit_subject;
  UiSingleLineEdit m_edit_classroom;

  UiStatic m_text_begweek;
  UiStatic m_text_endweek;
  UiStatic m_text_subject;
  UiStatic m_text_classroom;



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
	EditCaption.SetID(MZ_IDC_CAPTION_EDIT);
	EditCaption.SetPos(0,0,480,MZM_HEIGHT_CAPTION);
    EditCaption.SetTextSize(25);
    AddUiWin(&EditCaption);

	m_edit_begweek.SetID(MZ_IDC_BEGWEEK);
	m_edit_begweek.SetPos(100,60,100,60);
	m_edit_begweek.SetTextSize(MZFS_MAX);
	m_edit_begweek.SetSipMode(IM_SIP_MODE_DIGIT,0);
	m_edit_begweek.SetTip2(L"��", true);
	m_edit_begweek.SetRightInvalid(40);
	AddUiWin(&m_edit_begweek);

	m_edit_endweek.SetID(MZ_IDC_ENDWEEK);
	m_edit_endweek.SetPos(340,60,100,60);
	m_edit_endweek.SetTextSize(MZFS_MAX);
	m_edit_endweek.SetSipMode(IM_SIP_MODE_DIGIT,0);
	m_edit_endweek.SetTip2(L"��", true);
	m_edit_endweek.SetRightInvalid(40);
	AddUiWin(&m_edit_endweek);

	m_edit_subject.SetID(MZ_IDC_SUBJECT);
	m_edit_subject.SetPos(GetWidth()-210,130,200,60);
	m_edit_subject.SetTextSize(MZFS_MAX);
	m_edit_subject.SetSipMode(IM_SIP_MODE_GEL_PY,0);
	m_edit_subject.SetTip(L"���������");
//	m_edit_subject.SetRightInvalid(40);
	AddUiWin(&m_edit_subject);

	m_edit_classroom.SetID(MZ_IDC_CLASSROOM);
	m_edit_classroom.SetPos(GetWidth()-160,200,150,60);
	m_edit_classroom.SetTextSize(MZFS_MAX);
	m_edit_classroom.SetSipMode(IM_SIP_MODE_GEL_LETTER,0);
	AddUiWin(&m_edit_classroom);

	m_text_begweek.SetPos(50,60,60,60);
	m_text_begweek.SetText(L"��");
	m_text_begweek.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_begweek);

	m_text_endweek.SetPos(290,60,60,60);
	m_text_endweek.SetText(L"��");
	m_text_endweek.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_endweek);

	m_text_subject.SetPos(50,130,100,60);
	m_text_subject.SetText(L"�γ�:");
	m_text_subject.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_subject);

	m_text_classroom.SetPos(50,200,100,60);
	m_text_classroom.SetText(L"����:");
	m_text_classroom.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_classroom);

	
	m_Bottom_Edit_1.SetID(MZ_IDC_BOTTOM_EDIT_1);
	m_Bottom_Edit_1.SetPos(0,270,GetWidth(),MZM_HEIGHT_BOTTOM);
	m_Bottom_Edit_1.SetButton(0,true,true,L"����");
	m_Bottom_Edit_1.SetButton(1,true,true,L"����");
	m_Bottom_Edit_1.SetButton(2,true,true,L"����");
	AddUiWin(&m_Bottom_Edit_1);


    return TRUE;
  }

  // ����������Ϣ�Ĵ�������
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_BOTTOM_EDIT_1:
      {
		  int nIndex=lParam;
		  if(nIndex==0)
		  {
			  EndModal(MZ_IDC_BOTTOM_EDIT_1);
		  }
		  if(nIndex==1)
		  {
			InserToSqlite3();
			EndModal(MZ_IDC_BOTTOM_EDIT_1);
		  }
        
      }
      break;
    }
  }

public:
  //���༭�����Ϣ����sqlite3���ݿ�
  void InserToSqlite3()
  {
	  CppSQLite3DB db;
	  db.open(L"Schedule.db");
	  CMzString sql(200),class_edit(10),room_edit;  //CMzStringĬ�Ϸ�����ֽڲ�������Ĳ�ѯ����õ�............

	  switch(classEdit)
	  {
	  case 1:
		  class_edit=L"first_c";
		  room_edit=L"first_r";
		  break;
	  case 2:
		  class_edit=L"second_c";
		  room_edit=L"second_r";
		  break;
	  case 3:
		  class_edit=L"third_c";
		  room_edit=L"third_r";
		  break;
	  case 4:
		  class_edit=L"fouth_c";
		  room_edit=L"fouth_r";
		  break;
	  case 5:
		  class_edit=L"fifth_c";
		  room_edit=L"fifth_r";
		  break;
	  }

	  CMzString week_begin=this->m_edit_begweek.GetText();
	  CMzString week_end=this->m_edit_endweek.GetText();

	  
//	  wsprintf(sql.C_Str(),L"%s%s%s%s%s%s%s%s%s%d%s" ,L"update schedule set ",class_edit.C_Str(),L"='",this->m_edit_subject.GetText().C_Str(),L"',",room_edit.C_Str(),L"='",this->m_edit_classroom.GetText().C_Str(),L"' where dayweek=",weekEdit,L";");

	  wsprintf(sql.C_Str(),L"%s%s%s%s%s%s%s%s%s%d%s%s%s%s%s" ,L"update schedule set ",class_edit.C_Str(),L"='",this->m_edit_subject.GetText().C_Str(),L"',",room_edit.C_Str(),L"='",this->m_edit_classroom.GetText().C_Str(),L"' where dayweek=",weekEdit,L" and week>=",week_begin.C_Str(),L" and week<=",week_end.C_Str(),L";");
	  if(1 == MzMessageBoxEx(m_hWnd, sql, L"Exit", MB_YESNO, false));
	  db.execDML(sql);


	//  db.execDML(L"insert into schedule values (1,1,'wawawa','a210');");
//	  db.execDML(L"insert into schedule values (2,1,'hh','a210');"); 

	  db.close();
	  
	  return;
  }
};

//MZ_IMPLEMENT_DYNAMIC(BeginEdit)


class IniSchedule: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(IniSchedule);
public:
  // �����еİ�ť�ؼ�
	UiCaption caption_init;
	UiSingleLineEdit first_y;
	UiSingleLineEdit first_m;
	UiSingleLineEdit first_d;
	UiSingleLineEdit first_w;
	UiButton ok_init;
	UiButton cancel_init;

  
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
	caption_init.SetPos(0,0,480,MZM_HEIGHT_CAPTION);
    caption_init.SetTextSize(25);
    AddUiWin(&caption_init);

	first_y.SetID(MZ_IDC_FIRST_Y);
	first_y.SetPos(100,60,100,60);
	first_y.SetTextSize(MZFS_MAX);
	first_y.SetSipMode(IM_SIP_MODE_DIGIT,0);
	first_y.SetTip2(L"��", true);
	first_y.SetRightInvalid(40);
	AddUiWin(&first_y);

	first_m.SetID(MZ_IDC_FIRST_M);
	first_m.SetPos(340,60,100,60);
	first_m.SetTextSize(MZFS_MAX);
	first_m.SetSipMode(IM_SIP_MODE_DIGIT,0);
	first_m.SetTip2(L"��", true);
	first_m.SetRightInvalid(40);
	AddUiWin(&first_m);

	first_d.SetID(MZ_IDC_FIRST_D);
	first_d.SetPos(GetWidth()-210,130,200,60);
	first_d.SetTextSize(MZFS_MAX);
	first_d.SetSipMode(IM_SIP_MODE_DIGIT,0);
	first_d.SetTip2(L"��", true);;
	first_d.SetRightInvalid(40);
	AddUiWin(&first_d);

	first_w.SetID(MZ_IDC_FIRST_W);
	first_w.SetPos(GetWidth()-160,200,150,60);
	first_w.SetTextSize(MZFS_MAX);
	first_w.SetSipMode(IM_SIP_MODE_DIGIT,0);
	first_w.SetTip2(L"��", true);;
	first_w.SetRightInvalid(40);
	AddUiWin(&first_w);

	ok_init.SetID(MZ_IDC_OK_INIT);
	ok_init.SetPos(70,270,100,60);
	ok_init.SetButtonType(MZC_BUTTON_GREEN);
	ok_init.SetText(L"ȷ��");
	AddUiWin(&ok_init);

	cancel_init.SetID(MZ_IDC_CANCEL_INIT);
	cancel_init.SetPos(310,270,100,60);
	cancel_init.SetButtonType(MZC_BUTTON_ORANGE);
	cancel_init.SetText(L"ȡ��");
	AddUiWin(&cancel_init);

	

    return TRUE;
  }

  // ����������Ϣ�Ĵ�������
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_CANCEL_INIT:
      {
		  EndModal(MZ_IDC_CANCEL_INIT);
		  break;
	  }
	case MZ_IDC_OK_INIT:
		if(1 == MzMessageBoxEx(m_hWnd, L"��ȷ������ѧ���ں����ڶ��������?", L"Exit", MB_YESNO, false))
		{
			NewSchedule();
			EndModal(MZ_IDC_OK_INIT);
		}
		
		break;
      }
      
    }

public:
  void NewSchedule()
  {
	  CppSQLite3DB db;
	  db.open(L"Schedule.db");                        //���ݿ����ֺ��治��";"
	  db.execDML(L"drop table schedule");
	  if(!db.tableExists(L"schedule"))
	  {
		  int y=_ttoi(this->first_y.GetText());
		  int m=_ttoi(this->first_m.GetText());
		  int d=_ttoi(this->first_d.GetText());
		  int w=_ttoi(this->first_w.GetText());
		  M8Date mdate(y,m,d,w);			//���ݿ��еı�ʶ��ò�Ʋ���������....................

	
		  db.execDML(L"create table schedule (date char(12),week int,dayweek int,first_c char(20),first_r char(20),second_c char(20),second_r char(20),third_c char(20),third_r char(20),fouth_c char(20),fouth_r char(20),fifth_c char(20),fifth_r char(20));");// 
		  CMzString szsql(200),szdate(40),szmonth(10),szday(10);
		  for(int i=1;i<=50;i++)
		  {
			  if(mdate.Getmonth()<10)
			  {
				  wsprintf(szmonth.C_Str(),L"%s%d",L"0",mdate.Getmonth());
			  }
			  else                                                  //�·�С��10��ҲҪת����CMzString!!!!!!!!
			  {
				  wsprintf(szmonth.C_Str(),L"%d",mdate.Getmonth());
			  }
			  if(mdate.Getday()<10)
			  {
				  wsprintf(szday.C_Str(),L"%s%d",L"0",mdate.Getday());
			  }
			  else
			  {
				  wsprintf(szday.C_Str(),L"%d",mdate.Getday());
			  }
			  wsprintf(szdate.C_Str(),L"%d%s%s",mdate.Getyear(),szmonth.C_Str(),szday.C_Str());

			  w=mdate.Getweek();
			  d=mdate.Getdayweek();
			  wsprintf(szsql.C_Str(),L"%s%s,%d,%d%s",L"insert into schedule (date,week,dayweek,first_c,first_r,second_c,second_r,third_c,third_r,fouth_c,fouth_r,fifth_c,fifth_r) values (",szdate.C_Str(),w,d,L",'<��>','','<��>','','<��>','','<��>','','<��>','');");
//			  szsql=L"insert into schedule values ('2010',1);";
//		  if(i==1)

//			  }
//			  db.execDML(L"insert into schedule values ('2011',1,1,'asd','asd','','asd','asd','asd','asd','asd','asd','');");
			  db.execDML(szsql);
			  mdate=mdate.NextDay(mdate);

		  }	
		 
		  
		  
	  db.close();
	  }
	  
  }

};  
//MZ_IMPLEMENT_DYNAMIC(IniSchedule)


// �� CMzWndEx ��������������
class ScheduleEditWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(ScheduleEditWnd);
public:
  // �����еİ�ť�ؼ�
  UiCaption MondayEdit,TuesdayEdit,WednesdayEdit,ThursdayEdit,FridayEdit,SaturdayEdit,SundayEdit;
  UiButton MonEdit[5],TuesEdit[5],WedEdit[5],ThursEdit[5],FriEdit[5],SatEdit[5],SunEdit[5];
  UiToolbar_Text m_Bottom_Edit;


protected:
  // ���ڵĳ�ʼ��
  virtual BOOL OnInitDialog()
  {
    // �����ȵ��û���ĳ�ʼ��
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }

	MondayEdit.SetID(MZ_IDC_MON_EDIT);
	MondayEdit.SetPos(0,0,160,MZM_HEIGHT_SUBJECT);
	MondayEdit.SetText(L"��һ");
	MondayEdit.SetTextSize(25);
	AddUiWin(&MondayEdit);

	TuesdayEdit.SetID(MZ_IDC_TUES_EDIT);
	TuesdayEdit.SetPos(160,0,160,MZM_HEIGHT_SUBJECT);
	TuesdayEdit.SetText(L"�ܶ�");
	TuesdayEdit.SetTextSize(25);
	AddUiWin(&TuesdayEdit);

	WednesdayEdit.SetID(MZ_IDC_WED_EDIT);
	WednesdayEdit.SetPos(320,0,160,MZM_HEIGHT_SUBJECT);
	WednesdayEdit.SetText(L"����");
	WednesdayEdit.SetTextSize(25);
	AddUiWin(&WednesdayEdit);

	ThursdayEdit.SetID(MZ_IDC_THURS_EDIT);
	ThursdayEdit.SetPos(0,310,160,MZM_HEIGHT_SUBJECT);
	ThursdayEdit.SetText(L"����");
	ThursdayEdit.SetTextSize(25);
	AddUiWin(&ThursdayEdit);

	FridayEdit.SetID(MZ_IDC_FRI_EDIT);
	FridayEdit.SetPos(160,310,160,MZM_HEIGHT_SUBJECT);
	FridayEdit.SetText(L"����");
	FridayEdit.SetTextSize(25);
	AddUiWin(&FridayEdit);

	SaturdayEdit.SetID(MZ_IDC_SAT_EDIT);
	SaturdayEdit.SetPos(320,310,160,MZM_HEIGHT_SUBJECT);
	SaturdayEdit.SetText(L"��ĩ");
	SaturdayEdit.SetTextSize(25);
	AddUiWin(&SaturdayEdit);

	SundayEdit.SetID(MZ_IDC_SUN_EDIT);
	SundayEdit.SetPos(320,470,160,MZM_HEIGHT_SUBJECT);
	SundayEdit.SetText(L"������");
	SundayEdit.SetTextSize(25);
//	AddUiWin(&SundayEdit);

	m_Bottom_Edit.SetID(MZ_IDC_BOTTOM_EDIT);
	m_Bottom_Edit.SetPos(0,GetHeight()-MZM_HEIGHT_BOTTOM,GetWidth(),MZM_HEIGHT_BOTTOM);
	m_Bottom_Edit.SetButton(0,true,true,L"����");
	m_Bottom_Edit.SetButton(1,true,true,L"�½�");
	m_Bottom_Edit.SetButton(2,true,true,L"�ؽ�");
//	m_Bottom.SetButton(3,true,true,L"�ռ�");
	AddUiWin(&m_Bottom_Edit);

	for(int i=0;i<5;++i)
	{
		MonEdit[i].SetID(MZ_IDC_MON_1_EDIT+i);
		MonEdit[i].SetPos(0,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		MonEdit[i].SetButtonType(MZC_BUTTON_PELLUCID);
		MonEdit[i].SetText(L"�༭");
		AddUiWin(&MonEdit[i]);

		TuesEdit[i].SetID(MZ_IDC_TUES_1_EDIT+i);
		TuesEdit[i].SetPos(160,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		TuesEdit[i].SetButtonType(MZC_BUTTON_PELLUCID);
		TuesEdit[i].SetText(L"�༭");
		AddUiWin(&TuesEdit[i]);

		WedEdit[i].SetID(MZ_IDC_WED_1_EDIT+i);
		WedEdit[i].SetPos(320,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		WedEdit[i].SetButtonType(MZC_BUTTON_PELLUCID);
		WedEdit[i].SetText(L"�༭");
		AddUiWin(&WedEdit[i]);

		ThursEdit[i].SetID(MZ_IDC_THURS_1_EDIT+i);
		ThursEdit[i].SetPos(0,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		ThursEdit[i].SetButtonType(MZC_BUTTON_PELLUCID);
		ThursEdit[i].SetText(L"�༭");
		AddUiWin(&ThursEdit[i]);

		FriEdit[i].SetID(MZ_IDC_FRI_1_EDIT+i);
		FriEdit[i].SetPos(160,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		FriEdit[i].SetButtonType(MZC_BUTTON_PELLUCID);
		FriEdit[i].SetText(L"�༭");
		AddUiWin(&FriEdit[i]);

		SatEdit[i].SetID(MZ_IDC_SAT_1_EDIT+i);
		SatEdit[i].SetPos(320,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		SatEdit[i].SetButtonType(MZC_BUTTON_PELLUCID);
		SatEdit[i].SetText(L"�༭");
		AddUiWin(&SatEdit[i]);
	}

    return TRUE;
  }

  // ����������Ϣ�Ĵ�������
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_BOTTOM_EDIT:
      {
        int nIndex=lParam;
		  if(nIndex==0)
		  {
			  EndModal(MZ_IDC_BOTTOM_EDIT);
		  }
		  else if(nIndex==1)
		  {
			  IniSchedule begininit;
			  RECT rcWork = MzGetWorkArea();
			  begininit.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
			  begininit.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
			  begininit.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
			  begininit.DoModal();
		  }

      break;
	  }
	}
	if((id>=MZ_IDC_MON_1_EDIT)&&(id<=MZ_IDC_SAT_5_EDIT))
	{
		BeginEdit beginedit;
		RECT rcWork = MzGetWorkArea();
	    beginedit.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		CMzString msg(256);
		weekEdit=(id%100)/10;
		classEdit=id%10;
		swprintf(msg.C_Str(),L"���� %d   �� %d �ڿ�",weekEdit,classEdit);
		beginedit.EditCaption.SetText(msg);
		beginedit.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
		beginedit.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
		beginedit.DoModal();
	}
		
  }
};


//MZ_IMPLEMENT_DYNAMIC(ScheduleEditWnd)

class CSample1MainWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(CSample1MainWnd);
public:
  // �����еİ�ť�ؼ�
  UiButton m_btn;

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
    m_btn.SetButtonType(MZC_BUTTON_GREEN);
    m_btn.SetPos(0,250,480,100);
    m_btn.SetID(MZ_IDC_TESTBTN1);
    m_btn.SetText(L"��ӭʹ��M8ѧ������");
    m_btn.SetTextColor(RGB(255,255,255));

              // �ѿؼ����ӵ�������
    AddUiWin(&m_btn);

    return TRUE;
  }

  // ����������Ϣ�Ĵ�������   L"You have pressed Exit button, Really want exit?"
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_TESTBTN1:
      {
		  CMzString i=L"����";
		  CMzString q=L"";
		  int j=2009;
		  wsprintf(q.C_Str(),L"%s%s%d%s",L"����",i.C_Str(),j,L"��");
        //if(1 == MzMessageBoxEx(m_hWnd, q, L"Exit", MB_YESNO, false))
          EndModal(MZ_IDC_TESTBTN1);
      }
      break;
    }
  }
};

//MZ_IMPLEMENT_DYNAMIC(CSample1MainWnd)

//������
class MainWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(MainWnd);
public:
  // �����еİ�ť�ؼ�
  UiCaption Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday;
  UiStatic Mon[5],Tues[5],Wed[5],Thurs[5],Fri[5],Sat[5],Sun[5];
  UiToolbar_Text m_Bottom;


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

	Monday.SetID(MZ_IDC_MON);
	Monday.SetPos(0,0,160,MZM_HEIGHT_SUBJECT);
	Monday.SetText(L"��һ");
	Monday.SetTextSize(25);
	AddUiWin(&Monday);

	Tuesday.SetID(MZ_IDC_TUES);
	Tuesday.SetPos(160,0,160,MZM_HEIGHT_SUBJECT);
	Tuesday.SetText(L"�ܶ�");
	Tuesday.SetTextSize(25);
	AddUiWin(&Tuesday);

	Wednesday.SetID(MZ_IDC_WED);
	Wednesday.SetPos(320,0,160,MZM_HEIGHT_SUBJECT);
	Wednesday.SetText(L"����");
	Wednesday.SetTextSize(25);
	AddUiWin(&Wednesday);

	Thursday.SetID(MZ_IDC_THURS);
	Thursday.SetPos(0,310,160,MZM_HEIGHT_SUBJECT);
	Thursday.SetText(L"����");
	Thursday.SetTextSize(25);
	AddUiWin(&Thursday);

	Friday.SetID(MZ_IDC_FRI);
	Friday.SetPos(160,310,160,MZM_HEIGHT_SUBJECT);
	Friday.SetText(L"����");
	Friday.SetTextSize(25);
	AddUiWin(&Friday);

	Saturday.SetID(MZ_IDC_SAT);
	Saturday.SetPos(320,310,160,MZM_HEIGHT_SUBJECT);
	Saturday.SetText(L"��ĩ");
	Saturday.SetTextSize(25);
	AddUiWin(&Saturday);

	Sunday.SetID(MZ_IDC_SUN);
	Sunday.SetPos(320,470,160,MZM_HEIGHT_SUBJECT);
	Sunday.SetText(L"������");
	Sunday.SetTextSize(25);
//	AddUiWin(&Sunday);

	m_Bottom.SetID(MZ_IDC_BOTTOM );
	m_Bottom.SetPos(0,GetHeight()-MZM_HEIGHT_BOTTOM,GetWidth(),MZM_HEIGHT_BOTTOM);
	m_Bottom.SetButton(0,true,true,L"�γ�");
	m_Bottom.SetButton(1,true,true,L"�༭");
	m_Bottom.SetButton(2,true,true,L"�˳�");
//	m_Bottom.SetButton(3,true,true,L"�ռ�");
	AddUiWin(&m_Bottom);

	for(int i=0;i<5;++i)
	{
		Mon[i].SetID(MZ_IDC_MON_1+i);
		Mon[i].SetPos(0,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		Mon[i].SetText(L"<�޿�>");
		AddUiWin(&Mon[i]);

		Tues[i].SetID(MZ_IDC_TUES_1+i);
		Tues[i].SetPos(160,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		Tues[i].SetText(L"<�޿�>");
		AddUiWin(&Tues[i]);

		Wed[i].SetID(MZ_IDC_WED_1+i);
		Wed[i].SetPos(320,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK,160,MZM_HEIGHT_SUBJECT);
		Wed[i].SetText(L"<�޿�>");
		AddUiWin(&Wed[i]);

		Thurs[i].SetID(MZ_IDC_THURS_1+i);
		Thurs[i].SetPos(0,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		Thurs[i].SetText(L"<�޿�>");
		AddUiWin(&Thurs[i]);

		Fri[i].SetID(MZ_IDC_FRI_1+i);
		Fri[i].SetPos(160,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		Fri[i].SetText(L"<�޿�>");
		AddUiWin(&Fri[i]);

		Sat[i].SetID(MZ_IDC_SAT_1+i);
		Sat[i].SetPos(320,i*MZM_HEIGHT_SUBJECT+MZM_HEIGHT_DAYINWEEK+310,160,MZM_HEIGHT_SUBJECT);
		Sat[i].SetText(L"<�޿�>");
		AddUiWin(&Sat[i]);
	}



	//��ӭ����
	
	CSample1MainWnd welcome;
	RECT rcWork = MzGetWorkArea();
	welcome.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),
	m_hWnd, 0, WS_POPUP);
	welcome.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_PUSH);
	welcome.SetAnimateType_Hide(MZ_ANIMTYPE_FADE);
//	welcome.DoModal();




           
 

    return TRUE;
  }

  // ����������Ϣ�Ĵ�������
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
			  if(1 == MzMessageBoxEx(m_hWnd, L"��ȷ��Ҫ�˳�?", L"Exit", MB_YESNO, false))
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

		//    ò�Ʋ���Ҫ����...........
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


// �� CMzApp ������Ӧ�ó�����
class MainApp: public CMzApp
{
public:
  // Ӧ�ó����������
  MainWnd m_MainWnd;
  

  // Ӧ�ó���ĳ�ʼ��
  virtual BOOL Init()
  {
              // ��ʼ�� COM ���
    CoInitializeEx(0, COINIT_MULTITHREADED);

              // ����������
    RECT rcWork = MzGetWorkArea();
    m_MainWnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),0, 0, 0);
    m_MainWnd.Show();

              // �ɹ��򷵻�TRUE
    return TRUE;
  }
};




// �� CMzWndEx ��������������