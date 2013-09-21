#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <Sqlite/CppSQLite3U.h>
#include "M8Date.h"


//此代码演示了：
//  创建和初始化应用程序
//  创建和初始化窗体
//  按钮控件的使用及其命令消息的处理

//两个全局变量记录了待编辑课程的所在周和所处第几节课
int weekEdit,classEdit;


//开始具体编辑课程时的窗口
class BeginEdit: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(BeginEdit);
public:
  // 窗口中的按钮控件
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

  UiScrollWin m_text_showsubject;
  UiStatic *pText;

  UiButton m_edit_Line[2];
  UiCaption m_edit_Cap[3];



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

	m_text_showsubject.SetPos(0,350,480,264);
	m_text_showsubject.SetID(MZ_IDC_SCROLL);
	AddUiWin(&m_text_showsubject);

	EditCaption.SetID(MZ_IDC_CAPTION_EDIT);
	EditCaption.SetPos(0,0,480,MZM_HEIGHT_CAPTION_SH_EDIT);
    EditCaption.SetTextSize(25);
    AddUiWin(&EditCaption);

	m_edit_Cap[0].SetPos(0,315,170,35);
	m_edit_Cap[0].SetText(L"始末周次");
	AddUiWin(&m_edit_Cap[0]);

	m_edit_Cap[1].SetPos(170,315,140,35);
	m_edit_Cap[1].SetText(L"课程");
	AddUiWin(&m_edit_Cap[1]);

	m_edit_Cap[2].SetPos(310,315,170,35);
	m_edit_Cap[2].SetText(L"教室");
	AddUiWin(&m_edit_Cap[2]);

	m_edit_Line[0].SetPos(170,350,3,264);
	m_edit_Line[0].SetButtonType(MZC_BUTTON_LINE_RIGHT);
	AddUiWin(&m_edit_Line[0]);

	m_edit_Line[1].SetPos(310,350,3,264);
	m_edit_Line[1].SetButtonType(MZC_BUTTON_LINE_RIGHT);
	AddUiWin(&m_edit_Line[1]);

	m_edit_begweek.SetID(MZ_IDC_BEGWEEK);
	m_edit_begweek.SetPos(100,60,100,60);
	m_edit_begweek.SetTextSize(MZFS_MAX);
	m_edit_begweek.SetSipMode(IM_SIP_MODE_DIGIT);
	m_edit_begweek.SetTip2(L"周", true);
	m_edit_begweek.SetRightInvalid(40);
	AddUiWin(&m_edit_begweek);

	m_edit_endweek.SetID(MZ_IDC_ENDWEEK);
	m_edit_endweek.SetPos(340,60,100,60);
	m_edit_endweek.SetTextSize(MZFS_MAX);
	m_edit_endweek.SetSipMode(IM_SIP_MODE_DIGIT);
	m_edit_endweek.SetTip2(L"周", true);
	m_edit_endweek.SetRightInvalid(40);
	AddUiWin(&m_edit_endweek);

	m_edit_subject.SetID(MZ_IDC_SUBJECT);
	m_edit_subject.SetPos(GetWidth()-210,130,200,60);
	m_edit_subject.SetTextSize(MZFS_MAX);
	m_edit_subject.SetSipMode(IM_SIP_MODE_GEL_PY);
	m_edit_subject.SetTip(L"请最多六字");
