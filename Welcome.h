#include <mzfc_inc.h>

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
    m_btn.SetPos(0,250,480,100);
    m_btn.SetID(MZ_IDC_TESTBTN1);
    m_btn.SetText(L"��ӭʹ��M8ѧ������");
    m_btn.SetTextColor(RGB(255,255,255));

              // �ѿؼ���ӵ�������
    AddUiWin(&m_btn);

    return TRUE;
  }

  // ����������Ϣ�Ĵ�����   L"You have pressed Exit button, Really want exit?"
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

MZ_IMPLEMENT_DYNAMIC(CSample1MainWnd)


