#pragma once
#include "afxwin.h"


// InputTextDialog dialog

class InputTextDialog : public CDialog
{
	DECLARE_DYNAMIC(InputTextDialog)

private:
	CString m_value;

public:
	InputTextDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~InputTextDialog();
	CString GetValue() const {return m_value;}
	void SetValue(const CString& value) {m_value = value;}
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

// Dialog Data
	enum { IDD = IDD_INPUTTEXTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:  
	CEdit tekst;

};
