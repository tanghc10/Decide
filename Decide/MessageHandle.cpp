#include "stdafx.h"
#include "cJSON.h"
#include "Decide.h"
#include "MessageHandle.h"
#include "MSG.h"

void HandleLoginMsg(char *pMsg)
{
	cJSON *root = NULL;
	cJSON *temp = NULL;
	root = cJSON_Parse(pMsg);
	if (!root)
	{
		AfxMessageBox(_T("��Ϣ��ʽ����"));
		return;
	}

	temp = cJSON_GetObjectItem(root, "ip");
	if (!temp)
	{
		AfxMessageBox(_T("param����"));
		cJSON_Delete(root);
		return;
	}
	char *ip = temp->valuestring;
	temp = cJSON_GetObjectItem(root, "port");
	if (!temp)
	{
		AfxMessageBox(_T("param error"));
		return;
	}
	int port = temp->valueint;

	//�������
	IPINFO NewNode;
	strncpy(NewNode.ip, ip, 20);
	NewNode.port = port;
	theApp.IPList.push_back(NewNode);

	cJSON_Delete(root);

	//AfxMessageBox(_T("�µ��û�����"));
	theApp.version++;
}

void HandleVersionMsg(char *pMsg) {
	cJSON *root = NULL;
	cJSON *temp = NULL;
	
	root = cJSON_Parse(pMsg);
	if (!root)
	{
		AfxMessageBox(_T("��Ϣ��ʽ����"));
		return;
	}

	temp = cJSON_GetObjectItem(root, "version");
	if (!temp)
	{
		AfxMessageBox(_T("param error"));
		return;
	}
	int version = temp->valueint;
	CString str;
	str.Format(_T("version is %d��"), theApp.version);
	AfxMessageBox(str);
	cJSON_Delete(root);
}

void HandleRequstMsg(char *pMsg) {
	AfxMessageBox(_T("recvie requst msgs"));
}

void HandleListMsg(char *pMsg) {
	AfxMessageBox(_T("recvie list msgs"));
}