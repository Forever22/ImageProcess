// MyMatrixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMatrix.h"
#include "MyMatrixDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//成像矩阵  matGround2Screen_v(NULL, 1, Output, 2, Input);
#include "matGround2Screen.h"
extern "C" int DLLX _stdcall matGround2Screen_v(char* emsg, int nlhs, Mm* plhs[], int nrhs, Mm* prhs[]);
//第二个参数是实际坐标矩阵

#include "Ground2Screen.h"
extern "C" int DLLX _stdcall Ground2Screen_v(char* emsg, int nlhs, Mm* plhs[], int nrhs, Mm* prhs[]);
//第二个参数是实际坐标向量

//求实际坐标 Screen2Ground_v(NULL, 1, Output_2, 2, Input_2);
#include "Screen2Ground.h"
extern "C" int DLLX _stdcall Screen2Ground_v(char* emsg, int nlhs, Mm* plhs[], int nrhs, Mm* prhs[]);
//第二个参数是实际坐标向量


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMatrixDlg dialog

CMyMatrixDlg::CMyMatrixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMatrixDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyMatrixDlg)
	//add by zhangna 2015/1/3
	//初始化
	//选点状态
	m_editPointSelecting = _T("");
	m_editPoint_1Y = 0;
	m_editPoint_1X = 0;
	m_editPoint_2X = 0;
	m_editPoint_3Y = 0;
	m_editPoint_3X = 0;
	m_editPoint_2Y = 0;
	m_editInput_1X = 0.0f;
	m_editInput_2X = 0.0f;
	m_editInput_3X = 0.0f;
	m_editInput_1Y = 0.0f;
	m_editInput_2Y = 0.0f;
	m_editInput_3Y = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_nPointSelecting=0;
	m_ptSelected[0]=CPoint(0,0);
	m_ptSelected[1]=CPoint(0,0);
	m_ptSelected[2]=CPoint(0,0);
	m_ptSelected[3]=CPoint(0,0);
	//VC与Matlab混合编程初始化
	initM(MATCOM_VERSION);
	//四个矩阵向量的初始
	//
	a = zeros(3, 3);
	b = zeros(3, 3);
	c = zeros(3, 1);
	mat=zeros(3,3);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyMatrixDlg)
	DDX_Control(pDX, IDB_GROUND, m_btnGround);
	DDX_Control(pDX, IDB_POINT_3, m_btnPoint_3);
	DDX_Control(pDX, IDB_POINT_2, m_btnPoint_2);
	DDX_Control(pDX, IDB_POINT_1, m_btnPoint_1);
	DDX_Text(pDX, IDE_POINT_SELECTING, m_editPointSelecting);
	DDX_Text(pDX, IDE_POINT_1Y, m_editPoint_1Y);
	DDX_Text(pDX, IDE_POINT_1X, m_editPoint_1X);
	DDX_Text(pDX, IDE_POINT_2X, m_editPoint_2X);
	DDX_Text(pDX, IDE_POINT_3Y, m_editPoint_3Y);
	DDX_Text(pDX, IDE_POINT_3X, m_editPoint_3X);
	DDX_Text(pDX, IDE_POINT_2Y, m_editPoint_2Y);
	DDX_Text(pDX, IDE_INPUT_1X, m_editInput_1X);
	DDX_Text(pDX, IDE_INPUT_2X, m_editInput_2X);
	DDX_Text(pDX, IDE_INPUT_3X, m_editInput_3X);
	DDX_Text(pDX, IDE_INPUT_1Y, m_editInput_1Y);
	DDX_Text(pDX, IDE_INPUT_2Y, m_editInput_2Y);
	DDX_Text(pDX, IDE_INPUT_3Y, m_editInput_3Y);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyMatrixDlg, CDialog)
	//{{AFX_MSG_MAP(CMyMatrixDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_GND_SCREEN, OnGndScreen)
	ON_BN_CLICKED(IDB_SHOWPICTURE, OnShowpicture)
	ON_BN_CLICKED(IDB_POINT_1, OnPoint1)
	ON_BN_CLICKED(IDB_POINT_2, OnPoint2)
	ON_BN_CLICKED(IDB_POINT_3, OnPoint3)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDB_GROUND, OnGround)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMatrixDlg message handlers

BOOL CMyMatrixDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyMatrixDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyMatrixDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		CDC *pDc = GetDC();
		ShowPicture(pDc, "33.jpg", 0, 0);  
		CString str;
		for (int i=1;i<4;i++)
		{
			str.Format("点%d",i);
			pDc->TextOut(m_ptSelected[i].x, m_ptSelected[i].y, str);
		}
		ReleaseDC(pDc);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyMatrixDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CMyMatrixDlg::ShowPicture(CDC *pDC, CString strPath, int x, int y)
{
	IStream *pStm;     
    CFileStatus fstatus;     
    CFile file;     
    LONG cb;     
    if (file.Open(strPath,CFile::modeRead)&&file.GetStatus(strPath,fstatus)&&((cb = fstatus.m_size) != -1))     
    {     
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);     
        LPVOID pvData = NULL;     
        if (hGlobal != NULL)     
        {     
            pvData = GlobalLock(hGlobal);    
            if (pvData != NULL)     
            {     
                file.Read(pvData, cb);     
                GlobalUnlock(hGlobal);     
                CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);     
            }    
        }    
    }    
    else    
        return false;    
    //显示JPEG和GIF格式的图片，GIF只能显示一帧，还不能显示动画，     
    //要显示动画GIF请使用ACTIVE控//件。     
    IPicture *pPic;    
    //load image from file stream     
    if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)))    
    {    
        OLE_XSIZE_HIMETRIC hmWidth;     
        OLE_YSIZE_HIMETRIC hmHeight;     
        pPic->get_Width(&hmWidth);     
        pPic->get_Height(&hmHeight);     
        double fX,fY;     
        //get image height and width     
        fX = (double)pDC->GetDeviceCaps(HORZRES)*(double)hmWidth/((double)pDC->GetDeviceCaps(HORZSIZE)*100.0);     
        fY = (double)pDC->GetDeviceCaps(VERTRES)*(double)hmHeight/((double)pDC->GetDeviceCaps(VERTSIZE)*100.0);     
        //use render function display image     
        if(FAILED(pPic->Render(*pDC,x,y,(DWORD)fX,(DWORD)fY,0,hmHeight,hmWidth,-hmHeight,NULL)))     
        {    
            pPic->Release();    
            return false;    
        }    
        pPic->Release();    
    }     
    else     
        return false;   
	
	return true;    
}

