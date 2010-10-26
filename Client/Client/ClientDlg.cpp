// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClientDlg dialog




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
	, m_serverAdd(_T(""))
	, m_chatString(_T(""))
	, m_msgString(_T(""))
	, m_nameString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERADDR, m_serverAdd);
	DDX_Text(pDX, IDC_EDIT_CHAT, m_chatString);
	DDX_Text(pDX, IDC_EDIT_MSG, m_msgString);
	DDX_Text(pDX, IDC_EDIT_NICK, m_nameString);
	DDX_Control(pDX, IDC_LIST_NICK, m_ListClient);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BTN_SEND, &CClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CClientDlg::OnBnClickedQuit)
	//ON_MESSAGE(WM_SOCKET,SockMsg)
	ON_LBN_DBLCLK(IDC_LIST_NICK, &CClientDlg::OnLbnDblclkListNick)
	ON_LBN_DBLCLK(IDC_LIST_DOWNLOAD, &CClientDlg::OnLbnDblclkListDownload)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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

	//code them
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(iResult != 0)
		MessageBox(L"Error!Khong the khoi tao thu vien");
	msgType = 0;
	m_serverAdd = "127.0.0.1";
	UpdateData(FALSE);
	//end code them

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClientDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	//code them
	UpdateData();
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
  	hostent* host = NULL;
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(PORT);

	int size = m_serverAdd.GetLength();// lay kich thuoc dia chi server
	char *temp= new char[size+1];
	memset(temp,0,size+1);
	wcstombs(temp, m_serverAdd, size+1);//chuyen tu kieu CString sang kieu char*
	serverAdd.sin_addr.s_addr = inet_addr(temp);
	if(serverAdd.sin_addr.s_addr == INADDR_NONE)
	{
		host = gethostbyname(temp);
		if(host == NULL)
		{
			MessageBox(L"Unable to resolve server");
		}
		CopyMemory(&serverAdd.sin_addr, host->h_addr_list[0],host->h_length);
	}
	int iResult = connect(sockClient,(sockaddr*)&serverAdd, sizeof(serverAdd));
	if (iResult == SOCKET_ERROR){
			MessageBox(L"Back connect ...");
			return;
	}
	m_nameString += "-1";
	size = m_nameString.GetLength();//lay kich thuoc cua Nickname Client
	temp = new char [size + 1];
	memset(temp, 0, size+1);
	wcstombs(temp, m_nameString, size +1);
	send(sockClient, (char*)&size, sizeof(int), 0);//gui kich thuoc
	send(sockClient, temp, size, 0);//gui data

	/*
	//nhan danh sach client online tu server : 
	recv(sockClient, (char*)&size, sizeof(int), 0);
	if(size > 1)
	{
		recv(sockClient, temp, size, 0);
		char * pch;
		pch = strtok((char *)temp,",");
		USES_CONVERSION;
		while (pch != NULL)
		{
			LPCTSTR LPbuffer = A2W(pch);
			m_ListClient.AddString(LPbuffer);
			pch = strtok(NULL,",");
		}
	}
	*/

	WSAAsyncSelect(sockClient, m_hWnd, WM_SOCKET, FD_ACCEPT|FD_READ|FD_CLOSE);// ham non-blocking
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);//disable nut connect
	GetDlgItem(IDC_EDIT_CHAT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NICK)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);//end able nut send
	//end code them
}

LRESULT CClientDlg::SockMsg(WPARAM wParam, LPARAM lParam)
{
	if(WSAGETSELECTERROR(lParam))
	{
		closesocket(wParam);
	}
	switch(WSAGETSELECTEVENT(lParam))
	{
		case FD_ACCEPT:

			MessageBox(L"case FD_ACCEPT");
			break;
		case FD_READ:

			MessageBox(L"case FD_READ");
			break;
		case FD_CLOSE:

			MessageBox(L"case FD_CLOSE");
			closesocket(wParam);
			break;
	}
	return 0;
}

BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// code them
	//Nhan enter == nhan button send
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		int idCtrl = this->GetFocus()->GetDlgCtrlID();
		if(idCtrl == IDC_EDIT_CHAT)
		{
			OnBnClickedSend();
			return TRUE;
		}
	}
	//end code them
	return CDialog::PreTranslateMessage(pMsg);
}

void CClientDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString chuoi;// chuoi tam 
	chuoi += m_nameString;//lay ten
	chuoi += ": ";
	chuoi += m_chatString;//lay chuoi chat
	m_msgString += chuoi;//in ra man hinh cua Client noi dung chat.
	m_msgString += "\r\n";
	m_chatString = "";

	chuoi += "-2";
	int Len = chuoi.GetLength();
	char* buffer = new char[Len];
	memset(buffer,0,Len);
	wcstombs(buffer, chuoi, Len);

	send(sockClient, (char*)&Len, sizeof(int), 0);//gui kich thuoc
	send(sockClient, buffer, Len, 0);//gui chuoi <nick>:<noi dung chat> cho Server
	
	UpdateData(FALSE);
	delete buffer;
}

void CClientDlg::OnBnClickedQuit()
{
	// TODO: Add your control notification handler code here
	if(sockClient != INVALID_SOCKET)
	{
		shutdown(sockClient, SD_BOTH);
	}
	closesocket(sockClient);
	WSACleanup();
	exit(0);
}

void CClientDlg::OnLbnDblclkListNick()
{
	// TODO: Add your control notification handler code here
	//Choice Client chat private : 
}

void CClientDlg::OnLbnDblclkListDownload()
{
	// TODO: Add your control notification handler code here
	//choice file download :
}