//	m_edit_subject.SetRightInvalid(40);
	AddUiWin(&m_edit_subject);

	m_edit_classroom.SetID(MZ_IDC_CLASSROOM);
	m_edit_classroom.SetPos(GetWidth()-160,200,150,60);
	m_edit_classroom.SetTextSize(MZFS_MAX);
	m_edit_classroom.SetSipMode(IM_SIP_MODE_GEL_LETTER);
	AddUiWin(&m_edit_classroom);

	m_text_begweek.SetPos(50,60,60,60);
	m_text_begweek.SetText(L"从");
	m_text_begweek.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_begweek);

	m_text_endweek.SetPos(290,60,60,60);
	m_text_endweek.SetText(L"到");
	m_text_endweek.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_endweek);

	m_text_subject.SetPos(50,130,100,60);
	m_text_subject.SetText(L"课程:");
	m_text_subject.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_subject);

	m_text_classroom.SetPos(50,200,100,60);
	m_text_classroom.SetText(L"教室:");
	m_text_classroom.SetTextSize(MZFS_MAX);
	AddUiWin(&m_text_classroom);

	
	m_Bottom_Edit_1.SetID(MZ_IDC_BOTTOM_EDIT_1);
	m_Bottom_Edit_1.SetPos(0,GetHeight()-70,480,70);
	m_Bottom_Edit_1.SetButton(0,true,true,L"取消编辑");
	m_Bottom_Edit_1.SetButton(2,true,true,L"保存编辑");
	AddUiWin(&m_Bottom_Edit_1);

	ShowSubject();

    return TRUE;
  }

  // 重载命令消息的处理函数
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
		  if(nIndex==2)
		  {			  
			   if(1 == MzMessageBoxEx(m_hWnd, L"你确定要编辑吗?", L"Exit", MB_YESNO, false))
			   {
				   InserToSqlite3();
				   this->m_edit_begweek.SetFocus(false);
				   this->m_edit_endweek.SetFocus(false);
				   this->m_edit_subject.SetFocus(false);
				   this->m_edit_classroom.SetFocus(false);
				   this->m_edit_begweek.SetText(this->m_edit_endweek.GetText());
				   this->m_edit_endweek.SetText(L"");
				   this->m_edit_subject.SetText(L"");
				   this->m_edit_classroom.SetText(L"");
				   ShowSubject();				   
			    }	
		  }       
      }
      break;
    }
  }

public:
  //将编辑后的信息加入sqlite3数据库
  void InserToSqlite3()
  {
	  CppSQLite3DB db;
	  db.open(L"Schedule.db");
	  CMzString sql(200),class_edit(10),room_edit(20);  //CMzString默认分配的字节不够下面的查询语句用的............

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
	  db.execDML(sql);


	//  db.execDML(L"insert into schedule values (1,1,'wawawa','a210');");
//	  db.execDML(L"insert into schedule values (2,1,'hh','a210');"); 

	  db.close();
	  
	  return;
  }

  void ShowSubject()
  {
	  m_text_showsubject.RemoveAllChildren();
	  CppSQLite3DB db;
	  CppSQLite3Query *pQuery;
	  db.open(L"Schedule.db");
	  CMzString szsql(200),class_edit(10),room_edit(20);
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
	  if(db.tableExists(L"schedule"))
	  {	  
		  wsprintf(szsql.C_Str(),L"select * from schedule where dayweek = '%d' order by date;",weekEdit);
		  pQuery=db.execQuery(szsql);
//		  MzMessageBoxEx(m_hWnd, szsql, L"提醒");
		  CMzString class_select(10),room_select(10),class_begin(5),class_end(5);
		  class_select=pQuery->fieldValue(class_edit);
		  room_select=pQuery->fieldValue(room_edit);
		  class_begin=pQuery->fieldValue(L"week");
		  class_end=class_begin;

		  int i=0;
		  CMzString tobePrint(50);
		  while(!pQuery->eof())
		  {
			  pQuery->nextRow();
			  if(class_select.Compare(pQuery->fieldValue(class_edit))==0)
			  {
				  class_end=pQuery->fieldValue(L"week");
				//  MzMessageBoxEx(m_hWnd, class_begin, L"提醒");
			  }
			  else
			  {
				  if(class_begin.Compare(class_end.C_Str())==0)
				  {
						  wsprintf(tobePrint.C_Str(),L"第 %s 周",class_begin.C_Str());
						  pText=new UiStatic;
						  pText->SetPos(50,0+40*i,120,40);
						  pText->SetText(tobePrint);
						  m_text_showsubject.AddChild(pText);
						  pText=new UiStatic;
						  pText->SetPos(170,0+40*i,140,40);
						  pText->SetText(class_select);
						  m_text_showsubject.AddChild(pText);
						  pText=new UiStatic;
						  pText->SetPos(310,0+40*i,120,40);
						  pText->SetText(room_select);
						  m_text_showsubject.AddChild(pText);
						  ++i;						    
				  }
				  else
				  {
						  wsprintf(tobePrint.C_Str(),L"%s-%s 周",class_begin.C_Str(),class_end.C_Str());
						  pText=new UiStatic;
						  pText->SetPos(50,0+40*i,120,40);
						  pText->SetText(tobePrint);
						  m_text_showsubject.AddChild(pText);
						  pText=new UiStatic;
						  pText->SetPos(170,0+40*i,140,40);
						  pText->SetText(class_select);
						  m_text_showsubject.AddChild(pText);
						  pText=new UiStatic;
						  pText->SetPos(310,0+40*i,120,40);
						  pText->SetText(room_select);
						  m_text_showsubject.AddChild(pText);

						  ++i;  
				  }
			//	  MzMessageBoxEx(m_hWnd, tobePrint, L"提醒");
				  class_select=pQuery->fieldValue(class_edit);
				  room_select=pQuery->fieldValue(room_edit);
				  class_begin=pQuery->fieldValue(L"week");
				  class_end=class_begin;
			  }
		  }
		  
		 
			
	  
	  }

  }
  void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
  {
	  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
      {
		  this->m_edit_begweek.SetFocus(false);
		  this->m_edit_classroom.SetFocus(false);
		  this->m_edit_endweek.SetFocus(false);
		  this->m_edit_subject.SetFocus(false);          
      }
  }


  ~ BeginEdit()
  {
	  delete []pText;
  }
};

