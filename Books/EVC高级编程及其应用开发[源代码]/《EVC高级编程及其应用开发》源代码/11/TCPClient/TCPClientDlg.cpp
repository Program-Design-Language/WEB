// TCPClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCPClient.h"
#include "TCPClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCPClientDlg dialog

CTCPClientDlg::CTCPClientDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTCPClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCPClientDlg)
	m_remoteHost = _T("");
	m_remotePort = 0;
	m_recvData = _T("");
	m_sendData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCPClientDlg)
	DDX_Text(pDX, IDC_EDTREMOTEHOST, m_remoteHost);
	DDX_Text(pDX, IDC_EDTREMOTEPORT, m_remotePort);
	DDX_Text(pDX, IDC_EDTRECV, m_recvData);
	DDX_Text(pDX, IDC_EDTSENDDATA, m_sendData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCPClientDlg, CDialog)
//{{AFX_MSG_MAP(CTCPClientDlg)
ON_BN_CLICKED(IDC_BTNCONN, OnBtnconn)
ON_BN_CLICKED(IDC_BTNDISCONN, OnBtndisconn)
ON_BN_CLICKED(IDC_BTNSENDDATA, OnBtnsenddata)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCPClientDlg message handlers

BOOL CTCPClientDlg::OnInitDialog()
{
	m_bFullScreen = FALSE;
	CDialog::OnInitDialog();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen
	
	//初始化输入值
	m_remoteHost = GetLocalIP();
	m_remotePort = 5000;
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}


//连接断开事件
void CALLBACK CTCPClientDlg::OnDisConnect(CWnd* pWnd)
{
	CTCPClientDlg * pDlg = (CTCPClientDlg*)pWnd;
	
	CStatic * pStatus = (CStatic *)pDlg->GetDlgItem(IDC_LBLCONNSTATUS);
	ASSERT(pStatus != NULL);
	pStatus->SetWindowText(_T("连接断开"));
	
	/*设置按钮可用属性*/
	CButton * pBtnConn =(CButton*)pDlg->GetDlgItem(IDC_BTNCONN);
	CButton * pBtnDisConn = (CButton*)pDlg->GetDlgItem(IDC_BTNDISCONN);
	CButton * pBtnSendData =  (CButton*)pDlg->GetDlgItem(IDC_BTNSENDDATA);
	ASSERT(pBtnConn != NULL );
	ASSERT(pBtnDisConn != NULL );
	ASSERT(pBtnSendData != NULL );
	pBtnConn->EnableWindow(TRUE);
	pBtnDisConn->EnableWindow(FALSE);
	pBtnSendData->EnableWindow(FALSE);
}

//数据接收事件
void CALLBACK CTCPClientDlg::OnRead(CWnd* pWnd,const char * buf,int len )
{
	CTCPClientDlg * pDlg = (CTCPClientDlg*)pWnd;
	CEdit * pEdtRecv = (CEdit*)pDlg->GetDlgItem(IDC_EDTRECV);
	ASSERT(pEdtRecv != NULL);
	CString strRecv = buf;
	//将接收的数据显示到接收文本框上
	pEdtRecv->SetWindowText(strRecv);
}

//Socket错误事件
void CALLBACK CTCPClientDlg::OnError(CWnd* pWnd,int nErrorCode)
{
	AfxMessageBox(_T("客户端socket发生错误"));
}


