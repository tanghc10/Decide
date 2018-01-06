#pragma once
const int MSG_INFO = 1;		//����IP�Լ������˿���Ϣ
const int MSG_VOTE = 2;		//ͶƱ��Ϣ
const int MSG_LIST = 3;		//�û��б�
const int MSG_VERSION = 4;	//�汾��Ϣ

//��Ϣͷ
typedef struct msg {
	int type;
	int version;
	int length;
}MSGHEAD;

// IP�������˿���Ϣ
typedef struct ipinfo {
	char ip[20];
	 int port;
}IPINFO;

// ͶƱ��Ϣ
typedef struct vote {
	int choice;
	int flag;
}VOTE;