
// MicrosoftSpeechPlatformExample.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMicrosoftSpeechPlatformExampleApp:
// �� Ŭ������ ������ ���ؼ��� MicrosoftSpeechPlatformExample.cpp�� �����Ͻʽÿ�.
//

class CMicrosoftSpeechPlatformExampleApp : public CWinApp
{
public:
	CMicrosoftSpeechPlatformExampleApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMicrosoftSpeechPlatformExampleApp theApp;