MZ_IMPLEMENT_DYNAMIC(BeginEdit)


class IniSchedule: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(IniSchedule);
public:
  // 窗口中的按钮控件
	UiCaption caption_init;
	UiStatic ini_Static;
	UiSingleLineEdit first_y;
	UiSingleLineEdit first_m;
	UiSingleLineEdit first_d;
	UiSingleLineEdit first_w;
	UiToolbar_Text bottom_init;
	UiButton ini_WeekBtn;
	UiStatic ini_Static_week;
	UiStatic ini_Static_man[3];
	UiCaption ini_cap_man;


  
private:
	bool weekIsSet;
	int dayweek;
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
	caption_init.SetPos(0,0,480,MZM_HEIGHT_CAPTION_SH_EDIT);
    caption_init.SetTextSize(25);
	caption_init.SetText(L"正在创建一张新的课程表");
    AddUiWin(&caption_init);

	weekIsSet=false;
	dayweek=1;

	ini_WeekBtn.SetButtonType(MZC_BUTTON_GRAY);
    ini_WeekBtn.SetID(MZ_IDC_BEGIN_DAYWEEK);
    ini_WeekBtn.SetPos(270, 200, 180, 70);  
    ini_WeekBtn.SetTextColor(RGB(0, 0, 0));
	ini_WeekBtn.SetText(L"星期一");
    AddUiWin(&ini_WeekBtn);

	ini_Static_week.SetPos(5,210,250,60);
//	ini_Static_week.SetTextColor( RGB(165 ,42, 42 ));
	ini_Static_week.SetText(L"请输入开学星期:");
	AddUiWin(&ini_Static_week);

	bottom_init.SetPos(0,GetHeight()-70,480,70);
	bottom_init.SetID(MZ_IDC_BOTTOM_INIT);
	bottom_init.SetButton(0,true,true,L"取消新建");
    bottom_init.SetButton(2,true,true,L"确定新建");
	AddUiWin(&bottom_init);   

	ini_Static.SetPos(5,50,250,60);
	ini_Static.SetText(L"请输入开学日期:");
	AddUiWin(&ini_Static);

	first_y.SetID(MZ_IDC_FIRST_Y);
	first_y.SetPos(300,60,150,60);
	first_y.SetTextSize(MZFS_MAX);
	first_y.SetSipMode(IM_SIP_MODE_DIGIT);
	first_y.SetTip2(L"年", true);
	first_y.SetRightInvalid(40);
	AddUiWin(&first_y);

	first_m.SetID(MZ_IDC_FIRST_M);
	first_m.SetPos(160,130,120,60);
	first_m.SetTextSize(MZFS_MAX);
	first_m.SetSipMode(IM_SIP_MODE_DIGIT);
	first_m.SetTip2(L"月", true);
	first_m.SetRightInvalid(40);
	AddUiWin(&first_m);

	first_d.SetID(MZ_IDC_FIRST_D);
	first_d.SetPos(330,130,120,60);
	first_d.SetTextSize(MZFS_MAX);
	first_d.SetSipMode(IM_SIP_MODE_DIGIT);
	first_d.SetTip2(L"日", true);;
	first_d.SetRightInvalid(40);
	AddUiWin(&first_d);

	first_w.SetID(MZ_IDC_FIRST_W);
	first_w.SetPos(GetWidth()-160,200,150,60);
	first_w.SetTextSize(MZFS_MAX);
	first_w.SetSipMode(IM_SIP_MODE_DIGIT);
	first_w.SetTip2(L"周", true);;
	first_w.SetRightInvalid(40);
