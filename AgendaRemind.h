#include <mzfc_inc.h>
#include <mzfc\MzSetDaily.h>
#include <Sqlite/CppSQLite3U.h>
#include "define.h"
#include "resource.h"

//此代码演示了：
//  创建和初始化应用程序
//  创建和初始化窗体
//  按钮控件的使用及其命令消息的处理

// 按钮控件的ID
bool shouldDel=true;
class MyUiListEx: public UiListEx
{
public:
	virtual void OnRemoveItem(int nIndex)
    {
		if(shouldDel)
		{
			  CMzString vague(30),datetime(30),thing(30),mdate(30);
			  vague=this->GetItem(nIndex)->m_textPostscript1;
			  mdate=this->GetItem(nIndex)->m_textTitle;
			  thing=this->GetItem(nIndex)->m_textDescription;
			  if(vague.Length()==5)
			  {
				  wsprintf(datetime.C_Str(),L"%s %s",mdate.C_Str(),vague.C_Str());
			  }
			  else if(vague.Length()==2)
			  {
					if(vague==L"早晨")
					{
						vague=L"07:00";
					}
					else if(vague==L"上午")
					{
						vague=L"10:00";
					}
					else if(vague==L"中午")
					{
						vague=L"12:00";
					}
					else if(vague==L"下午")
					{
						vague=L"15:00";
					}
					else if(vague==L"晚上")
					{
						vague=L"19:00";
					}
					else if(vague==L"深夜")
					{
						vague=L"22:00";
					}
					wsprintf(datetime.C_Str(),L"%s %s",mdate.C_Str(),vague.C_Str());
			  }

			  CppSQLite3DB db;
			  db.open(L"Schedule.db");

			  CMzString sql(200);
			  wsprintf(sql.C_Str(),L"delete from agenda where date_time = '%s' and remind = '%s';",datetime.C_Str(),thing.C_Str());
		//	  MzMessageBoxEx(0, sql, L"提醒");
			  db.execDML(sql);
		}
	
	}
};



// 从 CMzWndEx 派生的主窗口类
class AgendaRemind: public CMzWndEx
{
  MZ_DECLARE_DYNAMIC(AgendaRemind);
public:
  // 窗口中的按钮控件
  UiCaption aga_caption;
  UiScrollWin aga_scroll;
  UiToolbar_Text aga_bottom;
  MyUiListEx aga_list;

  MzGridMenu aga_GridMenu;

  ImageContainer aga_imgContainer;

	
  SYSTEMTIME m_sTime;
  CMzString msg_today;

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
	shouldDel=true;

	aga_caption.SetID(MZ_AGA_CAPTION);
	aga_caption.SetPos(0,0,GetWidth(),50);
//	aga_caption.SetTextSize(28);
//	aga_caption.SetText(L"2010年10月1日星期三");
	AddUiWin(&aga_caption);

	
	GetLocalTime(&m_sTime);
	
	if(1==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期一",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	else if(2==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期二",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	else if(3==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期三",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	else if(4==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期四",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	else if(5==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期五",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	else if(6==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期六",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	else if(0==m_sTime.wDayOfWeek)
	{
		wsprintf(msg_today.C_Str(),L"%d年%02d月%02d日 星期天",m_sTime.wYear,m_sTime.wMonth,m_sTime.wDay);
	}
	
	aga_caption.SetText(msg_today);
	

	aga_scroll.SetID(MZ_AGA_SCROLL);
	aga_scroll.SetPos(0,45,GetWidth(),GetHeight()-70);
//	AddUiWin(&aga_scroll);

	
    aga_bottom.SetID(MZ_AGA_BOTTOM);
	aga_bottom.SetPos(0,GetHeight()-70,GetWidth(),70);
	aga_bottom.SetButton(0,true,true,L"返回");
    aga_bottom.SetButton(1,true,true,L"编辑");
    aga_bottom.SetButton(2,true,true,L"选项");
	aga_bottom.EnableLeftArrow(true);
	AddUiWin(&aga_bottom);

	ImagingHelper* m_selImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_selImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_dImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE, true);
    ImagingHelper* m_dImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_DELETE_PRESSED, true);
    ImagingHelper* m_celImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_celImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);
    ImagingHelper* m_secImg = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW, true);
    ImagingHelper* m_secImgPrs = aga_imgContainer.LoadImage(GetMzResV2ModuleHandle(), MZRESV2_IDR_PNG_NEW_PRESSED, true);

        // 初始化 MzGridMenu 控件
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM1, L"清空日程列表", m_selImg, m_selImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM2, L"显示当前日程", m_dImg, m_dImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM3, L"整理冗余", m_celImg, m_celImgPrs);
    aga_GridMenu.AppendMenuItem(MZ_AGA_GRIDMENU_ITEM4, L"显示全部日程", m_secImg, m_secImgPrs);


	aga_list.SetID(MZ_AGA_LIST);
    aga_list.SetPos(0,50,GetWidth(),GetHeight()-120);
    aga_list.EnableDragModeH(true);
    aga_list.EnableInsideScroll(true);
