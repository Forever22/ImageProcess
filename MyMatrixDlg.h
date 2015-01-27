// MyMatrixDlg.h : header file
//

#if !defined(AFX_MYMATRIXDLG_H__B74154CB_DF94_4F1F_BE4C_95AEE9F7DBC5__INCLUDED_)
#define AFX_MYMATRIXDLG_H__B74154CB_DF94_4F1F_BE4C_95AEE9F7DBC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyMatrixDlg dialog
struct MyPoint
{
	float x;
	float y;
};



class CMyMatrixDlg : public CDialog
{
// Construction
public:
	void GetInputPoints();
	BOOL ShowPicture(CDC *pDC, CString strPath, int x, int y);
	CMyMatrixDlg(CWnd* pParent = NULL);	// standard constructor

	//flag����־������OnLButtonDown()������
	int m_nPointSelecting;

	//�洢ͼƬ�����
	CPoint m_ptSelected[4];
	//�洢ʵ�������
	MyPoint m_ptInput[4];

	//VC++��matlab�Ļ�ϱ���
	//��������ʱ����������������������������1���������
	//matGround2Screen_v(NULL, 1, Output, 2, Input);
	//Input��Input[0]:ͼƬ�ϵ����꣨����������꣩��ӳ������,a
	//		 Input[1]:ʵ�ʵ����꣨����������꣩,b
	//Output:������� mat
	Mm *Input[2];
	Mm *Output[1];

	//��ʵ������
	//Screen2Ground_v(NULL, 1, Output_2, 2, Input_2);
	//�������������һ���������
	//Input:Input[0]:�������,mat
	//	    Input[1]:ͼƬ�ϵ����ֻ꣨��һ��������꣩��c
	//Output:ʵ�ʵ����꣨һ����
	Mm *Input_2[2];
	Mm *Output_2[1];

	//a,b��������������������꣨�����㣩
	Mm a, b;
	//c����ʵ�����������ͼƬ���꣨һ���㣩
	Mm c;
	//�������
	Mm mat;

// Dialog Data
	//{{AFX_DATA(CMyMatrixDlg)
	enum { IDD = IDD_MYMATRIX_DIALOG };

	//��ʵ������
	CButton	m_btnGround;
	//��3
	CButton	m_btnPoint_3;
	//��2
	CButton	m_btnPoint_2;
	//��1
	CButton	m_btnPoint_1;

	//ѡ��״̬
	CString	m_editPointSelecting;

	//ͼƬ�ϵ�����
	int		m_editPoint_1Y;
	int		m_editPoint_1X;
	int		m_editPoint_2X;
	int		m_editPoint_3Y;
	int		m_editPoint_3X;
	int		m_editPoint_2Y;
	//����ʵ������
	float	m_editInput_1X;
	float	m_editInput_2X;
	float	m_editInput_3X;
	float	m_editInput_1Y;
	float	m_editInput_2Y;
	float	m_editInput_3Y;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMatrixDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyMatrixDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGndScreen();
	afx_msg void OnShowpicture();
	afx_msg void OnPoint1();
	afx_msg void OnPoint2();
	afx_msg void OnPoint3();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGround();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMATRIXDLG_H__B74154CB_DF94_4F1F_BE4C_95AEE9F7DBC5__INCLUDED_)