//	AddUiWin(&first_w);

	ini_cap_man.SetPos(-50,300,580,20);
//	ini_cap_man.SetButtonType(MZCV2_BUTTON_GRAY);
	AddUiWin(&ini_cap_man);

	ini_Static_man[1].SetPos(10,330,460,40);
	ini_Static_man[1].SetTextColor( RGB(165 ,42, 42 ));
	ini_Static_man[1].SetText(L"注意: 请正确填写，并一定要保证开学日期");
	AddUiWin(&ini_Static_man[1]);

	ini_Static_man[2].SetPos(10,370,460,40);
	ini_Static_man[2].SetTextColor( RGB(165 ,42, 42 ));
	ini_Static_man[2].SetText(L" 与开学那天的星期相对应，最好参考日历。 ");
	AddUiWin(&ini_Static_man[2]);

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
	  case MZ_IDC_BEGIN_DAYWEEK:
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
					ini_WeekBtn.SetText(L"星期一");
					dayweek=1;
					weekIsSet=true;
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					ini_WeekBtn.SetText(L"星期二");
					dayweek=2;
					weekIsSet=true;
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					ini_WeekBtn.SetText(L"星期三");
					dayweek=3;
					weekIsSet=true;
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					ini_WeekBtn.SetText(L"星期四");
					dayweek=4;
					weekIsSet=true;
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					ini_WeekBtn.SetText(L"星期五");
					dayweek=5;
					weekIsSet=true;
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					ini_WeekBtn.SetText(L"星期六");
					dayweek=6;
					weekIsSet=true;
					break;
				}
			case MZV2_MID_MIN + 7:
				{
					ini_WeekBtn.SetText(L"星期天");
					dayweek=7;
					weekIsSet=true;
					break;
				}			
			}
			break;
		}
    case MZ_IDC_BOTTOM_INIT:
      {
		  int nIndex=lParam;
		  if(0==nIndex)
		  {
			  EndModal(MZ_IDC_BOTTOM_INIT);
		  }
		  if(2==nIndex)
		  {
			  if(weekIsSet)
			  {
				  if(1 == MzMessageBoxEx(m_hWnd, L"你确定将开学日期和星期都填对了吗?", L"Exit", MB_YESNO, false))
				  {
					  MzAutoMsgBoxEx(m_hWnd, L"正在初始化课程表,请等待...", 3000);
					  NewSchedule();
					  EndModal(MZ_IDC_BOTTOM_INIT);
				   }
			  }
		  }
		break;
		  
      
	  }
	}
  }

