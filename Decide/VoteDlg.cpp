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
	DDX_Control(pDX, IDC_COMBO1, m_option);
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


//��ʾͶƱ�������ѡ��
void CVoteDlg::DisplayVote()
{
	//��IDC_EDIT_QUESTION_R��ʾͶƱ����
	((CEdit*)GetDlgItem(IDC_EDIT_QUESTION_R))->ReplaceSel(CString(theApp.VoteQue.question));
	//�������б�����ѡ��
	m_option.InsertString(0, CString(theApp.VoteQue.answer1));
	m_option.InsertString(1, CString(theApp.VoteQue.answer2));
}

//��ʾͶƱ���ս��
void CVoteDlg::DisplayResult(int &index) const
{
	CString result;
	m_option.GetLBText(index-1, result);
	((CEdit*)GetDlgItem(IDC_EDIT_RESULT))->SetWindowTextW(result);
}


void CVoteDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//get the choise
	int nIndex = m_option.GetCurSel();  //get the index of the choised question

	//Use gossip to send vote message
	CHOICE CHO;
	CHO.answer = nIndex + 1;
	CHO.flag = 0;
	CHO.count = 0;
	theApp.setIsStart(1);
	theApp.setChoice(CHO);
	theApp.setType(MSG_VOTE);
	theApp.setVoteEnd(0);
	//AfxMessageBox(_T("Vote Succeed!"));
}


BOOL CVoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DisplayVote();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
