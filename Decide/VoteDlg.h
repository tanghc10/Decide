#pragma once
#include "afxwin.h"


// CVoteDlg �Ի���

class CVoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVoteDlg)

public:
	CVoteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVoteDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOTE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	void OnReceiveRequest();  //�յ�����ͶƱ������
	void OnSendOption(CString &choice);  //�������ڵ㷢���Լ���ѡ��
	void DisplayVote(CString &question, CString &answer1, CString &answer2);  //��ʾͶƱ�������ѡ��
	void DisplayResult(CString &result) const;  //��ʾ����ͶƱ���
	CComboBox *m_option = (CComboBox *)GetDlgItem(IDC_COMBO1);

};
