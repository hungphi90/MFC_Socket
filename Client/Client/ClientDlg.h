// ClientDlg.h : header file
//

#pragma once
#include "afxwin.h"
#define PORT 25000
#define WM_SOCKET WM_USER + 2


// CClientDlg dialog
class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };
public:
	//add
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//End add
	virtual LRESULT SockMsg(WPARAM wParam, LPARAM lParam);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	//add
	//LRESULT SockMsg(WPARAM wParam, LPARAM lParam);
	int msgType;
	int buffLength;
	SOCKET sockClient;
	sockaddr_in serverAdd;
	//end add

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	
	CString m_chatString;//bien luu noi dung chat tren editboxchat
	CString m_msgString;//bien tra ve noi dung chat tren editboxmsg
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedQuit();
	CString m_serverAdd;//bien luu dia chi server tren edit box server
	CString m_nameString;//bien luu nick client tren edit box name
	CListBox m_ListClient;//bien control de xu ly list box danh sach Client
	afx_msg void OnLbnDblclkListNick();
	afx_msg void OnLbnDblclkListDownload();
};
