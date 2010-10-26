// Test_WSAAsyncSelect_Dlg.h : header file
//

#pragma once
#include "afxwin.h"
//code them
#define WM_SOCKET WM_USER + 1
#define PORT 25000
#include <vector>
using namespace std;

struct DinhDanh
{
	int ID;
	char* cName;
	SOCKET sockClient;
};
//end code them

// CTest_WSAAsyncSelect_Dlg dialog
class CTest_WSAAsyncSelect_Dlg : public CDialog
{
// Construction
public:
	CTest_WSAAsyncSelect_Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_WSAASYNCSELECT__DIALOG };
	
	
public:
	virtual BOOL PreTranslateMessage(MSG* msg);//add
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);//code them

// Implementation
protected:
	//khoi tao ham o day :
	void SockMsg(WPARAM wParam, LPARAM lParam);//code them
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	//code them
	//Socket
	SOCKET sockServer;
	sockaddr_in serverAddr;

	//Cac bien dem:
	int msgType, flagName, count;
	int buffLength;
	DinhDanh Client;
	vector<DinhDanh> DanhSach;
	//end code them
	DECLARE_MESSAGE_MAP()
public:
	CString m_msgString;
	afx_msg void OnBnClickedListen();
	afx_msg void OnBnClickedQuit();
	CListBox m_listBox_nickClient;//bien control xu ly list box NickClient
	afx_msg void OnLbnSelchangeListDownload();
	afx_msg void OnLbnSelchangeListNick();
	afx_msg void OnEnChangeEditMessageList();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
