// LinkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Decide.h"
#include "LinkDlg.h"
#include "afxdialogex.h"


// CLinkDlg �Ի���

IMPLEMENT_DYNAMIC(CLinkDlg, CDialogEx)

CLinkDlg::CLinkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LINKDLG, pParent)
	, localIP(2130706433)
	, groupIP(2130706433)
	, localPort(6666)
	, groupPort(6666)
{

}

CLinkDlg::~CLinkDlg()
{
}

void CLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_LOCALIP, localIP);
	DDX_IPAddress(pDX, IDC_GROUPIP, groupIP);
	DDX_Text(pDX, IDC_LOCALPORT, localPort);
	DDX_Text(pDX, IDC_GROUPPORT, groupPort);
}


BEGIN_MESSAGE_MAP(CLinkDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLinkDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLinkDlg ��Ϣ�������


void CLinkDlg::OnBnClickedOk()
{
	UpdateData();
	if (localIP == 0 || groupIP == 0 || localPort == 0 || groupPort == 0)
	{
		AfxMessageBox(_T("�������Ϣ��Ч!"));
		return;
	}
	char ip[20];
	IN_ADDR addr1, addr2;
	addr1.S_un.S_addr = htonl(localIP);
	addr2.S_un.S_addr = htonl(groupIP);
	//inet_ntoa����һ��char *,�����char *�Ŀռ�����inet_ntoa���澲̬����
	theApp.m_IP.Empty();
	theApp.groupIP.Empty();
	inet_ntop(AF_INET, &addr1, ip, sizeof(ip));
	theApp.m_IP = ip;
	inet_ntop(AF_INET, &addr2, ip, sizeof(ip));
	theApp.groupIP = ip;
	theApp.m_Port = localPort;
	theApp.groupPort = groupPort;

	CDialogEx::OnOK();
}
