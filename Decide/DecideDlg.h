
// DecideDlg.h : ͷ�ļ�
//

#pragma once


// CDecideDlg �Ի���
class CDecideDlg : public CDialogEx
{
// ����
public:
	CDecideDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DECIDE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	// ��ҪͶƱ������
	CString m_Question;
	// ѡ��1
	CString m_Answer1;
	// ѡ��2
	CString m_Answer2;
	afx_msg void OnBnClickedOk();  //���·���ͶƱ��
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);  
};
