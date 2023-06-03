﻿#pragma once


// Диалоговое окно COptionDialog

class COptionDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionDialog)

public:
	COptionDialog(bool bRowColumn,CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~COptionDialog();
	enum { IDD = IDD_DIALOG_OPTIONS };
	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlStaticText1;
	CStatic m_ctrlStaticText2;
	int m_nValue1;
	int m_nValue2;
	afx_msg void OnBnClickedButtonDefaults();
	virtual BOOL OnInitDialog();
private:
	bool m_bRowColumnDialog;
};
	
