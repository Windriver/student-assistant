


//����MZFC���ͷ�ļ�
#include <mzfc_inc.h>
#include "welcome.h"
#include "define.h"
#include "ScheduleEdit.h"


//�˴�����ʾ�ˣ�
//  �����ͳ�ʼ��Ӧ�ó���
//  �����ͳ�ʼ������
//  ��ť�ؼ���ʹ�ü���������Ϣ�Ĵ���





// �� CMzWndEx ��������������
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

  // ����������Ϣ�Ĵ�����
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

// ȫ�ֵ�Ӧ�ó������
//MainApp theApp;
