
// MicrosoftSpeechPlatformExampleDlg.h : 헤더 파일
//

#pragma once

// CMicrosoftSpeechPlatformExampleDlg 대화 상자
class CMicrosoftSpeechPlatformExampleDlg : public CDialogEx
{
// 생성입니다.
public:
	CMicrosoftSpeechPlatformExampleDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MICROSOFTSPEECHPLATFORMEXAMPLE_DIALOG };

	UINT m_unVolumeValue;
	long m_nRateAdjustValue;
	CString m_strSpeechText;
	CComboBox m_ctrlVoiceList;
	CSliderCtrl m_ctrlVolumeSlider;
	CSliderCtrl m_ctrlRateAdjustSlider;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	CComPtr<ISpVoice> m_cpVoice;

	// 생성된 메시지 맵 함수
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
