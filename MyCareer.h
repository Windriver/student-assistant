#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <ReadWriteIni.h>
#include "Define.h"


//此代码演示了：
//  创建和初始化应用程序
//  创建和初始化窗体
//  时间日期设置对话框 MzSetDaily 的使用



class ColorfulCareer: public UiWin
{
private:
	float proportion;

public:
	ColorfulCareer()
	{
		proportion=0.5;
	}

	void SetProportion(float pro)
	{
		this->proportion=pro;
		this->Invalidate();
		this->Update();
	}	

	virtual void PaintWin(HDC hdcDst, RECT *prcWin, RECT *prcUpdate)
	{
		COLORREF clr = RGB(0 ,255 ,0);
		COLORREF clr_Important = RGB(255 ,0 ,0);
		COLORREF clr_Under_Line = RGB(0,0,0);
		COLORREF clr_Under = RGB(156  ,156  ,156   );
		COLORREF clr_White = RGB(255,255,255 );

		RECT rect=*prcWin;
		::InflateRect(&rect,-5,-5);
		DrawRoundRect(hdcDst,&rect,5,clr_Under,clr_Under);
		::InflateRect(&rect,-5,-5);

		RECT PastRect=rect;
		PastRect.right=PastRect.left+(PastRect.right-PastRect.left)*proportion;			  
		::DrawRect(hdcDst,&PastRect,clr_Important,clr_Important);

		RECT ToBePastRect=rect;
		ToBePastRect.left=PastRect.right;
		::DrawRect(hdcDst,&ToBePastRect,clr,clr);

		rect=*prcWin;
		rect.left=PastRect.right-2;
		rect.right=ToBePastRect.left+2;
		::DrawRoundRect(hdcDst,&rect,1,clr_Under,clr_Under);

	}
};

// 从 CMzWndEx 派生的窗口类
class CareerSetWnd : public CMzWndEx
{
    MZ_DECLARE_DYNAMIC(CareerSetWnd);
public:
	UiCaption       myc_caption;
	UiToolbar_Text  myc_bottom;
    UiButton        myc_DateBtn_Beg;
	UiButton        myc_DateBtn_End;
	UiButton        myc_DateBtn_ThisSem;
	UiButton        myc_DateBtn_ThisSem_end;
	UiStatic        myc_MsgStatic[6];
	UiButton        myc_Line[7];
	UiSingleLineEdit myc_Edit[2];

	int leftDay;


