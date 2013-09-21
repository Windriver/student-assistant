#include <mzfc_inc.h>
#include "Define.h"


class DiarySetWnd : public CMzWndEx
{
    MZ_DECLARE_DYNAMIC(DiarySetWnd);
public:
	UiCaption       bdy_caption_set;
	UiToolbar_Text  bdy_bottom_set;
	UiStatic        bdy_MsgStatic[2];
	UiButton        bdy_Line[3];
	UiSingleLineEdit bdy_Edit[2];



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

		bdy_caption_set.SetPos(0,0,480,60);
		bdy_caption_set.SetTextSize(25);
		bdy_caption_set.SetText(L"账号密码设定");
		AddUiWin(&bdy_caption_set);

		for(int i=0;i<3;++i)
		{
			bdy_Line[i].SetPos(0,60+90*i,480,90);
			bdy_Line[i].SetDrawTextFormat(DT_LEFT|DT_VCENTER);
			bdy_Line[i].SetButtonType(MZC_BUTTON_LINE_TOP);
			AddUiWin(&bdy_Line[i]);
		}

		for(int i=0;i<2;++i)
		{
			bdy_MsgStatic[i].SetPos(15,60+90*i,200,90);
			bdy_MsgStatic[i].SetDrawTextFormat(DT_LEFT|DT_VCENTER);
			AddUiWin(&bdy_MsgStatic[i]);
		}

		bdy_MsgStatic[0].SetText(L"新浪微博账号:");
		bdy_MsgStatic[1].SetText(L"新浪微博密码:");

		
		bdy_Edit[0].SetPos(220,75,240,60);
		bdy_Edit[0].SetSipMode(IM_SIP_MODE_GEL_LETTER);
		AddUiWin(&bdy_Edit[0]);
		bdy_Edit[1].SetPos(220,165,240,60);
		bdy_Edit[1].SetSipMode(IM_SIP_MODE_GEL_LETTER);
		AddUiWin(&bdy_Edit[1]);
		

		bdy_bottom_set.SetPos(0,GetHeight()-70,480,70);
		bdy_bottom_set.SetID(MZ_BDY_BOTTOM_SET);
		bdy_bottom_set.SetButton(0,true,true,L"取消设定");
        bdy_bottom_set.SetButton(2,true,true,L"保存设定");
	    AddUiWin(&bdy_bottom_set);


        GetLocalTime(&m_sTime);

        CMzString str(128);
        
		

        return TRUE;
    }

    // 重写命令消息的处理函数
    virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
    {
        UINT_PTR id = LOWORD(wParam);
        switch (id)
        {
		case MZ_BDY_BOTTOM_SET:
			{
				int nIndex=lParam;
				if(0==nIndex)
				{
					EndModal(MZ_BDY_BOTTOM_SET);
				}
				else if(2==nIndex)
				{
					SaveDiraySet();
				}
				
				break;
			}
        

		
       
		
        }
    }

	void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
	  {
		  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
		  {
			  bdy_Edit[0].SetFocus(false);
			  bdy_Edit[1].SetFocus(false);
			  
		  }
	  }

	void SaveDiraySet()
	{
		  CppSQLite3DB db;
		  db.open(L"Schedule.db"); 		  
		  if(!(this->bdy_Edit[0].GetText().IsEmpty())&&!(this->bdy_Edit[1].GetText().IsEmpty()))
		  {
			  db.execDML(L"drop table myaccount;");
			  db.execDML(L"create table myaccount (account char(50),password char(50));");
			  CMzString szsql(200);
			  wsprintf(szsql.C_Str(),L"insert into myaccount (account,password) values ('%s','%s');",bdy_Edit[0].GetText().C_Str(),bdy_Edit[1].GetText().C_Str());
			  MzMessageBoxEx(m_hWnd, szsql, L"提醒");

			  db.execDML(szsql);
			  db.close(); 
		  }
		  db.open(L"Schedule.db"); 	
		  CppSQLite3Query *pQuery;
		  pQuery=db.execQuery(L"select * from myaccount;");
		  CMzString test(40);
		  test=pQuery->fieldValue(L"account");
		  MzMessageBoxEx(m_hWnd, test, L"提醒");
	}
	

};

MZ_IMPLEMENT_DYNAMIC(DiarySetWnd);


