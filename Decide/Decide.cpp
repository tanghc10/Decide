
// Decide.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Decide.h"
#include "DecideDlg.h"
#include "LinkDlg.h"
#include "ClientSocket.h"
#include "ServerSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDecideApp

BEGIN_MESSAGE_MAP(CDecideApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDecideApp ����

CDecideApp::CDecideApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDecideApp ����

CDecideApp theApp;


// CDecideApp ��ʼ��

BOOL CDecideApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("TALK"));
	
	m_Socket = new CServerSocket();
	if (!m_Socket)
	{
		AfxMessageBox(_T("��̬�����������׽��ֳ���"));
		return false;
	}
	CLinkDlg Linkdlg;
	INT_PTR nResponse = Linkdlg.DoModal();
	if (nResponse == IDOK)
	{
		// ���û�����IP�Ͷ˿���Ϣ�󣬴�������ָ���˿ڵķ������׽���
		if (!m_Socket->Create(theApp.m_Port))
		{
			AfxMessageBox(_T("�����׽��ִ���"));
			m_Socket->Close();
			return false;
		}
		if (!m_Socket->Listen())
		{
			AfxMessageBox(_T("����ʧ�ܣ�"));
			m_Socket->Close();
			return false;
		}
		// �ж��Ƿ����Ⱥ��
		if (!((m_IP.CompareNoCase(groupIP) == 0) && (m_Port == groupPort)))
		{
			CClientSocket *pClient = new CClientSocket();
			if (!pClient)
			{
				AfxMessageBox(_T("�ڴ治�㣡"));
				return false;
			}
			if (!pClient->Create())
			{
				AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
				return false;
			}
			if (!pClient->Connect(theApp.groupIP.GetBuffer(0), theApp.groupPort))
			{
				AfxMessageBox(_T("����Ⱥ��ʧ�ܣ�"));
				return false;
			}
			MSGHEAD msg;
			IPINFO localip;
			msg.type = MSG_INFO;
			msg.length = sizeof(localip);
			msg.version = -1;
			theApp.WChar2MByte(m_IP, localip.ip, sizeof(localip));
			localip.port = m_Port;
			pClient->SendMSG((char*)&localip, &msg);
			pClient->Close();
			delete pClient;
		}
		CDecideDlg dlg;
		m_pMainWnd = &dlg;
		nResponse = dlg.DoModal();
		if (nResponse == IDCANCEL)
		{

		}
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

CServerSocket * CDecideApp::GetServerSocket() const
{
	return m_Socket;
}

int CDecideApp::ExitInstance()
{
	if (m_Socket)
	{
		delete m_Socket;
		m_Socket = NULL;
	}
	return CWinApp::ExitInstance();
}

BOOL CDecideApp::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n > nlen)
		return FALSE;

	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);

	return TRUE;
}

