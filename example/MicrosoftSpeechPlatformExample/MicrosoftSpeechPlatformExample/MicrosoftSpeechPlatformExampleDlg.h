
// MicrosoftSpeechPlatformExampleDlg.h : ��� ����
//

#pragma once

// CMicrosoftSpeechPlatformExampleDlg ��ȭ ����
class CMicrosoftSpeechPlatformExampleDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMicrosoftSpeechPlatformExampleDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MICROSOFTSPEECHPLATFORMEXAMPLE_DIALOG };

	UINT m_unVolumeValue;
	long m_nRateAdjustValue;
	CString m_strSpeechText;
	CComboBox m_ctrlVoiceList;
	CSliderCtrl m_ctrlVolumeSlider;
	CSliderCtrl m_ctrlRateAdjustSlider;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;

	CComPtr<ISpVoice> m_cpVoice;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnTtsPlay();
	afx_msg void OnBnClickedBtnTtsSave();
	afx_msg void OnCbnSelchangeCboVoiceList();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()
};