//    aga_list.EnableUltraGridlines(true);
	aga_list.EnableScrollOptimize(true);
    aga_list.SetItemHeight(80);//注意要在SetIteemAttribute前设置ItemHeigth
    aga_list.SetItemAttribute(UILISTEX_ITEMTYPE_SMS);  
//	aga_list.SetMultiSelectMode(UILISTEX_MULTISELECT_RIGHT);
    aga_list.EnableNotifyMessage(true);
    aga_list.UpdateItemAttribute_Del();
    AddUiWin(&aga_list);

	


	PrintAgenda();

    return TRUE;
  }

  // 重载命令消息的处理函数
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_AGA_BOTTOM:
      {
		  int nIndex=lParam;
		  if(nIndex==0)
		  {
			  if (aga_GridMenu.IsContinue())
              {
                    aga_GridMenu.EndGridMenu();
              }
			  else 
		      {
				  if (wcscmp(aga_bottom.GetButtonText(0).C_Str(),L"取消") == 0 )
				  {
					    aga_list.SetMultiSelectMode();
                        aga_list.SetSelectedIndex(-1);
                        aga_bottom.SetButtonText(0,L"返回");
						aga_bottom.SetButtonText(1,L"编辑");
						aga_bottom.EnableLeftArrow(true);
						Invalidate();
                        UpdateWindow();
				  }
				  else if (wcscmp(aga_bottom.GetButtonText(0).C_Str(),L"返回") == 0 )
				  {
						EndModal(MZ_AGA_BOTTOM);
				  }
			  }
		  }
		  else if(nIndex==1)
		  {
			  if (aga_GridMenu.IsContinue())
              {
                    aga_GridMenu.EndGridMenu();
              }
			  else
			  {
				  if (wcscmp(aga_bottom.GetButtonText(1).C_Str(),L"删除") == 0 )
                    {
                        for (int i = 0; i < aga_list.GetItemCount();)
                        {
                            ListItemEx* pItem = aga_list.GetItem(i);
                            if (pItem && pItem->m_isSelected)
                            {
                                aga_list.RemoveItem(i);
                            }
                            else
                            {
                                i++;
                            }
                        }
				
                        aga_list.Invalidate();
                        aga_list.Update();
						
						
                    } 

				  else if (wcscmp(aga_bottom.GetButtonText(1).C_Str(),L"编辑") == 0 )
				  {
					  aga_list.SetSelectedIndex(1);
					  aga_list.SetMultiSelectMode(UILISTEX_MULTISELECT_RIGHT);
					  aga_list.SetSelectedIndex(-1);
					  aga_list.Invalidate();
					  aga_bottom.SetButtonText(0,L"取消");
					  aga_bottom.EnableLeftArrow(false);
					  aga_bottom.SetButtonText(1,L"删除");
					  Invalidate();
					  UpdateWindow();

				  }

				 				  
			  }
		  }
		  else if(2==nIndex)
		  {
			  if (aga_GridMenu.IsContinue())
              {
                  aga_GridMenu.EndGridMenu();
              }
              else
              {
                    aga_GridMenu.TrackGridMenuDialog(m_hWnd, MZM_HEIGHT_TOOLBARPRO);
              }
		  }
        break;
	  }
	  case MZ_AGA_GRIDMENU_ITEM1:
		  {
			  if(1 == MzMessageBoxEx(m_hWnd, L"你确定要删除全部日程吗?", L"Exit", MB_YESNO, false))
			  {
				  if(1 == MzMessageBoxEx(m_hWnd, L"删除后无法恢复! 确定删除吗?", L"Exit", MB_YESNO, false))
				  {
					  CppSQLite3DB db;
					  db.open(L"Schedule.db"); 
					  db.execDML(L"drop table agenda;");
					  db.close();
					  PrintAgenda();
				  }
			  }
			  break;

		  }
      case MZ_AGA_GRIDMENU_ITEM4:
		  {
			  PrintAllAgenda();
			  break;
		  }
	  case MZ_AGA_GRIDMENU_ITEM2:
		  {
			  PrintAgenda();
			  break;
		  }
	  case MZ_AGA_GRIDMENU_ITEM3:
		  {
			  if(1 == MzMessageBoxEx(m_hWnd, L"你确定要清理今天之前的日程吗?", L"Exit", MB_YESNO, false))
			  {
					  SYSTEMTIME m_sTime;
					  GetLocalTime(&m_sTime);
					  CMzString str(128),sql(100);
					  wsprintf(str.C_Str(), L"%2d-%02d-%02d 00:00", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);

					  CppSQLite3DB db;
					  wsprintf(sql.C_Str(),L"%s%s%s",L"delete from agenda where date_time <'",str.C_Str(),L"';");					  
					  db.open(L"Schedule.db"); 
					  db.execDML(sql);
					  db.close();
					  PrintAgenda();
				  
			  }
			  break;
		  }
    }
  }


  virtual LRESULT MzDefWndProc(UINT message, WPARAM wParam, LPARAM lParam)
  {
      switch(message)
      {
          //处理删除某项时的消息
      case MZ_WM_LIST_ITEM_DRAG_H:
          {
              int index = wParam;
              ListItemEx* pItem = aga_list.GetItem(index);
              if (pItem)
              {
                  int customData = (int)pItem->m_pData;
                  if (customData < 6)
                  {
                      delete pItem->m_pImgFirst;
                  }
              }
			  break;
          }

          
      default:
          break;
      }
      return CMzWndEx::MzDefWndProc(message,wParam,lParam);
  }


  void OnLButtonDown(UINT fwKeys, int xPos, int yPos)
  {
	  if (yPos < (GetHeight() - MZM_HEIGHT_TOOLBARPRO))
      {
          if (aga_GridMenu.IsContinue())
          {
              aga_GridMenu.EndGridMenu();
          }
      }
  }
  
  void PrintAgenda()
  {
	  CppSQLite3DB db;
	  db.open(L"Schedule.db");  
	  shouldDel=false;
	  aga_list.RemoveAll();
	  shouldDel=true;
	  CppSQLite3Query *pQuery;
	  SYSTEMTIME m_sTime;
	  GetLocalTime(&m_sTime);
	  CMzString str(128);
	  wsprintf(str.C_Str(), L"%2d-%02d-%02d 00:00", m_sTime.wYear, m_sTime.wMonth, m_sTime.wDay);
	  CMzString sql(200);
	  CMzString date_time(30),vague_time(10);
	  if(db.tableExists(L"agenda"))
      {     
		  wsprintf(sql.C_Str(),L"%s%s%s",L"select * from agenda where date_time >='",str.C_Str(),L"' order by date_time;");
		  pQuery=db.execQuery(sql);   
		  while(!(pQuery->eof()))
		  {              
//	  		  MzMessageBoxEx(m_hWnd, sql, L"提醒");
			  ListItemEx* item = new ListItemEx;
//            item->m_pData = (void*)i;
			  item->m_textDescription = pQuery->fieldValue(L"remind");

              date_time = pQuery->fieldValue(L"date_time");
			  item->m_textTitle = date_time.SubStr(0,10);

//		      week_time = pQuery->fieldValue(L"week_time");
			  vague_time = pQuery->fieldValue(L"vague_time");
		 
			  item->m_textPostscript1=vague_time;
		
			  if(vague_time.Length()==5)
			  {
				  item->m_pImgFirst = aga_imgContainer.LoadImage(MzGetInstanceHandle(), IDB_PNG1, true);
			  }
			  else
			  {
				  item->m_pImgFirst = aga_imgContainer.LoadImage(MzGetInstanceHandle(), IDB_PNG0, true);
			  }


              aga_list.AddItem(item);
			  pQuery->nextRow();
		  }
		  pQuery->finalize();
	  }
	 
	  db.close();
	  aga_list.Invalidate();
	  aga_list.Update();
  }

  void PrintAllAgenda()
  {
	  CppSQLite3DB db;
	  db.open(L"Schedule.db");
	  shouldDel=false;
	  aga_list.RemoveAll();
	  shouldDel=true;
	  CppSQLite3Query *pQuery;
	 
	  CMzString sql(200);
	  CMzString date_time(30),vague_time(10);
	  if(db.tableExists(L"agenda"))
      {     
		  wsprintf(sql.C_Str(),L"select * from agenda order by date_time;");
		  pQuery=db.execQuery(sql);   
		  while(!(pQuery->eof()))
		  {              
//	  		  MzMessageBoxEx(m_hWnd, sql, L"提醒");
			  ListItemEx* item = new ListItemEx;
//            item->m_pData = (void*)i;
			  item->m_textDescription = pQuery->fieldValue(L"remind");

              date_time = pQuery->fieldValue(L"date_time");
			  item->m_textTitle = date_time.SubStr(0,10);

//		      week_time = pQuery->fieldValue(L"week_time");
			  vague_time = pQuery->fieldValue(L"vague_time");

			 
			  item->m_textPostscript1=vague_time;
		
			  item->m_pImgFirst = aga_imgContainer.LoadImage(MzGetInstanceHandle(), IDB_PNG1, true);



              aga_list.AddItem(item);
			  pQuery->nextRow();
		  }
		  pQuery->finalize();
	  }
	 
	  db.close();
	  aga_list.Invalidate();
	  aga_list.Update();
  }


};





MZ_IMPLEMENT_DYNAMIC(AgendaRemind)

