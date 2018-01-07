// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Decide.h"
#include "MessageHandle.h"
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
	delete pMsg;
	if (msg.length != 0)	//MSG_REQUESTû����Ϣ��
	{
		pMsg = new char[msg.length];
		memset(pMsg, 0, msg.length);
		if (Receive(pMsg, msg.length) != msg.length)
		{
			//AfxMessageBox(_T("�յ���������"));
			return;
		}
	}
	switch (msg.type)
	{
		case MSG_LOGIN:		//���û�����
		{
			HandleLoginMsg(pMsg);
			break;
		}
		case MSG_VOTE:		//�յ���ͶƱ���
		{
			HandleVoteMsg(pMsg);
			break;
		}
		case MSG_LIST:		//���±����û���Ϣ��
		{
			HandleListMsg(pMsg);
			break;
		}
		case MSG_VERSION:	//�汾��Ϣά��
		{
			HandleVersionMsg(pMsg);
			break;
		}
		case MSG_REQUEST:	//�����û���Ϣ�б�
		{
			HandleRequstMsg(pMsg);
			break;
		}
		case MSG_STARTVOTE:  //����ͶƱ
		{
			HandleStartVoteMsg(pMsg);
			break;
		}
	}
	CSocket::OnReceive(nErrorCode);
}

// ������Ϣ
BOOL CClientSocket::SendMSG(LPSTR pBuff, MSGHEAD* msg)
{
	//����Э��ͷ
	int i = Send(msg, sizeof(MSGHEAD));
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

