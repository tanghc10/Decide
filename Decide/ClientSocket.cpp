// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Decide.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��Ա����


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	this->Close();
	delete this;
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	//������Ϣͷ
	MSGHEAD msg;
	char* pMsg = NULL;
	pMsg = new char[sizeof(msg)];
	memset(pMsg, 0, sizeof(msg));
	Receive(pMsg, sizeof(msg));
	msg.type = ((MSGHEAD*)pMsg)->type;
	msg.length = ((MSGHEAD*)pMsg)->length;
	msg.version = ((MSGHEAD*)pMsg)->version;
	delete pMsg;
	pMsg = new char[msg.length];

	switch (msg.type)
	{
		case MSG_INFO:		//���û�����
		{
			delete pMsg;
			pMsg = new char[msg.length];
			Receive(pMsg, msg.length);

		}
		case MSG_VOTE:		//�յ���ͶƱ���
		{
			delete pMsg;
			pMsg = new char[msg.length];
			Receive(pMsg, msg.length);

		}
		case MSG_LIST:		//���±����û���Ϣ��
		{
			delete pMsg;
			pMsg = new char[msg.length];
			Receive(pMsg, msg.length);

		}
		case MSG_VERSION:	//�汾��Ϣά��
		{

		}
	}
	CSocket::OnReceive(nErrorCode);
}

// ������Ϣ
BOOL CClientSocket::SendMSG(LPSTR pBuff, MSGHEAD* msg)
{
	//����Э��ͷ
	int i = Send(msg, sizeof(MSG));
	if (i == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ʹ���"));
		return FALSE;
	};
	//������Ϣ
	if (pBuff)
	{
		if (Send(pBuff, msg->length) == SOCKET_ERROR)
		{
			AfxMessageBox(_T("���ʹ���"));
			return FALSE;
		};
	}

	return  TRUE;
}

