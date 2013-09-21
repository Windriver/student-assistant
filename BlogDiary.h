#include <mzfc_inc.h>
#include <Wininet.h>
#include <string.h>
#include <CallNotifyApi.h>
#include <mzfc/ConvertHelper.h>
#include "Encode.h"
#include "base64.h"
//#include "DiarySet.h"


//表情图片资源ID
static DWORD ResID[18] = 
{
    MZRESV2_IDR_PNG_SMILE,
    MZRESV2_IDR_PNG_LAUGH,
    MZRESV2_IDR_PNG_TONGUE,
    MZRESV2_IDR_PNG_SAD,
    MZRESV2_IDR_PNG_WINKING,
    MZRESV2_IDR_PNG_COOL,
    MZRESV2_IDR_PNG_UNDECIDED,
    MZRESV2_IDR_PNG_SURPRISED,
    MZRESV2_IDR_PNG_MONEY,
    MZRESV2_IDR_PNG_STOPPER,
    MZRESV2_IDR_PNG_APATHY,
    MZRESV2_IDR_PNG_KISSING,
    MZRESV2_IDR_PNG_JIONG,
    MZRESV2_IDR_PNG_CRYING,
    MZRESV2_IDR_PNG_ANGGER,
    MZRESV2_IDR_PNG_SAWLOGS,
    MZRESV2_IDR_PNG_GOSH,
    MZRESV2_IDR_PNG_PIG
};
//与表情资源id对应的表情字符
static WCHAR* EmotionTxt[18] = 
{
    L"[呵呵]",L"[嘻嘻]",L"[做鬼脸]",
    L"[失望]",L"[乐乐]",L"[酷]",
    L"[委屈]",L"[吃惊]",L"[钱]",
    L"[闭嘴]",L"[晕]",L"[花心]",
    L"[囧]",L"[泪]",L"[愤怒]",
    L"[睡觉]",L"[汗]",L"[猪头]"
};

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
					  
				CMzString account(30),password(30),test01;;
				string account_s,password_s,accountPassword,accountPassword_64;
				
				/*WideCharToMultiByte (CP_OEMCP,NULL,bdy_Edit[0].GetText().C_Str(),-1,(LPSTR)account_s.c_str(),account_s.length(),NULL,FALSE);
				WideCharToMultiByte (CP_OEMCP,NULL,bdy_Edit[1].GetText().C_Str(),-1,(LPSTR)password_s.c_str(),password_s.length(),NULL,FALSE);*/
				WcharToChar(bdy_Edit[0].GetText().C_Str(),account_s);
				WcharToChar(bdy_Edit[0].GetText().C_Str(),password_s);

				wsprintf(test01.C_Str(),L"%s%s",account_s.c_str(),password_s.c_str());
				accountPassword = account_s + ":" + password_s;
				accountPassword_64= Base64::encode(accountPassword);
		//		accountPassword_64="zy081314:zy222409";
				CMzString accountPassword_W(50),header;
				MultiByteToWideChar(CP_UTF8,0,accountPassword_64.c_str(),-1,accountPassword_W.C_Str(),accountPassword_64.length());
		//		accountPassword_W=L"asdasd";
				wsprintf(header.C_Str(),L"Authorization: Basic %s\r\n",accountPassword_W.C_Str());
MzMessageBoxEx(m_hWnd, test01, L"提醒");
			  db.execDML(L"drop table myaccount;");
			  db.execDML(L"create table myaccount (account char(50),password char(50),encode char(100));");
			  CMzString szsql(200);
			  wsprintf(szsql.C_Str(),L"insert into myaccount (account,password) values ('%s','%s','%s');",bdy_Edit[0].GetText().C_Str(),bdy_Edit[1].GetText().C_Str(),header.C_Str());
			  MzMessageBoxEx(m_hWnd, szsql, L"提醒");

			  db.execDML(szsql);
			  db.close(); 
		  }
		  db.open(L"Schedule.db"); 	
		  CppSQLite3Query *pQuery;
		  pQuery=db.execQuery(L"select * from myaccount;");
		  CMzString test(40);
		  test=pQuery->fieldValue(L"account");
		  




	
	}
	

};

