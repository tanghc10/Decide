// ServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Decide.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket ��Ա����


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CClientSocket *Client(0);
	Accept(*Client);
	CSocket::OnAccept(nErrorCode);
}