    SYSTEMTIME m_sTime;

protected:
    // 窗口初始化
    virtual BOOL OnInitDialog()
    {
        // 必须先调用基类的初始化
        if (!CMzWndEx::OnInitDialog())
        {
            return FALSE;
        }

		myc_caption.SetPos(0,0,480,60);
		myc_caption.SetTextSize(25);
		myc_caption.SetText(L"学生生涯设定");
		AddUiWin(&myc_caption);

		for(int i=0;i<7;++i)
		{
			myc_Line[i].SetPos(0,60+80*i,480,80);
			myc_Line[i].SetButtonType(MZC_BUTTON_LINE_TOP);
			AddUiWin(&myc_Line[i]);
		}

		for(int i=0;i<6;++i)
		{
			myc_MsgStatic[i].SetPos(15,60+80*i,200,80);
			myc_MsgStatic[i].SetDrawTextFormat(DT_LEFT|DT_VCENTER);
			AddUiWin(&myc_MsgStatic[i]);
		}

		for(int i=0;i<2;++i)
		{
			myc_Edit[i].SetPos(240,70+80*i,220,60);
			AddUiWin(&myc_Edit[i]);
		}

		myc_MsgStatic[0].SetText(L"阶段:");
		myc_MsgStatic[1].SetText(L"学校:");
		myc_MsgStatic[2].SetText(L"阶段开学日期:");
		myc_MsgStatic[3].SetText(L"阶段毕业日期:");
		myc_MsgStatic[4].SetText(L"本学期开始日期:");
		myc_MsgStatic[5].SetText(L"本学期结束日期:");



		myc_bottom.SetPos(0,GetHeight()-70,480,70);
		myc_bottom.SetID(MZ_MYC_BOTTOM);
		myc_bottom.SetButton(0,true,true,L"取消设定");
        myc_bottom.SetButton(2,true,true,L"保存设定");
//		myc_bottom.EnableLeftArrow(true);
	    AddUiWin(&myc_bottom);


        GetLocalTime(&m_sTime);

        CMzString str(128);
        
        myc_DateBtn_Beg.SetButtonType(MZC_BUTTON_GRAY);
        myc_DateBtn_Beg.SetID(MZ_MYC_DATE_BEG);
		myc_DateBtn_Beg.SetPos(240, 230, 220, 60);
		myc_DateBtn_Beg.SetTextSize(22);
        wsprintf(str.C_Str(), L"%d年%02d月%02d日", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
        myc_DateBtn_Beg.SetText(str.C_Str());
        myc_DateBtn_Beg.SetTextColor(RGB(0, 0, 0));
        AddUiWin(&myc_DateBtn_Beg);

		myc_DateBtn_End.SetButtonType(MZC_BUTTON_GRAY);
        myc_DateBtn_End.SetID(MZ_MYC_DATE_END);
        myc_DateBtn_End.SetPos(240, 310, 220, 60);
		myc_DateBtn_End.SetTextSize(22);
        myc_DateBtn_End.SetText(str.C_Str());
        myc_DateBtn_End.SetTextColor(RGB(0, 0, 0));
        AddUiWin(&myc_DateBtn_End);
		
		myc_DateBtn_ThisSem.SetButtonType(MZC_BUTTON_GRAY);
        myc_DateBtn_ThisSem.SetID(MZ_MYC_DATE_THISSEM);
        myc_DateBtn_ThisSem.SetPos(240, 390, 220, 60);
		myc_DateBtn_ThisSem.SetTextSize(22);
        myc_DateBtn_ThisSem.SetText(str.C_Str());
        myc_DateBtn_ThisSem.SetTextColor(RGB(0, 0, 0));
        AddUiWin(&myc_DateBtn_ThisSem);

		myc_DateBtn_ThisSem_end.SetButtonType(MZC_BUTTON_GRAY);
        myc_DateBtn_ThisSem_end.SetID(MZ_MYC_DATE_THISSEMEND);
        myc_DateBtn_ThisSem_end.SetPos(240, 470, 220, 60);
		myc_DateBtn_ThisSem_end.SetTextSize(22);
        myc_DateBtn_ThisSem_end.SetText(str.C_Str());
        myc_DateBtn_ThisSem_end.SetTextColor(RGB(0, 0, 0));
        AddUiWin(&myc_DateBtn_ThisSem_end);

		CppSQLite3DB db;
		db.open(L"Schedule.db");
		if(db.tableExists(L"mycareershow"))
		{
			CppSQLite3Query *pQuery;
			pQuery=db.execQuery(L"select * from mycareershow;");
			str=pQuery->fieldValue(L"career");
			myc_Edit[0].SetText(str.C_Str());
			str=pQuery->fieldValue(L"school");
			myc_Edit[1].SetText(str.C_Str());
			str=pQuery->fieldValue(L"careerbeg");
			myc_DateBtn_Beg.SetText(str.C_Str());
			str=pQuery->fieldValue(L"careerend");
			myc_DateBtn_End.SetText(str.C_Str());
			str=pQuery->fieldValue(L"sembeg");
			myc_DateBtn_ThisSem.SetText(str.C_Str());
			str=pQuery->fieldValue(L"semend");
			myc_DateBtn_ThisSem_end.SetText(str.C_Str());
				
			pQuery->finalize();
		}
		db.close();

        return TRUE;
    }

    // 重写命令消息的处理函数
    virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
    {
        UINT_PTR id = LOWORD(wParam);
        switch (id)
        {
        case MZ_MYC_DATE_BEG:
            {
                // 日期设置对话框的初始化数据
                MzSetDaily setDateDlg;
                setDateDlg.m_InitData.iItemCounter = 3;
                setDateDlg.m_InitData.iItem1Max = 2100 - 1923; // 年份是从1923年开始计算的
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
                    wsprintf(str.C_Str(), L"%d年%02d月%02d日", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
                    myc_DateBtn_Beg.SetText(str.C_Str());
                }

                break;            
			}

		case MZ_MYC_DATE_END:
            {
                // 日期设置对话框的初始化数据
                MzSetDaily setDateDlg;
                setDateDlg.m_InitData.iItemCounter = 3;
                setDateDlg.m_InitData.iItem1Max = 2100 - 1923; // 年份是从1923年开始计算的
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
                    wsprintf(str.C_Str(), L"%d年%02d月%02d日", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
                    myc_DateBtn_End.SetText(str.C_Str());
				//	CareerCount();
                }

                break;            
            }
        // 退出程序
       
		case MZ_MYC_DATE_THISSEM:
            {
                // 日期设置对话框的初始化数据
                MzSetDaily setDateDlg;
                setDateDlg.m_InitData.iItemCounter = 3;
                setDateDlg.m_InitData.iItem1Max = 2100 - 1923; // 年份是从1923年开始计算的
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
                    wsprintf(str.C_Str(), L"%d年%02d月%02d日", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
                    myc_DateBtn_ThisSem.SetText(str.C_Str());
                }

                break;            
            }
		case MZ_MYC_DATE_THISSEMEND:
            {
                // 日期设置对话框的初始化数据
                MzSetDaily setDateDlg;
                setDateDlg.m_InitData.iItemCounter = 3;
                setDateDlg.m_InitData.iItem1Max = 2100 - 1923; // 年份是从1923年开始计算的
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
                    wsprintf(str.C_Str(), L"%d年%02d月%02d日", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
                    myc_DateBtn_ThisSem_end.SetText(str.C_Str());
                }

                break;            
            }
		case MZ_MYC_BOTTOM:
			{   //MzMessageBoxEx(m_hWnd, L"哈哈", L"提醒");
				if(0==lParam)
				{
					EndModal(MZ_MYC_BOTTOM);
				}
				else if(2==lParam)
				{
					
					if(!(this->myc_Edit[0].GetText().IsEmpty()) && !(this->myc_Edit[1].GetText().IsEmpty()))
					{
						if(1 == MzMessageBoxEx(m_hWnd, L"确定要更新本阶段和本学期的日期信息吗?", L"Exit", MB_YESNO, false))
						{
								FILETIME tFrom,tTo; 
								FILETIME tFrom_sem,tTo_sem; 
								SYSTEMTIME m_time_from , m_time_to;
								SYSTEMTIME m_time_from_sem , m_time_to_sem;
								CMzString Time(50);

						//		GetLocalTime(&st);
						//		wsprintf(Time.C_Str(),L"%d-%d-%d-%d-%d-%d-%d-%d",st.wYear,st.wMonth,st.wDay,st.wDayOfWeek,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
								m_time_from.wYear=_ttoi(this->myc_DateBtn_Beg.GetText().SubStr(0,4));
								m_time_from.wMonth=_ttoi(this->myc_DateBtn_Beg.GetText().SubStr(5,2));
								m_time_from.wDay=_ttoi(this->myc_DateBtn_Beg.GetText().SubStr(8,2));
								m_time_from.wDayOfWeek=m_time_from.wHour=m_time_from.wMilliseconds=m_time_from.wMinute=m_time_from.wSecond=0;

								m_time_from_sem.wYear=_ttoi(this->myc_DateBtn_ThisSem.GetText().SubStr(0,4));
								m_time_from_sem.wMonth=_ttoi(this->myc_DateBtn_ThisSem.GetText().SubStr(5,2));
								m_time_from_sem.wDay=_ttoi(this->myc_DateBtn_ThisSem.GetText().SubStr(8,2));
								m_time_from_sem.wDayOfWeek=m_time_from_sem.wHour=m_time_from_sem.wMilliseconds=m_time_from_sem.wMinute=m_time_from_sem.wSecond=0;
							
						//wsprintf(Time.C_Str(),L"%d-%d-%d-%d-%d-%d-%d-%d",m_time_from.wYear,m_time_from.wMonth,m_time_from.wDay,m_time_from.wDayOfWeek,m_time_from.wHour,m_time_from.wMinute,m_time_from.wSecond,m_time_from.wMilliseconds);
						//MzMessageBoxEx(m_hWnd, Time, L"提醒");

								m_time_to.wYear=_ttoi(this->myc_DateBtn_End.GetText().SubStr(0,4));
								m_time_to.wMonth=_ttoi(this->myc_DateBtn_End.GetText().SubStr(5,2));
								m_time_to.wDay=_ttoi(this->myc_DateBtn_End.GetText().SubStr(8,2));
								m_time_to.wDayOfWeek=m_time_to.wHour=m_time_to.wMilliseconds=m_time_to.wMinute=m_time_to.wSecond=0;

								m_time_to_sem.wYear=_ttoi(this->myc_DateBtn_ThisSem_end.GetText().SubStr(0,4));
								m_time_to_sem.wMonth=_ttoi(this->myc_DateBtn_ThisSem_end.GetText().SubStr(5,2));
								m_time_to_sem.wDay=_ttoi(this->myc_DateBtn_ThisSem_end.GetText().SubStr(8,2));
								m_time_to_sem.wDayOfWeek=m_time_to_sem.wHour=m_time_to_sem.wMilliseconds=m_time_to_sem.wMinute=m_time_to_sem.wSecond=0;

								SystemTimeToFileTime(&m_time_from,&tFrom);
								SystemTimeToFileTime(&m_time_to,&tTo);
								SystemTimeToFileTime(&m_time_from_sem,&tFrom_sem);
								SystemTimeToFileTime(&m_time_to_sem,&tTo_sem);
								LARGE_INTEGER iFrom,iTo;
								LARGE_INTEGER iFrom_sem,iTo_sem;

								iFrom.HighPart=tFrom.dwHighDateTime;
								iFrom.LowPart=tFrom.dwLowDateTime;
								iTo.HighPart=tTo.dwHighDateTime;
								iTo.LowPart=tTo.dwLowDateTime;

								iFrom_sem.HighPart=tFrom_sem.dwHighDateTime;
								iFrom_sem.LowPart=tFrom_sem.dwLowDateTime;
								iTo_sem.HighPart=tTo_sem.dwHighDateTime;
								iTo_sem.LowPart=tTo_sem.dwLowDateTime;

								time_t tF,tT;                  //转换成time_t 类型 单位为秒
								tF=(iFrom.QuadPart-116444736000000000)/10000000;
								tT=(iTo.QuadPart-116444736000000000)/10000000;   

								time_t tF_sem,tT_sem;                  //转换成time_t 类型 单位为秒
								tF_sem=(iFrom_sem.QuadPart-116444736000000000)/10000000;
								tT_sem=(iTo_sem.QuadPart-116444736000000000)/10000000;   

						//		leftDay=(tT-tF)/(24*3600);
						//		int leftDay_1=(tT_sem-tF_sem)/(24*3600);
						//		CMzString dayleft(10);
						//		wsprintf(dayleft.C_Str(),L"%d",leftDay);
						//		MzMessageBoxEx(m_hWnd, dayleft, L"提醒");


									  CppSQLite3DB db;
									  db.open(L"Schedule.db"); 	
									  db.execDML(L"drop table mycareer;");
									  db.execDML(L"drop table mycareershow;");
									  db.execDML(L"create table mycareer (careerbeg int(50),careerend int(50),sembeg int(50),semend int(50));");
									  db.execDML(L"create table mycareershow (career char(50),school char(50),careerbeg char(50),careerend char(50),sembeg char(50),semend char(50));");

									  CMzString szsql(400),sql(400);
									  wsprintf(szsql.C_Str(),L"insert into mycareer (careerbeg,careerend,sembeg,semend) values (%d,%d,%d,%d);",(int)tF,(int)tT,(int)tF_sem,(int)tT_sem);
					//				  wsprintf(szsql.C_Str(),L"update mycareer set careerbeg = %d ,careerend = %d ,sembeg = %d ,semend = %d;",(int)tF,(int)tT,(int)tF_sem,(int)tT_sem);									 
									  db.execDML(szsql);
									  wsprintf(sql.C_Str(),L"insert into mycareershow (career,school,careerbeg,careerend,sembeg,semend) values ('%s','%s','%s','%s','%s','%s');",myc_Edit[0].GetText().C_Str(),myc_Edit[1].GetText().C_Str(),myc_DateBtn_Beg.GetText().C_Str(),myc_DateBtn_End.GetText().C_Str(),myc_DateBtn_ThisSem.GetText().C_Str(),myc_DateBtn_ThisSem_end.GetText().C_Str());
									  db.execDML(sql);
								//	MzMessageBoxEx(m_hWnd, sql, L"提醒");
								//	  CppSQLite3Query *pQuery;
								//		pQuery=db.execQuery(L"select * from mycareer;");
								//		CMzString tF_S=pQuery->fieldValue(L"careerbeg");
								//		int tF_=_ttoi(tF_S);
								////		CMzString tT_S=pQuery->fieldValue(L"careerend");
								////		int tT_=_ttoi(tT_S);
								////		CMzString tF_sem_S=pQuery->fieldValue(L"sembeg");
								////		int tF_sem_=_ttoi(tF_sem_S);
								////		CMzString tT_sem_S=pQuery->fieldValue(L"semend");
								////		int tT_sem_=_ttoi(tT_sem_S);
								//		CMzString test(200);
								//		wsprintf(test.C_Str(),L"%d,%d,%d,%d",tF_,tF_,tF_,tF_);
								//		MzMessageBoxEx(m_hWnd, test, L"提醒");
								//		pQuery->finalize();

									  db.close(); 
									  EndModal(MZ_MYC_BOTTOM);
						}
						
					}
					else
					{
						MzMessageBoxEx(m_hWnd, L"请将信息补全!", L"提醒");
					}
						 
				}
				break;
			}
        }
    }

//	void CareerCount()
//	{
//		FILETIME tFrom,tTo; 
//		SYSTEMTIME m_time_from , m_time_to;
//		CMzString Time(50);
//
////		GetLocalTime(&st);
////		wsprintf(Time.C_Str(),L"%d-%d-%d-%d-%d-%d-%d-%d",st.wYear,st.wMonth,st.wDay,st.wDayOfWeek,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
//		m_time_from.wYear=_ttoi(this->myc_DateBtn_Beg.GetText().SubStr(0,4));
//		m_time_from.wMonth=_ttoi(this->myc_DateBtn_Beg.GetText().SubStr(5,2));
//		m_time_from.wDay=_ttoi(this->myc_DateBtn_Beg.GetText().SubStr(8,2));
//		m_time_from.wDayOfWeek=m_time_from.wHour=m_time_from.wMilliseconds=m_time_from.wMinute=m_time_from.wSecond=0;
//	
////wsprintf(Time.C_Str(),L"%d-%d-%d-%d-%d-%d-%d-%d",m_time_from.wYear,m_time_from.wMonth,m_time_from.wDay,m_time_from.wDayOfWeek,m_time_from.wHour,m_time_from.wMinute,m_time_from.wSecond,m_time_from.wMilliseconds);
////MzMessageBoxEx(m_hWnd, Time, L"提醒");
//
//		m_time_to.wYear=_ttoi(this->myc_DateBtn_End.GetText().SubStr(0,4));
//		m_time_to.wMonth=_ttoi(this->myc_DateBtn_End.GetText().SubStr(5,2));
//		m_time_to.wDay=_ttoi(this->myc_DateBtn_End.GetText().SubStr(8,2));
//		m_time_to.wDayOfWeek=m_time_to.wHour=m_time_to.wMilliseconds=m_time_to.wMinute=m_time_to.wSecond=0;
//
////wsprintf(Time.C_Str(),L"%d-%d-%d-%d-%d-%d-%d-%d",m_time_to.wYear,m_time_to.wMonth,m_time_to.wDay,m_time_to.wDayOfWeek,m_time_to.wHour,m_time_to.wMinute,m_time_to.wSecond,m_time_to.wMilliseconds);
////MzMessageBoxEx(m_hWnd, Time, L"提醒");
//
//		SystemTimeToFileTime(&m_time_from,&tFrom);
//		SystemTimeToFileTime(&m_time_to,&tTo);
//		LARGE_INTEGER iFrom,iTo;
//
//		iFrom.HighPart=tFrom.dwHighDateTime;
//		iFrom.LowPart=tFrom.dwLowDateTime;
//		iTo.HighPart=tTo.dwHighDateTime;
//		iTo.LowPart=tTo.dwLowDateTime;
//		time_t tF,tT;                  //转换成time_t 类型 单位为秒
//		tF=(iFrom.QuadPart-116444736000000000)/10000000;
//		tT=(iTo.QuadPart-116444736000000000)/10000000;        
//
//		leftDay=(tT-tF)/(24*3600);
//		CMzString dayleft(10);
//		wsprintf(dayleft.C_Str(),L"%d",leftDay);
//		MzMessageBoxEx(m_hWnd, dayleft, L"提醒");
//
//	}

};

MZ_IMPLEMENT_DYNAMIC(CareerSetWnd);

#define MZM_HEIGHT_COUNTDOWN  131
#define MZM_HEIGHT_OFFSET  0
#define MZM_WIDTH_OFFSET  -5

class MyCareerWnd : public CMzWndEx
{
    MZ_DECLARE_DYNAMIC(MyCareerWnd);
public:
	UiStatic       myc_caption_show;
	UiToolbar_Text  myc_bottom_show;
	UiButton        myc_Line[5];
	UiStatic		mys_Msg[5];
	UiStatic        mys_Msg_show[5];
	UiStatic        MyLeftday;
	UiStatic        MyLeftday_smester;
	ColorfulCareer  colorful_career;
	ColorfulCareer  colorful_sem;

