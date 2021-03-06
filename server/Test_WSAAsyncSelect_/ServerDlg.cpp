// Test_WSAAsyncSelect_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include <string.h>

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


// CTest_WSAAsyncSelect_Dlg dialog




CTest_WSAAsyncSelect_Dlg::CTest_WSAAsyncSelect_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest_WSAAsyncSelect_Dlg::IDD, pParent)
	, m_msgString(_T(""))
{
	m_msgString = L"";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_WSAAsyncSelect_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_LIST, m_msgString);
	DDX_Control(pDX, IDC_LIST_DOWNLOAD, m_listBox_nickClient);
}

BEGIN_MESSAGE_MAP(CTest_WSAAsyncSelect_Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LISTEN, &CTest_WSAAsyncSelect_Dlg::OnBnClickedListen)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CTest_WSAAsyncSelect_Dlg::OnBnClickedQuit)
	ON_LBN_SELCHANGE(IDC_LIST_DOWNLOAD, &CTest_WSAAsyncSelect_Dlg::OnLbnSelchangeListDownload)
	ON_LBN_SELCHANGE(IDC_LIST_NICK, &CTest_WSAAsyncSelect_Dlg::OnLbnSelchangeListNick)
	ON_EN_CHANGE(IDC_EDIT_MESSAGE_LIST, &CTest_WSAAsyncSelect_Dlg::OnEnChangeEditMessageList)
	ON_BN_CLICKED(IDC_BUTTON1, &CTest_WSAAsyncSelect_Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTest_WSAAsyncSelect_Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTest_WSAAsyncSelect_Dlg message handlers

BOOL CTest_WSAAsyncSelect_Dlg::OnInitDialog()
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

	// TODO: Add extra initialization here :
	//==================code=====================
	//cai nay thay lam cho bon H, chi dung code cua thay va phat trien len ^^
	//Tao thu vien : khoi tao no
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(iResult != 0)
	{
		MessageBox(L"Error! Khong the khoi tao thu vien.");
	}
	msgType = 0;
	flagName = 1;
	count = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest_WSAAsyncSelect_Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTest_WSAAsyncSelect_Dlg::OnPaint()
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
HCURSOR CTest_WSAAsyncSelect_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CTest_WSAAsyncSelect_Dlg::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg == WM_SOCKET)
		SockMsg(wParam, lParam);
	return CDialog::WindowProc(msg, wParam, lParam);
}

void CTest_WSAAsyncSelect_Dlg::SockMsg(WPARAM wParam, LPARAM lParam)
{
	if(WSAGETSELECTERROR(lParam))
	{
		closesocket(wParam);
	}
	switch(WSAGETSELECTEVENT(lParam))
	{
		//nhận accept từ Client : 
		case FD_ACCEPT:
			Client.sockClient = accept(sockServer, NULL, NULL);
			Client.cName = "";
			Client.ID = count;
			GetDlgItem(IDC_BTN_LISTEN)->EnableWindow(FALSE);
			flagName = 1;
			count++;
			break;
		//nhận các yêu cầu từ CLient : 
		case FD_READ:
			if(!msgType)//Nhan so byte
			{
				recv(wParam, (char*)&buffLength, sizeof(int), 0);
				msgType = 1;
			}
			else
			{
				char* buffer = new char[buffLength + 1];
				recv(wParam, buffer, buffLength, 0);
				char choice = buffer[buffLength -1];
				buffer[buffLength - 2] = '\0';
				switch(choice)
				{
				//chuoi nhan dc: "nick_name-1"
				case '1' :
					{				
						if(DanhSach.empty())
						{
							Client.cName = buffer;
							DanhSach.push_back(Client);
							USES_CONVERSION;
							LPCTSTR LPbuffer = A2W(buffer);
							m_listBox_nickClient.AddString(LPbuffer);
							m_msgString += buffer;
							m_msgString += " log in.";
							m_msgString += "\r\n";
							UpdateData(FALSE);
							flagName = 0;
							msgType = 0;
							break;
						}
						else
						{
							int flag = 0;
							for(unsigned int i = 0; i < DanhSach.size(); i++)
							{
								if(strcmp(DanhSach[i].cName, buffer) == 0)
								{
									MessageBox(L"Error, Nick name exits !");
									flag = 1;
									msgType = 0;
									break;
								}
							}
							if(flag == 0)
							{
								Client.cName = buffer;
								DanhSach.push_back(Client);
								USES_CONVERSION;
								LPCTSTR LPbuffer = A2W(buffer);
								m_listBox_nickClient.AddString(LPbuffer);
								m_msgString += buffer;
								m_msgString += " log in.";
								m_msgString += "\r\n";
								msgType = 0;
								flagName = 0;
								UpdateData(FALSE);
								/*
								//Gui danh sach client ve cho Client :
								char *listData;
								int size = 1;
								for(unsigned int i = 0; i < DanhSach.size() - 1; i++)
								{
								size += strlen(DanhSach[i].cName);
								size++;
								}
								send(wParam, (char*)&size, sizeof(int), 0);
								if(size == 1)
								{
								listData = new char[size];
								listData[0] = '\0';
								//lay tung ten client vao chuoi :
								for(unsigned int i = 0; i < DanhSach.size() -1; i++)
								{
								strcat(listData,DanhSach[i].cName);
								strcat(listData,",");
								flag = 1;
								}
								send(wParam, listData, size, 0);
								}
								*/
							}
						}
					}
				//nhan noi dung chat : "noidung-2"
				case '2' :
					{
						m_msgString += buffer;
						m_msgString += "\r\n";
						msgType = 0;
						UpdateData(FALSE);
						delete buffer;
					}

				//Chat private : "nick name-3"
				case  '3' :
					{
						for(unsigned int i = 0; i < DanhSach.size(); i++)
						{
							if(strcmp(DanhSach[i].cName, buffer) == 0)
							{
								//tim thay nick client chat private : 

								break;
							}
						}
					}
				}//end switch.
			}
			break;
		case FD_CLOSE:
			m_msgString += Client.cName;
			m_msgString += " log off.";
			m_msgString += "\r\n";
			UpdateData(FALSE);
			closesocket(wParam);
			break;
	}
}


BOOL CTest_WSAAsyncSelect_Dlg::PreTranslateMessage(MSG* msg)
{
	return CDialog::PreTranslateMessage(msg);
}


void CTest_WSAAsyncSelect_Dlg::OnBnClickedListen()
{
	// TODO: Add your control notification handler code here
	sockServer = socket(AF_INET,SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockServer, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(sockServer, 5);
	int iResult = WSAAsyncSelect(sockServer, m_hWnd, WM_SOCKET, FD_READ|FD_ACCEPT|FD_CLOSE);
	if(iResult)
		MessageBox(L"Can't call WSAAsyncSelect");
	GetDlgItem(IDC_BTN_LISTEN)->EnableWindow(FALSE);
}


void CTest_WSAAsyncSelect_Dlg::OnBnClickedQuit()
{
	closesocket(sockServer);
	WSACleanup();
	exit(0);
}

void CTest_WSAAsyncSelect_Dlg::OnLbnSelchangeListDownload()
{
	// TODO: Add your control notification handler code here
}

void CTest_WSAAsyncSelect_Dlg::OnLbnSelchangeListNick()
{
	// TODO: Add your control notification handler code here
}

void CTest_WSAAsyncSelect_Dlg::OnEnChangeEditMessageList()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTest_WSAAsyncSelect_Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_msgString = "";
	msgType = 0;
	UpdateData(FALSE);
}

void CTest_WSAAsyncSelect_Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}
