// InputTextDialog.cpp : implementation file
//

#include "stdafx.h"
#include "EindOpdr.h"
#include "InputTextDialog.h"
#include "afxdialogex.h"


// InputTextDialog dialog

IMPLEMENT_DYNAMIC(InputTextDialog, CDialog)

InputTextDialog::InputTextDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputTextDialog::IDD, pParent)
{
	
}

InputTextDialog::~InputTextDialog()
{
}

BOOL InputTextDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  SetDlgItemText(IDC_EDIT1, m_value);

  return TRUE;
}

BOOL InputTextDialog::DestroyWindow()
{
  GetDlgItemText(IDC_EDIT1, m_value);

  return CDialog::DestroyWindow();
}

void InputTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, tekst);
}


BEGIN_MESSAGE_MAP(InputTextDialog, CDialog)
END_MESSAGE_MAP()


// InputTextDialog message handlers
