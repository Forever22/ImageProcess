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

	//flag，标志，用于OnLButtonDown()函数中
	int m_nPointSelecting;

	//存储图片坐标的
	CPoint m_ptSelected[4];
	//存储实际坐标的
	MyPoint m_ptInput[4];

	//VC++与matlab的混合编译
	//求成像矩阵时的输入输出参数，二个输入参数，1个输出参数
	//matGround2Screen_v(NULL, 1, Output, 2, Input);
	//Input：Input[0]:图片上的坐标（三个点的坐标），映射坐标,a
	//		 Input[1]:实际的坐标（三个点的坐标）,b
	//Output:成像矩阵 mat
	Mm *Input[2];
	Mm *Output[1];

	//求实际坐标
	//Screen2Ground_v(NULL, 1, Output_2, 2, Input_2);
	//二个输入参数，一个输出参数
	//Input:Input[0]:成像矩阵,mat
	//	    Input[1]:图片上的坐标（只有一个点的坐标），c
	//Output:实际的坐标（一个）
	Mm *Input_2[2];
	Mm *Output_2[1];

	//a,b是求成像矩阵的输入点的坐标（三个点）
	Mm a, b;
	//c是求实际坐标输入的图片坐标（一个点）
	Mm c;
	//成像矩阵
	Mm mat;

// Dialog Data
	//{{AFX_DATA(CMyMatrixDlg)
	enum { IDD = IDD_MYMATRIX_DIALOG };

	//求实际坐标
	CButton	m_btnGround;
	//点3
	CButton	m_btnPoint_3;
	//点2
	CButton	m_btnPoint_2;
	//点1
	CButton	m_btnPoint_1;

	//选点状态
	CString	m_editPointSelecting;

	//图片上的坐标
	int		m_editPoint_1Y;
	int		m_editPoint_1X;
	int		m_editPoint_2X;
	int		m_editPoint_3Y;
	int		m_editPoint_3X;
	int		m_editPoint_2Y;
	//输入实际坐标
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
