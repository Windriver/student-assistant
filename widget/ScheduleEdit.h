
#include <mzfc_inc.h>
//#include <mzfc/ConvertHelper.h>   //ʹ�������ᵼ��LINK2005���Ӵ���

#include <Sqlite/CppSQLite3U.h>
#include "M8Date.h"
#include "define.h"


//�˴�����ʾ�ˣ�
//  �����ͳ�ʼ��Ӧ�ó���
//  �����ͳ�ʼ������
//  ��ť�ؼ���ʹ�ü���������Ϣ�Ĵ���

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

  // ����������Ϣ�Ĵ�����
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

  // ����������Ϣ�Ĵ�����
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

  // ����������Ϣ�Ĵ�����
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