MZ_IMPLEMENT_DYNAMIC(DiarySetWnd);









class BlogDirayWnd : public CMzWndEx
{
	MZ_DECLARE_DYNAMIC(BlogDirayWnd);
public:
	UiButton bdy_Weather;
	UiStatic bdy_Date;

    UiEdit m_pEdit;
    UiToolbar_Text m_Toolbar;

    UiButton_Image m_btEmotion[18];
    ImagingHelper m_imgEmotion[18];
    ImagingHelper  m_bgPressed;
    UiCanvas m_Bg;
	UiStatic m_text1;


	MzGridMenu bdy_GridMenu;
    ImageContainer bdy_imgContainer;

protected:
    virtual BOOL OnInitDialog()
    {
        if (!CMzWndEx::OnInitDialog())
        {
            return FALSE;
        }


		m_text1.SetPos(0,560,480,614-560);
		AddUiWin(&m_text1);

 

		bdy_Weather.SetPos(310,5,150,45);
		bdy_Weather.SetID(MZ_BDY_WEATHER);
		bdy_Weather.SetButtonType(MZC_BUTTON_DELETE_ORANGE);
		bdy_Weather.SetText(L"天气");
		AddUiWin(&bdy_Weather);

		SYSTEMTIME st;
		CMzString today(100),dayofweek(10);
		GetLocalTime(&st);
		if(st.wDayOfWeek==1)
		{
			dayofweek=L"星期一";
		}
		else if(st.wDayOfWeek==2)
		{
			dayofweek=L"星期二";
		}
		else if(st.wDayOfWeek==3)
		{
			dayofweek=L"星期三";
		}
		else if(st.wDayOfWeek==4)
		{
			dayofweek=L"星期四";
		}
		else if(st.wDayOfWeek==5)
		{
			dayofweek=L"星期五";
		}
		else if(st.wDayOfWeek==6)
		{
			dayofweek=L"星期六";
		}
		else if(st.wDayOfWeek==0)
		{
			dayofweek=L"星期天";
		}
		wsprintf(today.C_Str(),L"%d年%d月%d日   %s",st.wYear,st.wMonth,st.wDay,dayofweek.C_Str());

		bdy_Date.SetPos(15,0,300,60);
		bdy_Date.SetTextSize(22);
		bdy_Date.SetText(today);
		bdy_Date.SetDrawTextFormat(DT_LEFT|DT_VCENTER);
		AddUiWin(&bdy_Date);

        m_pEdit.SetPos(10,60,460,500);
        m_pEdit.SetID(MZ_BDY_EDIT);
        m_pEdit.EnableZoomIn(true);
        m_pEdit.OpenFace(true);
        m_pEdit.SetFontSize(MZFS_NORMAL);
        m_pEdit.EnableGridlines(false);
        m_pEdit.EnableRichTextFormat(true);
        m_pEdit.SetReadOnly(false);
        m_pEdit.SetLineSpace(10);
        m_pEdit.SetRightInvalid(10);
        m_pEdit.EnableGridlines(true);
        m_pEdit.EnableRichTextFormat(true);
        m_pEdit.EnableInsideScroll(true);
        m_pEdit.SetInitHeight(100);
        m_pEdit.SetEditBgType(UI_EDIT_BGTYPE_FILL_WHITE);
        m_pEdit.SetFontColor(RGB(155,155,2));
        m_pEdit.SetLineSpace(10);
		m_pEdit.SetSipMode(IM_SIP_MODE_GEL_PY,60);
		m_pEdit.SetFocus(true);
        //启用Redo,Undo功能
        m_pEdit.EnableUndo(true);
        AddUiWin(&m_pEdit);  

        m_Toolbar.SetPos(0, GetHeight()-70, GetWidth(), 70);
        m_Toolbar.SetButton(0, true, true, L"操作");
        m_Toolbar.SetButton(1, true, true, L"表情");
        m_Toolbar.SetButton(2, true, true, L"发送");
        m_Toolbar.SetID(MZ_BDY_BOTTOM);
        AddUiWin(&m_Toolbar);

        //画表情背景到画布上
        m_Bg.SetID(MZ_IDC_EMOTIONBG);
        m_Bg.SetPos(0, GetHeight() - MZM_HEIGHT_TEXT_TOOLBAR - 300, GetWidth(), 300);
        RECT rc = MzGetClientRect();
        if (m_Bg.m_dcCanvas.GetDC()==0)
        {
            rc.bottom = rc.top + GetHeight();
            m_Bg.m_dcCanvas.Create(480, 300);
        }
        BOOL a = MzDrawGridPopupMenuBG_480(m_Bg.m_dcCanvas.GetDC(), &rc);

        //设置好18个表情button
        int x = 10, y = 380;
        int cx = 75, cy = 75;
        m_bgPressed.LoadImageFromRes(GetMzResV2ModuleHandle(),
            RT_RCDATA,
            MAKEINTRESOURCE(MZRES_IDR_PNG_BUTTON_GRAY),true,true);
        for (int i = 0; i< 18; i++)
        {

            m_imgEmotion[i].LoadImageFromRes(GetMzResV2ModuleHandle(), 
                RT_RCDATA, 
                MAKEINTRESOURCE(ResID[i]), 
                true,true,true);
            m_btEmotion[i].SetImage_Normal(&m_imgEmotion[i]);
            m_btEmotion[i].SetImage_Pressed(&m_bgPressed);
            m_btEmotion[i].SwapImageZOrder(true);
            m_btEmotion[i].SetMode(UI_BUTTON_IMAGE_MODE_ALWAYS_SHOW_NORMAL);
            m_btEmotion[i].SetID(MZ_IDC_EMOTION_START + i);
            m_btEmotion[i].SetPos(x + cx *(i%6),y + cy*(i/6),cx,cy);
        }    

		ImagingHelper* m_selImg = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
		ImagingHelper* m_selImgPrs = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
		ImagingHelper* m_dImg = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
		ImagingHelper* m_dImgPrs = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
		ImagingHelper* m_celImg = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
		ImagingHelper* m_celImgPrs = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);
		ImagingHelper* m_secImg = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
		ImagingHelper* m_secImgPrs = bdy_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);

			// 初始化 MzGridMenu 控件
		bdy_GridMenu.AppendMenuItem(MZ_BDY_GRIDMENU_ITEM1, L"清空内容", m_selImg, m_selImgPrs);
		bdy_GridMenu.AppendMenuItem(MZ_BDY_GRIDMENU_ITEM2, L"设定账号密码", m_dImg, m_dImgPrs);
		bdy_GridMenu.AppendMenuItem(MZ_BDY_GRIDMENU_ITEM3, L"返回主界面", m_celImg, m_celImgPrs);
		bdy_GridMenu.AppendMenuItem(MZ_BDY_GRIDMENU_ITEM4, L"暂存于本机", m_secImg, m_secImgPrs);



	//	OpenGprs();



        return TRUE;
    }


    virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
    {
        UINT_PTR id = LOWORD(wParam);

        switch(id)
        {     
		case MZ_BDY_WEATHER:
		{
			
			MzPopupMenu weekPopupMenu;
			weekPopupMenu.SetMenuTitle(L"设置天气");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 1, L"晴天");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 2, L"阴天");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 3, L"小雨");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 4, L"大雨");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 5, L"雷雨");
			weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 6, L"雪");
            weekPopupMenu.AppendMenuItem(MZV2_MID_MIN + 7, L"大风");

			int result = weekPopupMenu.MzTrackPopupMenu(m_hWnd, TRUE);
			switch(result)
			{
			case MZV2_MID_MIN + 1:
				{
					bdy_Weather.SetText(L"晴天");
					break;
				}
			case MZV2_MID_MIN + 2:
				{
					bdy_Weather.SetText(L"阴天");
					break;
				}
			case MZV2_MID_MIN + 3:
				{
					bdy_Weather.SetText(L"小雨");
					break;
				}
			case MZV2_MID_MIN + 4:
				{
					bdy_Weather.SetText(L"大雨");
					break;
				}
			case MZV2_MID_MIN + 5:
				{
					bdy_Weather.SetText(L"雷雨");
					break;
				}
			case MZV2_MID_MIN + 6:
				{
					bdy_Weather.SetText(L"雪");
					break;
				}
			case MZV2_MID_MIN + 7:
				{
					bdy_Weather.SetText(L"大风");
					break;
				}
			}
			OpenGprs();
			break;
		}
		case MZ_BDY_BOTTOM:
            {
                if(0==lParam)
                    {
						  m_pEdit.SetFocus(false);
						  for (int i = 0; i< 18; i++)
						  {
								RemoveUiWin(&m_btEmotion[i]);
						  } 
						  RemoveUiWin(&m_Bg);
						  Invalidate();
						  UpdateWindow();
                          if (bdy_GridMenu.IsContinue())
						  {
							  bdy_GridMenu.EndGridMenu();
						  }
						 
						  else
						  {
								bdy_GridMenu.TrackGridMenuDialog(m_hWnd, 70);
						  }
                    }
                else if(1==lParam)
                    {
						if (bdy_GridMenu.IsContinue())
						  {
							  bdy_GridMenu.EndGridMenu();
						  }
						else
						{
							//添加表情面板
							if (wcscmp(m_Toolbar.GetButtonText(1),L"表情")==0) 
							{
								AddUiWin(&m_Bg);
								for (int i = 0; i< 18; i++)
								{
									AddUiWin(&m_btEmotion[i]);
								}    
								//
								m_pEdit.SwitchSipMode(IM_SIP_MODE_NONE);
								m_Toolbar.SetButton(1,true,true,L"取消");
								Invalidate();
								UpdateWindow();
							}
							//取消表情面板
							else if (wcscmp(m_Toolbar.GetButtonText(1),L"取消")==0)
							{
								for (int i = 0; i< 18; i++)
								{
									RemoveUiWin(&m_btEmotion[i]);
								}  
								RemoveUiWin(&m_Bg);
								m_pEdit.SetFocus(true);
								m_pEdit.SwitchSipMode(IM_SIP_MODE_GEL_PY);
								m_Toolbar.SetButton(1,true,true,L"表情");

								Invalidate();
								UpdateWindow();
							}
						}
					}
				else if(2==lParam)
					{
						if (bdy_GridMenu.IsContinue())
						  {
							  bdy_GridMenu.EndGridMenu();
						  }
						else
						{
							if(1 == MzMessageBoxEx(m_hWnd, L"你确定要上传到新浪微博吗?", L"Exit", MB_YESNO, false))
							{
								MzAutoMsgBoxEx(m_hWnd, L"正在上传中...", 3000);
								OpenGprs();
								PostoSinaTwitter();

							}
						}
					}
  
 
                    break;
			}
		case MZ_BDY_GRIDMENU_ITEM3:
			{
				if(this->m_pEdit.GetText().IsEmpty())
				{
					EndModal(MZ_BDY_GRIDMENU_ITEM1);
				}
				else
				{
					if(1 == MzMessageBoxEx(m_hWnd, L"确定放弃已编辑的内容?", L"Exit", MB_YESNO, false))
						EndModal(MZ_BDY_GRIDMENU_ITEM1);
					
				}

				break;
			}
		case MZ_BDY_GRIDMENU_ITEM2:
			{
				DiarySetWnd diarysetwnd;
				RECT rcWork = MzGetWorkArea();
				diarysetwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
			    diarysetwnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			    diarysetwnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			    diarysetwnd.DoModal();
				break;
			}
		case MZ_BDY_GRIDMENU_ITEM1:
			{
				m_pEdit.Clear();
                m_pEdit.Invalidate();
				break;
			}
		case MZ_BDY_GRIDMENU_ITEM4:
			{
				break;
			}
		}
            
            //点击表情按钮的处理
            if (id >= MZ_IDC_EMOTION_START && id <= MZ_IDC_EMOTION_END)
            {
                m_pEdit.InsertString(EmotionTxt[id-MZ_IDC_EMOTION_START]);
                size_t row = 0;
                size_t col = 0;
                m_pEdit.GetCaretPos(&row, &col);
                m_pEdit.SetCaretPos(row, col);
                m_pEdit.Update();
                m_pEdit.Invalidate();
            }
            return;
        }
                    
	void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
	  {
		  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
		  {
			  if (bdy_GridMenu.IsContinue())
			  {
				  bdy_GridMenu.EndGridMenu();
			  }
		  }
	  }
