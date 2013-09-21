
















//����MZFC���ͷ�ļ�
#include <mzfc_inc.h>
#include <Sqlite/CppSQLite3U.h>
#include "MyCareer.h"

//�˴�����ʾ�ˣ�
//  �����ͳ�ʼ��Ӧ�ó���
//  �����ͳ�ʼ������
//  ��ť�ؼ���ʹ�ü���������Ϣ�Ĵ���

// ��ť�ؼ���ID
#define MZ_IDC_TESTBTN1  101

// �� CMzWndEx ��������������
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
    m_btn.SetPos(100,250,280,100);
    m_btn.SetID(MZ_IDC_TESTBTN1);
    m_btn.SetText(L"Hello MZFC!");
    m_btn.SetTextColor(RGB(255,255,255));

              // �ѿؼ���ӵ�������
    AddUiWin(&m_btn);

    return TRUE;
  }

  // ����������Ϣ�Ĵ�����
  virtual void OnMzCommand(WPARAM wParam, LPARAM lParam)
  {
    UINT_PTR id = LOWORD(wParam);
    switch(id)
    {
    case MZ_IDC_TESTBTN1:
      {
        MyCareerWnd mycareerwnd;
			RECT rcWork = MzGetWorkArea();
			mycareerwnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork),m_hWnd, 0, WS_POPUP);
		    mycareerwnd.SetAnimateType_Show(MZ_ANIMTYPE_SCROLL_TOP_TO_BOTTOM_2);
			mycareerwnd.SetAnimateType_Hide(MZ_ANIMTYPE_SCROLL_BOTTOM_TO_TOP_2);
			mycareerwnd.DoModal();
      }
      break;
    }
  }
};

MZ_IMPLEMENT_DYNAMIC(CSample1MainWnd)

// �� CMzApp ������Ӧ�ó�����
class CSample1App: public CMzApp
{
public:
  // Ӧ�ó����������
  CSample1MainWnd m_MainWnd;

  // Ӧ�ó���ĳ�ʼ��
  virtual BOOL Init()
  {
              // ��ʼ�� COM ���
    CoInitializeEx(0, COINIT_MULTITHREADED);

              // ����������
    RECT rcWork = MzGetWorkArea();
    m_MainWnd.Create(rcWork.left,rcWork.top,RECT_WIDTH(rcWork),RECT_HEIGHT(rcWork), 0, 0, 0);
    m_MainWnd.Show();

              // �ɹ��򷵻�TRUE
    return TRUE;
  }
};

// ȫ�ֵ�Ӧ�ó������
CSample1App theApp;