//建立连接按钮
void CTCPClientDlg::OnBtnconn() 
{
	UpdateData(TRUE);
	//设置m_tcpClient属性
	m_tcpClient.m_remoteHost = m_remoteHost;
	m_tcpClient.m_port = m_remotePort;
	m_tcpClient.OnDisConnect = OnDisConnect;
	m_tcpClient.OnRead = OnRead;
	m_tcpClient.OnError = OnError;
	//打开客户端socket
	m_tcpClient.Open(this);
	
	//建立与服务器端连接
	if (m_tcpClient.Connect())
	{
		CStatic *pStatus = (CStatic*)GetDlgItem(IDC_LBLCONNSTATUS);
		ASSERT(pStatus != NULL);
		pStatus->SetWindowText(L"建立连接");
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("建立连接失败"));
		CStatic *pStatus = (CStatic*)GetDlgItem(IDC_LBLCONNSTATUS);
		ASSERT(pStatus != NULL);
		pStatus->SetWindowText(L"连接断开");
		return;
	}
	/*设置按钮可用属性*/
	CButton * pBtnConn =(CButton*)GetDlgItem(IDC_BTNCONN);
	CButton * pBtnDisConn = (CButton*)GetDlgItem(IDC_BTNDISCONN);
	CButton * pBtnSendData =  (CButton*)GetDlgItem(IDC_BTNSENDDATA);
	ASSERT(pBtnConn != NULL );
	ASSERT(pBtnDisConn != NULL );
	ASSERT(pBtnSendData != NULL );
	pBtnConn->EnableWindow(FALSE);
	pBtnDisConn->EnableWindow(TRUE);
	pBtnSendData->EnableWindow(TRUE);
	
}

//断开连接按钮单击事件
void CTCPClientDlg::OnBtndisconn() 
{
	if (m_tcpClient.Close())
	{
		CStatic *pStatus = (CStatic*)GetDlgItem(IDC_LBLCONNSTATUS);
		ASSERT(pStatus != NULL);
		pStatus->SetWindowText(L"连接断开");
		CButton * pBtnConn =(CButton*)GetDlgItem(IDC_BTNCONN);
		CButton * pBtnDisConn = (CButton*)GetDlgItem(IDC_BTNDISCONN);
		CButton * pBtnSendData = (CButton*)GetDlgItem(IDC_BTNSENDDATA);
		ASSERT(pBtnConn != NULL );
		ASSERT(pBtnDisConn != NULL );
		ASSERT(pBtnSendData != NULL );
		pBtnConn->EnableWindow(TRUE);
		pBtnDisConn->EnableWindow(FALSE);
		pBtnSendData->EnableWindow(FALSE);
	}
	else
	{
		AfxMessageBox(_T("连接断开失败"));
	}	
}

//发送数据按钮单击事件代码
void CTCPClientDlg::OnBtnsenddata() 
{
	char * sendBuf;
	int sendLen=0;
	UpdateData(TRUE);
	
	sendLen = m_sendData.GetLength();
	sendBuf = new char[sendLen*2];
	wcstombs(sendBuf,m_sendData,sendLen);
	if (!m_tcpClient.SendData(sendBuf,sendLen))
	{
		AfxMessageBox(_T("发送失败"));
	}
	delete[] sendBuf;
	sendBuf = NULL;		
}

//得到本地的IP地址
CString CTCPClientDlg::GetLocalIP()
{
	
	HOSTENT *LocalAddress;
	char	*Buff;
	TCHAR	*wBuff;
	CString strReturn = _T("");
	
	
	//创建新的缓冲区
	Buff = new char[256];
	wBuff = new TCHAR[256];
	//置空缓冲区
	memset(Buff, '\0', 256);
	memset(wBuff, TEXT('\0'), 256*sizeof(TCHAR));
	//得到本地计算机名
	if (gethostname(Buff, 256) == 0)
	{
		//转换成双字节字符串
		mbstowcs(wBuff, Buff, 256);
		//得到本地地址
		LocalAddress = gethostbyname(Buff);
		//置空buff
		memset(Buff, '\0', 256);
		//组合本地IP地址
		sprintf(Buff, "%d.%d.%d.%d\0", LocalAddress->h_addr_list[0][0] & 0xFF,
			LocalAddress->h_addr_list[0][1] & 0x00FF, LocalAddress->h_addr_list[0][2] & 0x0000FF, LocalAddress->h_addr_list[0][3] & 0x000000FF);
		//置空wBuff
		memset(wBuff, TEXT('\0'), 256*sizeof(TCHAR));
		//转换成双字节字符串
		mbstowcs(wBuff, Buff, 256);
        //设置返回值
		strReturn = wBuff;
	}
	else
	{
	}
	
	//释放Buff缓冲区
	delete[] Buff;
	//释放wBuff缓冲区
	delete[] wBuff;
	return strReturn;
}