public:
//	void PostoSinaTwitter()
//	{
//		HINTERNET hInternet = InternetOpen(L"MEIZU M8", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL); 
//		bool hresult= 1;
//		HINTERNET hSession = InternetConnect(hInternet, L"api.t.sina.com.cn", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
//
//		CMzString content_M=this->m_pEdit.GetText();
////		CMzString content_S(200);
////		CUrlEncodeUnicode::Encode(content_M.C_Str(),content_S.C_Str(),content_M.Length());
//
////		CString  data;
//		string content_S;
//		WcharToChar(content_M.C_Str(),content_S);
//		string content_S_1;
//		GB2312ToUTF_8(content_S_1,(char*)content_S.c_str(),content_S.length());
//		string content_U=urlEncoding(content_S_1);
//
//		string data_s="source=762290452&status="+content_U;
////		string data_s="source=762290452&status=%e5%93%88%e5%93%88";
////		
////		CMzString data_s(200);
////		wsprintf(data_s.C_Str(),L"source=762290452&status=%s",L"%e5%93%88%e5%93%88");
////		char data[200];
////		WideCharToMultiByte(CP_UTF8,0,content_S.C_Str(),content_S.Length(),data,200,0,0);
//		
//
////		char data[100]="source=762290452&status=%ad%a4%e6%9d%a1%bf%a1%e6%81%af%e6%9d%a5%e8%87%aa%e9%ad%85%e6%97%8fM8";
//		HINTERNET hRequest = HttpOpenRequest(hSession, L"POST", L"statuses/update.json", NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, 0); 
//
///*		CMzString usernamePassword =L"zy081314:zy222409";
//		string passname_s,passname_base64;
//		WcharToChar(usernamePassword.C_Str(),passname_s);
//		passname_base64=Base64::encode(passname_s);
//		CMzString header_passname(100);
//		MultiByteToWideChar(CP_ACP, 0, passname_base64.c_str(), passname_base64.length(), header_passname.C_Str(), header_passname.Length());    
//		wsprintf(header_passname.C_Str(),L"Authorization: Basic %s\r\n",header_passname.C_Str());
//		MzMessageBoxV2(m_hWnd,header_passname, MZV2_MB_OK);       */
//
//		CMzString header_Content_Length(100);
//		CMzString header_Content_Type = L"Content-Type:application/x-www-form-urlencoded\r\n";
//
////******账号密码的转码
////		CMzString account(30),password(30);
////		string account_s,password_s;
////		account=L"zy081314";
////		password=L"zy222409";
////		WcharToChar(account.C_Str(),account_s);
////		WcharToChar(password.C_Str(),password_s);
////		string accountPassword = account_s + ":" + password_s;
////		string accountPassword_64= Base64::encode(accountPassword);
//
////		CMzString accountPassword_W(50),header;
////		MultiByteToWideChar(CP_UTF8,0,accountPassword_64.c_str(),-1,accountPassword_W.C_Str(),accountPassword_64.length());
////		wsprintf(header.C_Str(),L"Authorization: Basic %s\r\n",accountPassword_W.C_Str());
////		MzMessageBoxV2(m_hWnd,test01, MZV2_MB_OK);
//		CMzString header =L"Authorization: Basic enkwODEzMTRAc2luYS5jb206enkyMjI0MDk=\r\n";	
//	   
//
//		wsprintf(header_Content_Length.C_Str(),L"Content-Length: %d\r\n",data_s.length());
////		wsprintf(header_Content_Length.C_Str(),L"Content-Length: %d\r\n",data_s.Length());
//		HttpAddRequestHeaders(hRequest,header_Content_Type,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
//		HttpAddRequestHeaders(hRequest,header,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
//		HttpAddRequestHeaders(hRequest,header_Content_Length,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
//
////		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.C_Str(),data_s.Length());
//		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.c_str(),data_s.length());
////		hresult =HttpSendRequest(hRequest,NULL,0,data,strlen(data));
//	//	wsprintf(data.C_Str(),L"%d",hresult);
//	//	InternetWriteFile(hRequest, (LPVOID)data, data.Length(), NULL);
//		
//
//		HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, NULL, NULL);
//		char inetBuffer[200];
//		TCHAR buffer[200] ;
//		_stprintf(buffer, _T("Tom") );  
//		LPCTSTR strTmp ;
//		DWORD dwRead=0;
//	//	int n=20;
//		// do
//	    //  {
//				BOOL bRead = InternetReadFile(hRequest,inetBuffer,200,&dwRead);         
//				
//			//		strcat(buffer,inetBuffer);	
//			//	--n;
//	    // }   
//	   // while (n>=0);
//		//			CMzString temp(100);
//		//strcat(buffer,inetBuffer);
//		
//		//wsprintf(temp.C_Str(),L"%s%s%s",inetBuffer,L"oo",inetBuffer);
//
//		MultiByteToWideChar(CP_UTF8,0,inetBuffer,-1,buffer,strlen(inetBuffer));
//		strTmp = LPCTSTR(buffer);	    
//	//	MzMessageBoxV2(m_hWnd,header_Content_Length, MZV2_MB_OK);
//		CMzString feedBack(strTmp);
//		if(feedBack.SubStr(2,7)==L"created")
//		{
//			MzMessageBoxV2(m_hWnd,L"成功发布到新浪微博!", MZV2_MB_OK);
//		}
//		else
//		{
//			MzMessageBoxV2(m_hWnd,L"发布失败!请重新发送!", MZV2_MB_OK);
//		}
//		//this->m_pEdit.SetText(strTmp);
//
//
//		HttpEndRequest(hRequest, NULL, 0, 0);
//
//
//		InternetCloseHandle(hRequest); 
//		InternetCloseHandle(hSession); 
//		InternetCloseHandle(hInternet);
//
//
//	}
//
//

	void OpenGprs()
	{
		m_text1.SetText(L"正在连接GPRS...");
		DWORD dwNetWorkStatus;
		dwNetWorkStatus = QueryNetWorkStatus();
		if(dwNetWorkStatus == NETWORK_NONE)
		{

			if (RESULT_OK == Dial_StartGprsConnect2(m_hWnd, GPRS_FORCE_APP_TYPE))
                {
                    m_text1.SetText(L"GPRS拨号成功!");
					m_text1.Invalidate();
			        m_text1.Update();
                }
                else
                {
                    m_text1.SetText(L"GPRS拨号失败!");
					m_text1.Invalidate();
			        m_text1.Update();
                }
		}
		else
		{
			m_text1.SetText(L"GPRS拨号成功!");
		}
                



		
	}
	
	void PostoSinaTwitter()
	{
		HINTERNET hInternet = InternetOpen(L"MEIZU M8", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL); 
		bool hresult= 1;
		HINTERNET hSession = InternetConnect(hInternet, L"api.t.sina.com.cn", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

		CMzString content_M=this->m_pEdit.GetText();
//		CMzString content_S(200);
//		CUrlEncodeUnicode::Encode(content_M.C_Str(),content_S.C_Str(),content_M.Length());

//		CString  data;
		string content_S;
		WcharToChar(content_M.C_Str(),content_S);
		string content_S_1;
		GB2312ToUTF_8(content_S_1,(char*)content_S.c_str(),content_S.length());
		string content_U=urlEncoding(content_S_1);
		string data_s="source=762290452&status="+content_U;
//		string data_s="source=762290452&status=%e5%93%88%e5%93%88";
//		
//		CMzString data_s(200);
//		wsprintf(data_s.C_Str(),L"source=762290452&status=%s",L"%e5%93%88%e5%93%88");
//		char data[200];
//		WideCharToMultiByte(CP_UTF8,0,content_S.C_Str(),content_S.Length(),data,200,0,0);
		

//		char data[100]="source=762290452&status=%ad%a4%e6%9d%a1%bf%a1%e6%81%af%e6%9d%a5%e8%87%aa%e9%ad%85%e6%97%8fM8";
		HINTERNET hRequest = HttpOpenRequest(hSession, L"POST", L"statuses/update.json", NULL, NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE, 0); 

/*		CMzString usernamePassword =L"zy081314:zy222409";
		string passname_s,passname_base64;
		WcharToChar(usernamePassword.C_Str(),passname_s);
		passname_base64=Base64::encode(passname_s);
		CMzString header_passname(100);
		MultiByteToWideChar(CP_ACP, 0, passname_base64.c_str(), passname_base64.length(), header_passname.C_Str(), header_passname.Length());    
		wsprintf(header_passname.C_Str(),L"Authorization: Basic %s\r\n",header_passname.C_Str());
		MzMessageBoxV2(m_hWnd,header_passname, MZV2_MB_OK);       */

		CMzString header_Content_Length(100);
		CMzString header_Content_Type = L"Content-Type:application/x-www-form-urlencoded\r\n";

		CMzString header =L"Authorization: Basic enkwODEzMTRAc2luYS5jb206enkyMjI0MDk=\r\n";	
	   

		wsprintf(header_Content_Length.C_Str(),L"Content-Length: %d\r\n",data_s.length());
//		wsprintf(header_Content_Length.C_Str(),L"Content-Length: %d\r\n",data_s.Length());
		HttpAddRequestHeaders(hRequest,header_Content_Type,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);
		HttpAddRequestHeaders(hRequest,header_Content_Length,-1,HTTP_ADDREQ_FLAG_REPLACE|HTTP_ADDREQ_FLAG_ADD);

//		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.C_Str(),data_s.Length());
		hresult =HttpSendRequest(hRequest,NULL,0,(LPVOID)data_s.c_str(),data_s.length());
//		hresult =HttpSendRequest(hRequest,NULL,0,data,strlen(data));
	//	wsprintf(data.C_Str(),L"%d",hresult);
	//	InternetWriteFile(hRequest, (LPVOID)data, data.Length(), NULL);
		

		HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, NULL, NULL);
		char inetBuffer[200];
		TCHAR buffer[200] ;
		_stprintf(buffer, _T("Tom") );  
		LPCTSTR strTmp ;
		DWORD dwRead=0;
	//	int n=20;
		// do
	    //  {
				BOOL bRead = InternetReadFile(hRequest,inetBuffer,200,&dwRead);         
				
			//		strcat(buffer,inetBuffer);	
			//	--n;
	    // }   
	   // while (n>=0);
		//			CMzString temp(100);
		//strcat(buffer,inetBuffer);
		
		//wsprintf(temp.C_Str(),L"%s%s%s",inetBuffer,L"oo",inetBuffer);

		MultiByteToWideChar(CP_UTF8,0,inetBuffer,-1,buffer,strlen(inetBuffer));
		strTmp = LPCTSTR(buffer);	    
	//	MzMessageBoxV2(m_hWnd,header_Content_Length, MZV2_MB_OK);
		CMzString feedBack(strTmp);
		if(feedBack.SubStr(2,7)==L"created")
		{
			MzMessageBoxV2(m_hWnd,L"成功发布到新浪微博!", MZV2_MB_OK);
		}
		else
		{
			MzMessageBoxV2(m_hWnd,L"发布失败!请重新发送!", MZV2_MB_OK);
		}
		//this->m_pEdit.SetText(strTmp);
		HttpEndRequest(hRequest, NULL, 0, 0);


		InternetCloseHandle(hRequest); 
		InternetCloseHandle(hSession); 
		InternetCloseHandle(hInternet);


	}




};

MZ_IMPLEMENT_DYNAMIC(BlogDirayWnd)