	UiButton_Image  countdown_Image;
    ImageContainer m_imgContainer;

	UiStatic end_of_sem;

	//UiButton_Image  oracle,oracle_Bg;

	UiStatic  countdown_Text[4];
	UiStatic  countdown_Msg[4];

	int  tF,tT,tF_sem,tT_sem;
    SYSTEMTIME m_sTime;

protected:
    // 窗口初始化
    virtual BOOL OnInitDialog()
    {
        // 必须先调用基类的初始化
        if (!CMzWndEx::OnInitDialog())
        {
            return FALSE;
        }
		ImagingHelper* imgNormal = m_imgContainer.LoadImage(MzGetInstanceHandle(), IDB_PNG_COUNTDOWN, true);

		countdown_Image.SetButtonType(MZC_BUTTON_NONE);
		countdown_Image.SetPos(0,0,480,MZM_HEIGHT_COUNTDOWN+MZM_HEIGHT_OFFSET);
		countdown_Image.SetImage_Normal(imgNormal);
		countdown_Image.SetImage_Pressed(imgNormal);
		countdown_Image.SetMode(UI_BUTTON_IMAGE_MODE_ALWAYS_SHOW_NORMAL);
		countdown_Image.SwapImageZOrder(true);
		countdown_Image.SetTextColor(RGB(0,0,0));
		AddUiWin(&countdown_Image);

		end_of_sem.SetPos(0,531,480,83);
		end_of_sem.SetTextColor(RGB(139, 58 ,58 ));
		AddUiWin(&end_of_sem);
		
		for(int i=0; i<4; ++i)
		{
			countdown_Text[i].SetPos(4*36+30*i+36*2*i+MZM_HEIGHT_OFFSET+MZM_WIDTH_OFFSET,95,30,31);
			countdown_Text[i].SetTextSize(20);
			AddUiWin(&countdown_Text[i]);

			countdown_Msg[i].SetPos(4*36+30*i+36*2*(i-1)+MZM_HEIGHT_OFFSET+MZM_WIDTH_OFFSET,60,36*2,61);
			countdown_Msg[i].SetTextSize(60);
			AddUiWin(&countdown_Msg[i]);
		}
		countdown_Msg[0].SetPos(15+MZM_WIDTH_OFFSET,60+MZM_HEIGHT_OFFSET,36*4-10,61);
		countdown_Text[0].SetText(L"天");
		countdown_Text[1].SetText(L"时");
		countdown_Text[2].SetText(L"分");
		countdown_Text[3].SetText(L"秒");

		
		colorful_career.SetPos(200,160+MZM_HEIGHT_COUNTDOWN+MZM_HEIGHT_OFFSET+20,280,40);
		colorful_sem.SetPos(200,320+MZM_HEIGHT_COUNTDOWN+MZM_HEIGHT_OFFSET+20,280,40);
		

		myc_caption_show.SetPos(20,20,480,45);
		myc_caption_show.SetTextSize(22);
		myc_caption_show.SetDrawTextFormat(DT_LEFT);
		myc_caption_show.SetText(L"毕业倒计时:");
		AddUiWin(&myc_caption_show);
		
		for(int i=0;i<5;++i)
		{
			myc_Line[i].SetPos(0,MZM_HEIGHT_OFFSET+80*i+MZM_HEIGHT_COUNTDOWN,480,80);
			myc_Line[i].SetButtonType(MZC_BUTTON_LINE_BOTTOM);
			AddUiWin(&myc_Line[i]);

			mys_Msg[i].SetPos(15,MZM_HEIGHT_OFFSET+80*i+MZM_HEIGHT_COUNTDOWN,180,80);
			mys_Msg[i].SetDrawTextFormat(DT_LEFT | DT_VCENTER);
			AddUiWin(&mys_Msg[i]);

			mys_Msg_show[i].SetPos(200,MZM_HEIGHT_OFFSET+80*i+MZM_HEIGHT_COUNTDOWN,280,80);
			mys_Msg_show[i].SetDrawTextFormat(DT_LEFT | DT_VCENTER);
			AddUiWin(&mys_Msg_show[i]);
		}

		mys_Msg[0].SetText(L"学校:");
		mys_Msg[1].SetText(L"大学进度:");
		mys_Msg[2].SetText(L"大学进度条:");
		mys_Msg[3].SetText(L"本学期进度:");
		mys_Msg[4].SetText(L"本学期进度条:");

		COLORREF clr = RGB(0 ,0 ,205 );
		COLORREF clr_Important = RGB(165 ,42, 42 );
		mys_Msg_show[0].SetText(L"未设定");
		mys_Msg_show[1].SetTextSize(35);
		mys_Msg_show[1].SetTextColor(clr_Important);
		mys_Msg_show[2].SetTextSize(25);
		mys_Msg_show[3].SetTextSize(35);
		mys_Msg_show[3].SetTextColor(clr);

		myc_bottom_show.SetPos(0,GetHeight()-70,480,70);
		myc_bottom_show.SetID(MZ_MYC_BOTTOM);
		myc_bottom_show.SetButton(0,true,true,L"关于");
		myc_bottom_show.SetButton(1,true,true,L"本学期");
        myc_bottom_show.SetButton(2,true,true,L"设定");
	    AddUiWin(&myc_bottom_show);


		CppSQLite3DB db;
		db.open(L"Schedule.db");
		if(db.tableExists(L"mycareer"))
		{
			db.close();
			ShowMsg();
			AddUiWin(&colorful_career);
			AddUiWin(&colorful_sem);//加入大学进度条
			
		}
		else
		{
			mys_Msg_show[0].SetText(L"未设定");
			mys_Msg_show[1].SetText(L"未知");
			mys_Msg_show[2].SetText(L"未知");
			mys_Msg_show[3].SetText(L"未知");
		}

        SetTimer(m_hWnd, 1, 500, NULL);
		

        return TRUE;
    }