public:
  void NewSchedule()
  {
	  CppSQLite3DB db;
	  db.open(L"Schedule.db");                        //数据库名字后面不带";"
	  db.execDML(L"drop table schedule");
	  if(!db.tableExists(L"schedule"))
	  {
		  int y=_ttoi(this->first_y.GetText());
		  int m=_ttoi(this->first_m.GetText());
		  int d=_ttoi(this->first_d.GetText());
		  int w=this->dayweek;
		  M8Date mdate(y,m,d,w);			//数据库中的标识符貌似不能用数字....................

	
		  db.execDML(L"create table schedule (date char(12),week int,dayweek int,first_c char(20),first_r char(20),second_c char(20),second_r char(20),third_c char(20),third_r char(20),fouth_c char(20),fouth_r char(20),fifth_c char(20),fifth_r char(20));");// 
		  CMzString szsql(200),szdate(40),szmonth(10),szday(10);
		  for(int i=1;i<=200;i++)
		  {
			  if(mdate.Getmonth()<10)
			  {
				  wsprintf(szmonth.C_Str(),L"%s%d",L"0",mdate.Getmonth());
			  }
			  else                                                  //月份小于10是也要转换成CMzString!!!!!!!!
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
//			  wsprintf(szsql.C_Str(),L"%s%s,%d,%d%s",L"insert into schedule (date,week,dayweek,first_c,first_r,second_c,second_r,third_c,third_r,fouth_c,fouth_r,fifth_c,fifth_r) values (",szdate.C_Str(),w,d,L",'休息','╱','休息','╱','休息','╱','休息','╱','休息','╱');");
			  wsprintf(szsql.C_Str(),L"%s%s,%d,%d%s",L"insert into schedule (date,week,dayweek,first_c,first_r,second_c,second_r,third_c,third_r,fouth_c,fouth_r,fifth_c,fifth_r) values (",szdate.C_Str(),w,d,L",'','','','','','','','','','');");
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
  void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
  {
	  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
      {
		  this->first_d.SetFocus(false);
		  this->first_m.SetFocus(false);
		  this->first_w.SetFocus(false);
		  this->first_y.SetFocus(false);          
      }
  }


};  
MZ_IMPLEMENT_DYNAMIC(IniSchedule)






// 从 CMzWndEx 派生的主窗口类
class ScheduleEditWnd: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(ScheduleEditWnd);
public:
  // 窗口中的按钮控件
  UiCaption MondayEdit,TuesdayEdit,WednesdayEdit,ThursdayEdit,FridayEdit,SaturdayEdit,SundayEdit;
  UiButton MonEdit[5],TuesEdit[5],WedEdit[5],ThursEdit[5],FriEdit[5],SatEdit[5],SunEdit[5];
  UiToolbar_Text m_Bottom_Edit;
  UiStatic e_which_o[6];
  UiStatic e_which_u[6];
  UiCaption e_Caption;
  UiCaption keci[2];
  UiButton e_Line[5];
  UiStatic e_Man;


protected:
  // 窗口的初始化
  virtual BOOL OnInitDialog()
  {
    // 必须先调用基类的初始化
    if (!CMzWndEx::OnInitDialog())
    {
      return FALSE;
    }
	e_Caption.SetPos(0,0,480,MZM_HEIGHT_CAPTION_SH_EDIT-3);
	AddUiWin(&e_Caption);

	e_Line[0].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_SUBJECT_EDIT,100,MZM_HEIGHT_SUBJECT_EDIT);
	e_Line[0].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&e_Line[0]);

	e_Line[1].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_SUBJECT_EDIT*3,100,MZM_HEIGHT_SUBJECT_EDIT);
	e_Line[1].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&e_Line[1]);

	e_Line[2].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_SUBJECT_EDIT*6,100,MZM_HEIGHT_SUBJECT_EDIT);
	e_Line[2].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&e_Line[2]);

	e_Line[3].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_SUBJECT_EDIT*8,100,MZM_HEIGHT_SUBJECT_EDIT);
	e_Line[3].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&e_Line[3]);

	e_Line[4].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_SUBJECT_EDIT*10-2,100,3);
	e_Line[4].SetButtonType(MZC_BUTTON_LINE_TOPBOTTOM);
	AddUiWin(&e_Line[4]);

	e_Man.SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_SUBJECT_EDIT*10,480,65);
	e_Man.SetTextColor( RGB(165 ,42, 42 ));
	e_Man.SetText(L"提示: 点击按钮以编辑或查看相应的课次.");
	AddUiWin(&e_Man);

	keci[0].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+3,60,MZM_HEIGHT_SUBJECT_EDIT);
	keci[0].SetText(L"课次");
	keci[1].SetPos(0,MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_SUBJECT_EDIT*5+MZM_HEIGHT_DAYINWEEK_EDIT+3,60,MZM_HEIGHT_SUBJECT_EDIT);
	keci[1].SetText(L"课次");
	AddUiWin(&keci[0]);
	AddUiWin(&keci[1]);

	CMzString classnumber;
	for(int i=1;i<6;++i)
	{
		e_which_o[i].SetPos(0,(i-1)*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT,60,MZM_HEIGHT_SUBJECT_EDIT);
		e_which_u[i].SetPos(0,(i+4)*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_CAPTION_SH_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2,60,MZM_HEIGHT_SUBJECT_EDIT);
		wsprintf(classnumber.C_Str(),L"%d",i);
		e_which_o[i].SetText(classnumber);
		e_which_u[i].SetText(classnumber);
		AddUiWin(&e_which_o[i]);
		AddUiWin(&e_which_u[i]);
	}

	MondayEdit.SetID(MZ_IDC_MON_EDIT);
	MondayEdit.SetPos(60,MZM_HEIGHT_CAPTION_SH_EDIT+3,140,MZM_HEIGHT_SUBJECT_EDIT);
	MondayEdit.SetText(L"周一");
	MondayEdit.SetTextSize(25);
	AddUiWin(&MondayEdit);

	TuesdayEdit.SetID(MZ_IDC_TUES_EDIT);
	TuesdayEdit.SetPos(200,MZM_HEIGHT_CAPTION_SH_EDIT+3,140,MZM_HEIGHT_SUBJECT_EDIT);
	TuesdayEdit.SetText(L"周二");
	TuesdayEdit.SetTextSize(25);
	AddUiWin(&TuesdayEdit);

	WednesdayEdit.SetID(MZ_IDC_WED_EDIT);
	WednesdayEdit.SetPos(340,MZM_HEIGHT_CAPTION_SH_EDIT+3,140,MZM_HEIGHT_SUBJECT_EDIT);
	WednesdayEdit.SetText(L"周三");
	WednesdayEdit.SetTextSize(25);
	AddUiWin(&WednesdayEdit);

	ThursdayEdit.SetID(MZ_IDC_THURS_EDIT);
	ThursdayEdit.SetPos(60,MZM_HEIGHT_CAPTION_SH_EDIT+3+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_SUBJECT_EDIT*5,140,MZM_HEIGHT_SUBJECT_EDIT);
	ThursdayEdit.SetText(L"周四");
	ThursdayEdit.SetTextSize(25);
	AddUiWin(&ThursdayEdit);

	FridayEdit.SetID(MZ_IDC_FRI_EDIT);
	FridayEdit.SetPos(200,MZM_HEIGHT_CAPTION_SH_EDIT+3+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_SUBJECT_EDIT*5,140,MZM_HEIGHT_SUBJECT_EDIT);
	FridayEdit.SetText(L"周五");
	FridayEdit.SetTextSize(25);
	AddUiWin(&FridayEdit);

	SaturdayEdit.SetID(MZ_IDC_SAT_EDIT);
	SaturdayEdit.SetPos(340,MZM_HEIGHT_CAPTION_SH_EDIT+3+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_SUBJECT_EDIT*5,140,MZM_HEIGHT_SUBJECT_EDIT);
	SaturdayEdit.SetText(L"周末");
	SaturdayEdit.SetTextSize(25);
	AddUiWin(&SaturdayEdit);

	SundayEdit.SetID(MZ_IDC_SUN_EDIT);
	SundayEdit.SetPos(320,470,160,MZM_HEIGHT_SUBJECT_EDIT);
	SundayEdit.SetText(L"星期天");
	SundayEdit.SetTextSize(25);
