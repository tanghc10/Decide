#include "stdafx.h"
#include "cJSON.h"
#include "Decide.h"
#include "MessageHandle.h"
#include "MSG.h"
#include "VoteDlg.h"

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

	theApp.SendListMsg(ip, port);
	theApp.setVersion(theApp.version + 1);
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

	if (version != theApp.version)
		theApp.VersionCompare(version, ip, port);
	cJSON_Delete(root);
}

void HandleListMsg(char *pMsg)
{
	cJSON *json_root = cJSON_Parse(pMsg);
	if (!json_root)
	{
		AfxMessageBox(_T("Message format error"));
		return;
	}

	cJSON *temp = cJSON_GetObjectItem(json_root, "version");
	if (!temp)
	{
		AfxMessageBox(_T("param error"));
		cJSON_Delete(json_root);
		return;
	}

	theApp.setVersion(temp->valueint);
	temp = cJSON_GetObjectItem(json_root, "data");
	if (!temp)
	{
		AfxMessageBox(_T("param error"));
		return;
	}

	theApp.IPList.clear();	//���IP�б�
	//����дIP�б�
	int num = cJSON_GetArraySize(temp);
	cJSON *Node = NULL;
	cJSON *NodeIP = NULL;
	cJSON *NodePort = NULL;
	for (int i = 0; i < num; i++)
	{
		Node = cJSON_GetArrayItem(temp, i);
		if (!Node)
			break;
		NodeIP = cJSON_GetObjectItem(Node, "ip");
		if (!NodeIP)
		{
			AfxMessageBox(_T("param error"));
			break;
		}
		NodePort = cJSON_GetObjectItem(Node, "port");
		if (!NodePort)
		{
			AfxMessageBox(_T("param error"));
			break;
		}

		IPINFO IPNode;
		strncpy(IPNode.ip, NodeIP->valuestring, 20);
		IPNode.port = NodePort->valueint;

		theApp.IPList.push_back(IPNode);
	}

	cJSON_Delete(json_root);
}

void HandleRequstMsg(char *pMsg)
{
	cJSON *root = NULL;
	cJSON *temp = NULL;

	root = cJSON_Parse(pMsg);
	if (!root)
	{
		AfxMessageBox(_T("param����"));
		cJSON_Delete(root);
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

	theApp.SendListMsg(ip, port);
}

void HandleVoteMsg(char *pMsg) {
	if (theApp.is_start == 0)
		return;
	cJSON *root = NULL;
	cJSON *temp = NULL;
	CHOICE MyChoice;

	root = cJSON_Parse(pMsg);
	if (!root) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	temp = cJSON_GetObjectItem(root, "answer");
	if (!temp) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	MyChoice.answer = temp->valueint;
	temp = cJSON_GetObjectItem(root, "flag");
	if (!temp) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	MyChoice.flag = temp->valueint;
	temp = cJSON_GetObjectItem(root, "count");
	if (!temp) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	MyChoice.count = temp->valueint;

	theApp.HandleChoice(MyChoice);

}

void HandleStartVoteMsg(char *pMsg) {
	cJSON *root = NULL;
	cJSON *temp = NULL;
	LCHVOTE vote;

	root = cJSON_Parse(pMsg);
	if (!root) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	temp = cJSON_GetObjectItem(root, "question");
	if (!temp) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	strcpy_s(vote.question, temp->valuestring);
	temp = cJSON_GetObjectItem(root, "answer1");
	if (!temp) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	strcpy_s(vote.answer1, temp->valuestring);
	temp = cJSON_GetObjectItem(root, "answer2");
	if (!temp) {
		AfxMessageBox(_T("param error"));
		cJSON_Delete(root);
		return;
	}
	strcpy_s(vote.answer2, temp->valuestring);
	
	theApp.setVoteQue(vote);
	theApp.setIsStart(0);
	theApp.StartVote();
}