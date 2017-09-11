
// MicrosoftSpeechPlatformExampleDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MicrosoftSpeechPlatformExample.h"
#include "MicrosoftSpeechPlatformExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMicrosoftSpeechPlatformExampleDlg 대화 상자


CMicrosoftSpeechPlatformExampleDlg::CMicrosoftSpeechPlatformExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMicrosoftSpeechPlatformExampleDlg::IDD, pParent)
	, m_unVolumeValue(0)
	, m_nRateAdjustValue(0)
	, m_strSpeechText(_T("안녕하세요. 테스트 문자열입니다."))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMicrosoftSpeechPlatformExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_VOICE_LIST, m_ctrlVoiceList);
	DDX_Text(pDX, IDC_VOLUME_VALUE, m_unVolumeValue);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_ctrlVolumeSlider);
	DDX_Control(pDX, IDC_SLIDER_RATE, m_ctrlRateAdjustSlider);
	DDX_Text(pDX, IDC_RATE_VALUE, m_nRateAdjustValue);
	DDX_Text(pDX, IDC_EDT_SPEECH_TEXT, m_strSpeechText);
}

BEGIN_MESSAGE_MAP(CMicrosoftSpeechPlatformExampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_CBO_VOICE_LIST, &CMicrosoftSpeechPlatformExampleDlg::OnCbnSelchangeCboVoiceList)
	ON_BN_CLICKED(IDC_BTN_TTS_PLAY, &CMicrosoftSpeechPlatformExampleDlg::OnBnClickedBtnTtsPlay)
	ON_BN_CLICKED(IDC_BTN_TTS_FILE_SAVE, &CMicrosoftSpeechPlatformExampleDlg::OnBnClickedBtnTtsSave)
END_MESSAGE_MAP()


// CMicrosoftSpeechPlatformExampleDlg 메시지 처리기

BOOL CMicrosoftSpeechPlatformExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 컨트롤을 초기화합니다.
	m_ctrlVolumeSlider.SetRange(0, 100);
	m_ctrlVolumeSlider.SetRangeMin(0);
	m_ctrlVolumeSlider.SetRangeMax(100);
	m_ctrlVolumeSlider.SetTicFreq(10);

	m_ctrlRateAdjustSlider.SetRange(-10, 10);
	m_ctrlRateAdjustSlider.SetRangeMin(-10);
	m_ctrlRateAdjustSlider.SetRangeMax(10);
	m_ctrlRateAdjustSlider.SetTicFreq(1);

	// Speech Platform을 초기화합니다.
	HRESULT hr = m_cpVoice.CoCreateInstance(CLSID_SpVoice);
	if (SUCCEEDED(hr))
	{
		SpInitTokenComboBox(m_ctrlVoiceList.GetSafeHwnd(), SPCAT_VOICES);

		OnCbnSelchangeCboVoiceList();
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMicrosoftSpeechPlatformExampleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	SpDestroyTokenComboBox(m_ctrlVoiceList.GetSafeHwnd());

	m_cpVoice.Release();
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMicrosoftSpeechPlatformExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMicrosoftSpeechPlatformExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMicrosoftSpeechPlatformExampleDlg::OnCbnSelchangeCboVoiceList()
{
	ISpObjectToken* pObjectToken = SpGetComboBoxToken(m_ctrlVoiceList.GetSafeHwnd(), m_ctrlVoiceList.GetCurSel());
	if (pObjectToken)
	{
		// 선택된 항목으로 음성을 변경한다.
		m_cpVoice->SetVoice(pObjectToken);

		USHORT usVolume;
		if (SUCCEEDED(m_cpVoice->GetVolume(&usVolume)))
		{
			m_unVolumeValue = usVolume;
			m_ctrlVolumeSlider.SetPos(m_unVolumeValue);
		}

		long nRateAdjust;
		if (SUCCEEDED(m_cpVoice->GetRate(&nRateAdjust)))
		{
			m_nRateAdjustValue = nRateAdjust;
			m_ctrlRateAdjustSlider.SetPos(m_nRateAdjustValue);
		}

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("ISpObjectToken을 구할 수 없습니다."));
	}
}

void CMicrosoftSpeechPlatformExampleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar)
	{
		HWND hWnd = pScrollBar->GetSafeHwnd();
		if (hWnd == m_ctrlVolumeSlider.GetSafeHwnd())
		{
			m_unVolumeValue = m_ctrlVolumeSlider.GetPos();
			m_cpVoice->SetVolume(m_unVolumeValue);
			UpdateData(FALSE);
		}
		else if (hWnd == m_ctrlRateAdjustSlider.GetSafeHwnd())
		{
			m_nRateAdjustValue = m_ctrlRateAdjustSlider.GetPos();
			m_cpVoice->SetRate(m_nRateAdjustValue);
			UpdateData(FALSE);
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMicrosoftSpeechPlatformExampleDlg::OnBnClickedBtnTtsPlay()
{
	UpdateData(TRUE);

	HRESULT hr = m_cpVoice->SetOutput(NULL, TRUE);
	if (SUCCEEDED(hr))
	{
		if (FAILED(m_cpVoice->Speak(m_strSpeechText, SPF_ASYNC | SPF_IS_NOT_XML, NULL)))
		{
			AfxMessageBox(_T("재생이 실패하였습니다."));
		}
	}
	else
	{
		AfxMessageBox(_T("재생이 실패하였습니다."));
	}
}

void CMicrosoftSpeechPlatformExampleDlg::OnBnClickedBtnTtsSave()
{
	UpdateData(TRUE);

	CSpStreamFormat	cAudioFormat;
	HRESULT hr = cAudioFormat.AssignFormat(SPSF_22kHz16BitStereo);
	if (SUCCEEDED(hr))
	{
		CComPtr<ISpStream> cpStream;
		hr = SPBindToFile(_T("tts.wav"), SPFM_CREATE_ALWAYS, &cpStream, &cAudioFormat.FormatId(), cAudioFormat.WaveFormatExPtr());
		if (SUCCEEDED(hr))
		{
			hr = m_cpVoice->SetOutput(cpStream, TRUE);
			if (SUCCEEDED(hr))
			{
				hr = m_cpVoice->Speak(m_strSpeechText, SPF_DEFAULT, NULL);
				if (SUCCEEDED(hr))
				{
					m_cpVoice->WaitUntilDone(INFINITE);
				}
				else
				{
					AfxMessageBox(_T("파일 저장 작업이 실패하였습니다."));
				}

				cpStream->Close();
			}
			else
			{
				AfxMessageBox(_T("파일 저장 작업이 실패하였습니다."));
			}

			cpStream.Release();
		}
		else
		{
			AfxMessageBox(_T("파일 저장 작업이 실패하였습니다."));
		}
	}
	else
	{
		AfxMessageBox(_T("파일 저장 작업이 실패하였습니다."));
	}
}