void CMyMatrixDlg::OnShowpicture() 
{
	// TODO: Add your control notification handler code here

}

void CMyMatrixDlg::OnPoint1() 
{
	// TODO: Add your control notification handler code here
	m_nPointSelecting=1;
	m_btnPoint_1.EnableWindow(FALSE);
	m_editPointSelecting="请选择点 1";
	UpdateData(FALSE);
	
}

void CMyMatrixDlg::OnPoint2() 
{
	// TODO: Add your control notification handler code here
	m_nPointSelecting=2;
	m_btnPoint_2.EnableWindow(FALSE);
	m_editPointSelecting="请选择点 2";
	UpdateData(FALSE);
}

void CMyMatrixDlg::OnPoint3() 
{
	// TODO: Add your control notification handler code here
	m_nPointSelecting=3;
	m_btnPoint_3.EnableWindow(FALSE);
	m_editPointSelecting="请选择点 3";
	UpdateData(FALSE);
}

void CMyMatrixDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//求实际坐标
	if (m_nPointSelecting==11)
	{
		//c里面存的是图片上的坐标
		c.r(1,1)=(float)point.x;
		c.r(2,1)=(float)point.y;
		c.r(3,1)=1.0f;

		/*Mm *Input_2[2]; Mm *Output_2[1];*/
		Input_2[0]=&mat;
		Input_2[1]=&c;
		Screen2Ground_v(NULL, 1, Output_2, 2, Input_2);
	
		CString str;
		str.Format("%f %f",Output_2[0]->r(1,1),Output_2[0]->r(2,1));
		MessageBox(str);
		m_nPointSelecting=0;
	}
	//
	if (m_nPointSelecting!=0)
	{
		m_ptSelected[m_nPointSelecting]=point;
		m_nPointSelecting=0;
	}
	m_nPointSelecting=0;

	m_editPoint_1X=m_ptSelected[1].x;
	m_editPoint_1Y=m_ptSelected[1].y;
	m_editPoint_2X=m_ptSelected[2].x;
	m_editPoint_2Y=m_ptSelected[2].y;
	m_editPoint_3X=m_ptSelected[3].x;
	m_editPoint_3Y=m_ptSelected[3].y;
	
	m_btnPoint_1.EnableWindow(TRUE);
	m_btnPoint_2.EnableWindow(TRUE);
	m_btnPoint_3.EnableWindow(TRUE);
	m_btnGround.EnableWindow(TRUE);
	m_editPointSelecting="没有在选择点";
	UpdateData(FALSE);

	Invalidate(FALSE);
	CDialog::OnLButtonDown(nFlags, point);
}

void CMyMatrixDlg::GetInputPoints()
{
	UpdateData(TRUE);
	m_ptInput[1].x=m_editInput_1X;
	m_ptInput[1].y=m_editInput_1Y;
	m_ptInput[2].x=m_editInput_2X;
	m_ptInput[2].y=m_editInput_2Y;
	m_ptInput[3].x=m_editInput_3X;
	m_ptInput[3].y=m_editInput_3Y;

}

//成像矩阵
void CMyMatrixDlg::OnGndScreen() 
{
	// TODO: Add your control notification handler code here
	GetInputPoints();
	
	for(int i = 1; i <= 3; i++)
	{	
		//a里面放的是图片上的点坐标
		a.r(1, i)=(float)m_ptSelected[i].x;
		a.r(2, i)=(float)m_ptSelected[i].y;
		a.r(3, i) = 1.0f;
		//b里面放的是实际的点坐标
		b.r(1, i)=(float)m_ptInput[i].x;
		b.r(2, i)=(float)m_ptInput[i].y;
		b.r(3, i) = 1.0f;
	}
	
	Input[0] = &a;
	Input[1] = &b;
	Output[1];

	//函数matGround2Screen_v
	//输入 图片上的坐标、实际坐标
	//输出 成像矩阵
	matGround2Screen_v(NULL, 1, Output, 2, Input);
	for (int m=1;m<=3;m++)
	{
		for (int n=1;n<=3;n++)
		{
			mat.r(m,n)=Output[0]->r(m,n);

		}
	}
	CString str;
	str.Format("%f %f %f\r\n%f %f %f\r\n%f %f %f",mat.r(1,1),mat.r(1,2),mat.r(1,3),mat.r(2,1),mat.r(2,2),mat.r(2,3),mat.r(3,1),mat.r(3,2),mat.r(3,3));
	MessageBox(str);
}

//求实际坐标
void CMyMatrixDlg::OnGround() 
{
	// TODO: Add your control notification handler code here
	m_nPointSelecting=11;
	m_btnGround.EnableWindow(FALSE);
	m_editPointSelecting="点击要计算的点";
	UpdateData(FALSE);
}
