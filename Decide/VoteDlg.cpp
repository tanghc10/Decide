// VoteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Decide.h"
#include "VoteDlg.h"
#include "afxdialogex.h"


// CVoteDlg �Ի���

IMPLEMENT_DYNAMIC(CVoteDlg, CDialogEx)

CVoteDlg::CVoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VOTE_DIALOG, pParent)
{

}

CVoteDlg::~CVoteDlg()
{
}

void CVoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVoteDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CVoteDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CVoteDlg ��Ϣ�������

//�յ��ڵ㷢�͵�ͶƱ���󣬷���ͶƱ�Ľڵ㷢�������ѡ��
void CVoteDlg::OnReceiveRequest()
{
	/*
	�յ���
	key: question value:(CString)m_questiong
	key: answer value: (CString)m_answer1
	key: answer value: (CString)m_answer2
	*/
	
	/*
	��������DisplayVote()��ʾͶƱ�������ѡ��
	*/

}

//�������ڵ㷢���Լ���ѡ��
void CVoteDlg::OnSendOption(CString &choice)
{
	/*
	���ͣ�key:choice value:(CString)choice
	*/
}

//��ʾͶƱ�������ѡ��
void CVoteDlg::DisplayVote(CString &question, CString &answer1, CString &answer2)
{
	//��IDC_EDIT_QUESTION_R��ʾͶƱ����
	((CEdit*)GetDlgItem(IDC_EDIT_QUESTION_R))->ReplaceSel(question);
	//�������б�����ѡ��
	m_option->InsertString(0, answer1);
	m_option->InsertString(1, answer2);
}

//��ʾͶƱ���ս��
void CVoteDlg::DisplayResult(CString &result) const
{
	((CEdit*)GetDlgItem(IDC_EDIT_RESULT))->ReplaceSel(result);
}


void CVoteDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�ڵ�������ѡ��
	CString choice;  //�ڵ�������ѡ��
	int nIndex = m_option->GetCurSel();  //��ȡѡ�е�����
	m_option->GetLBText(nIndex, choice);
	//���ú���OnSendOption()���������ڵ㷢�ͱ��ڵ��ѡ��
	OnSendOption(choice);
	CDialogEx::OnOK();
}