//	AddUiWin(&SundayEdit);

	m_Bottom_Edit.SetID(MZ_IDC_BOTTOM_EDIT);
	m_Bottom_Edit.SetPos(0,GetHeight()-70,GetWidth(),70);
	m_Bottom_Edit.EnableLeftArrow(true);
	m_Bottom_Edit.SetButton(0,true,true,L"返回");
//	m_Bottom_Edit.SetButton(1,true,true,L"新建");
//	m_Bottom_Edit.SetButton(2,true,true,L"帮助");
	AddUiWin(&m_Bottom_Edit);

	for(int i=0;i<5;++i)
	{
		MonEdit[i].SetID(MZ_IDC_MON_1_EDIT+i);
		MonEdit[i].SetPos(60,i*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_CAPTION_SH_EDIT,140,MZM_HEIGHT_SUBJECT_EDIT-2);
		MonEdit[i].SetButtonType(MZC_BUTTON_DELETE_ORANGE);
		MonEdit[i].SetText(L"编辑/查看");
		AddUiWin(&MonEdit[i]);

		TuesEdit[i].SetID(MZ_IDC_TUES_1_EDIT+i);
		TuesEdit[i].SetPos(200-10,i*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_CAPTION_SH_EDIT,140+20,MZM_HEIGHT_SUBJECT_EDIT-2);
		TuesEdit[i].SetButtonType(MZC_BUTTON_GREEN);
		TuesEdit[i].SetText(L"编辑/查看");
		AddUiWin(&TuesEdit[i]);

		WedEdit[i].SetID(MZ_IDC_WED_1_EDIT+i);
		WedEdit[i].SetPos(340,i*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT+MZM_HEIGHT_CAPTION_SH_EDIT,140,MZM_HEIGHT_SUBJECT_EDIT-2);
		WedEdit[i].SetButtonType(MZC_BUTTON_DELETE_ORANGE);
		WedEdit[i].SetText(L"编辑/查看");
		AddUiWin(&WedEdit[i]);

		ThursEdit[i].SetID(MZ_IDC_THURS_1_EDIT+i);
		ThursEdit[i].SetPos(60-10,(i+5)*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_CAPTION_SH_EDIT,140+20,MZM_HEIGHT_SUBJECT_EDIT-2);
		ThursEdit[i].SetButtonType(MZC_BUTTON_GREEN);
		ThursEdit[i].SetText(L"编辑/查看");
		AddUiWin(&ThursEdit[i]);

		FriEdit[i].SetID(MZ_IDC_FRI_1_EDIT+i);
		FriEdit[i].SetPos(200,(i+5)*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_CAPTION_SH_EDIT,140,MZM_HEIGHT_SUBJECT_EDIT-2);
		FriEdit[i].SetButtonType(MZC_BUTTON_DELETE_ORANGE);
		FriEdit[i].SetText(L"编辑/查看");
		AddUiWin(&FriEdit[i]);

		SatEdit[i].SetID(MZ_IDC_SAT_1_EDIT+i);
		SatEdit[i].SetPos(340-10,(i+5)*MZM_HEIGHT_SUBJECT_EDIT+MZM_HEIGHT_DAYINWEEK_EDIT*2+MZM_HEIGHT_CAPTION_SH_EDIT,140+20,MZM_HEIGHT_SUBJECT_EDIT-2);
		SatEdit[i].SetButtonType(MZC_BUTTON_GREEN);
		SatEdit[i].SetText(L"编辑/查看");
		AddUiWin(&SatEdit[i]);
	}

	SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
	CMzString msg_today;
	wsprintf(msg_today.C_Str(),L"%d年%d月%d日",sysTime.wYear,sysTime.wMonth, sysTime.wDay);
    e_Caption.SetText(msg_today);

    return TRUE;
  }

  // 重载命令消息的处理函数
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
		weekEdit=(id%100)/10;
		classEdit=id%10;
		BeginEdit beginedit;
		RECT rcWork = MzGetWorkArea();
	    beginedit.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		CMzString msg(256);
		
		if(weekEdit==1)
		{
			swprintf(msg.C_Str(),L"星期一   第 %d 节课",classEdit);
		}
		else if(weekEdit==2)
		{
			swprintf(msg.C_Str(),L"星期二   第 %d 节课",classEdit);
		}
		else if(weekEdit==3)
		{
			swprintf(msg.C_Str(),L"星期三   第 %d 节课",classEdit);
		}
		else if(weekEdit==4)
		{
			swprintf(msg.C_Str(),L"星期四   第 %d 节课",classEdit);
		}
		else if(weekEdit==5)
		{
			swprintf(msg.C_Str(),L"星期五   第 %d 节课",classEdit);
		}
		else if(weekEdit==6)
		{
			swprintf(msg.C_Str(),L"周末   第 %d 节课",classEdit);
		}

		beginedit.EditCaption.SetText(msg);
		beginedit.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
		beginedit.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH );
		beginedit.DoModal();
	}
		
  }
};


MZ_IMPLEMENT_DYNAMIC(ScheduleEditWnd)

