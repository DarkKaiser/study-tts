
// MicrosoftSpeechPlatformExampleDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MicrosoftSpeechPlatformExample.h"
#include "MicrosoftSpeechPlatformExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMicrosoftSpeechPlatformExampleDlg ��ȭ ����


CMicrosoftSpeechPlatformExampleDlg::CMicrosoftSpeechPlatformExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMicrosoftSpeechPlatformExampleDlg::IDD, pParent)
	, m_unVolumeValue(0)
	, m_nRateAdjustValue(0)
	, m_strSpeechText(_T("�ȳ��ϼ���. �׽�Ʈ ���ڿ��Դϴ�."))
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


// CMicrosoftSpeechPlatformExampleDlg �޽��� ó����

BOOL CMicrosoftSpeechPlatformExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// ��Ʈ���� �ʱ�ȭ�մϴ�.
	m_ctrlVolumeSlider.SetRange(0, 100);
	m_ctrlVolumeSlider.SetRangeMin(0);
	m_ctrlVolumeSlider.SetRangeMax(100);
	m_ctrlVolumeSlider.SetTicFreq(10);

	m_ctrlRateAdjustSlider.SetRange(-10, 10);
	m_ctrlRateAdjustSlider.SetRangeMin(-10);
	m_ctrlRateAdjustSlider.SetRangeMax(10);
	m_ctrlRateAdjustSlider.SetTicFreq(1);

	// Speech Platform�� �ʱ�ȭ�մϴ�.
	HRESULT hr = m_cpVoice.CoCreateInstance(CLSID_SpVoice);
	if (SUCCEEDED(hr))
	{
		SpInitTokenComboBox(m_ctrlVoiceList.GetSafeHwnd(), SPCAT_VOICES);

		OnCbnSelchangeCboVoiceList();
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMicrosoftSpeechPlatformExampleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	SpDestroyTokenComboBox(m_ctrlVoiceList.GetSafeHwnd());

	m_cpVoice.Release();
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMicrosoftSpeechPlatformExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMicrosoftSpeechPlatformExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMicrosoftSpeechPlatformExampleDlg::OnCbnSelchangeCboVoiceList()
{
	ISpObjectToken* pObjectToken = SpGetComboBoxToken(m_ctrlVoiceList.GetSafeHwnd(), m_ctrlVoiceList.GetCurSel());
	if (pObjectToken)
	{
		// ���õ� �׸����� ������ �����Ѵ�.
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
		AfxMessageBox(_T("ISpObjectToken�� ���� �� �����ϴ�."));
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
			AfxMessageBox(_T("����� �����Ͽ����ϴ�."));
		}
	}
	else
	{
		AfxMessageBox(_T("����� �����Ͽ����ϴ�."));
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
					AfxMessageBox(_T("���� ���� �۾��� �����Ͽ����ϴ�."));
				}

				cpStream->Close();
			}
			else
			{
				AfxMessageBox(_T("���� ���� �۾��� �����Ͽ����ϴ�."));
			}

			cpStream.Release();
		}
		else
		{
			AfxMessageBox(_T("���� ���� �۾��� �����Ͽ����ϴ�."));
		}
	}
	else
	{
		AfxMessageBox(_T("���� ���� �۾��� �����Ͽ����ϴ�."));
	}
}