	virtual void OnTimer(UINT_PTR nIDEvent)
	{
		if(nIDEvent==1)
		{
			RefreshCareer();
			RefreshCountdown();
		}
	}


    // 重写命令消息的处理函数
    virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
    {
        UINT_PTR id = LOWORD(wParam);
        switch (id)
        {
		case MZ_MYC_BOTTOM:
			{
				if(0==lParam)
				{
					RefreshCountdown();
				}
				else if(1==lParam)
				{
					EndModal(MZ_MYC_BOTTOM);
				}
				else if(2==lParam)
				{
					CareerSetWnd careersetwnd;
					RECT rcWork = MzGetWorkArea();
					careersetwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
					careersetwnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_RIGHT_TO_LEFT_PUSH);
					careersetwnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_LEFT_TO_RIGHT_PUSH);
					careersetwnd.DoModal();
					ShowMsg();
				}
				break;
			}
        }
    }

	void ShowMsg()
	{
			CppSQLite3DB db;
			CppSQLite3Query *pQuery;
			db.open(L"Schedule.db");
			pQuery=db.execQuery(L"select * from mycareer;");
			CMzString tF_s=pQuery->fieldValue(L"careerbeg");
			CMzString tT_s=pQuery->fieldValue(L"careerend");
			tF=_ttoi(tF_s);
			tT=_ttoi(tT_s);

			CMzString tF_sem_s=pQuery->fieldValue(L"sembeg");
			CMzString tT_sem_s=pQuery->fieldValue(L"semend");
			tF_sem=_ttoi(tF_sem_s);
			tT_sem=_ttoi(tT_sem_s);

			pQuery=db.execQuery(L"select * from mycareershow;");
			tF_sem_s=pQuery->fieldValue(L"career");
			tT_sem_s=pQuery->fieldValue(L"school");
			mys_Msg_show[0].SetText(tT_sem_s);
			wsprintf(tF_s.C_Str(),L"%s毕业倒计时:",tF_sem_s.C_Str());
			myc_caption_show.SetText(tF_s);
			pQuery->finalize();
			db.close();

			

			RefreshCareer();
			RefreshCountdown();

	}
	void RefreshCareer()
	{
		FILETIME tNow; 
		GetLocalTime(&m_sTime);		
		SystemTimeToFileTime(&m_sTime,&tNow);

		LARGE_INTEGER iNow;
		iNow.HighPart=tNow.dwHighDateTime;
		iNow.LowPart=tNow.dwLowDateTime;
		time_t tN;                  //转换成time_t 类型 单位为秒
		tN=(iNow.QuadPart-116444736000000000)/10000000;      

		float aa = (tT-tF)/(24*3600);
		float bb = (tN-tF)/(24*3600);
		if(aa)
		{
			float percentage=(100*bb)/aa;
			this->colorful_career.SetProportion(percentage/100);
			//colorful_career.Invalidate();
			//colorful_career.Update();
			CMzString perc(200);     //MzMessageBoxEx(m_hWnd, L"haha", L"提醒");
			wsprintf(perc.C_Str(),L"%.2f%s",percentage,L"%");
			mys_Msg_show[1].SetText(perc);			
		}

		float aa_1 = (tT_sem-tF_sem)/(24*3600);
		float bb_1 = (tN-tF_sem)/(24*3600);		
		if(aa_1)
		{
			float percentage_1=(100*bb_1)/aa_1;
			colorful_sem.SetProportion(percentage_1/100);
			CMzString perc_1(200);         
			wsprintf(perc_1.C_Str(),L"%.2f%s",percentage_1,L"%");
			mys_Msg_show[3].SetText(perc_1);
		}
		int cc_1 = (tT_sem-tN)/(24*3600);
		CMzString endofsem;
		wsprintf(endofsem.C_Str(),L"离放寒假还有 %d 天",cc_1);
		this->end_of_sem.SetText(endofsem);
		
	}

	void RefreshCountdown()
	{
		FILETIME tNow; 
		GetLocalTime(&m_sTime);		
		SystemTimeToFileTime(&m_sTime,&tNow);

		LARGE_INTEGER iNow;
		iNow.HighPart=tNow.dwHighDateTime;
		iNow.LowPart=tNow.dwLowDateTime;
		time_t tN;                  //转换成time_t 类型 单位为秒
		tN=(iNow.QuadPart-116444736000000000)/10000000;      

		int left_Day,left_Hour,left_Min,left_Sec;
		
		left_Day=(tT-tN)/(24*3600);
		left_Hour=(tT-tN-left_Day*24*3600)/3600;
		left_Min=(tT-tN-left_Day*24*3600-left_Hour*3600)/60;
		left_Sec=tT-tN-left_Day*24*3600-left_Hour*3600-left_Min*60;

//		CMzString countdown;
//		wsprintf(countdown.C_Str(),L"%d 天 %d 时 %d 分 %02d 秒",left_Day,left_Hour,left_Min,left_Sec);
////		wsprintf(countdown.C_Str(),L"%d",tT-tN);
//		mys_Msg_show[2].SetText(countdown);
//		mys_Msg_show[2].Invalidate();
//		mys_Msg_show[2].Update();

		CMzString countdownMsg;
		wsprintf(countdownMsg.C_Str(),L"%d",left_Day);
		this->countdown_Msg[0].SetText(countdownMsg);
		wsprintf(countdownMsg.C_Str(),L"%02d",left_Hour);
		this->countdown_Msg[1].SetText(countdownMsg);
		wsprintf(countdownMsg.C_Str(),L"%02d",left_Min);
		this->countdown_Msg[2].SetText(countdownMsg);
		wsprintf(countdownMsg.C_Str(),L"%02d",left_Sec);
		this->countdown_Msg[3].SetText(countdownMsg);

		for(int i=0; i<4; ++i)
		{
			countdown_Msg[i].Invalidate();
			countdown_Msg[i].Update();
		}

	}

};

MZ_IMPLEMENT_DYNAMIC(MyCareerWnd);

