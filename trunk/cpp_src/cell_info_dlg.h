#pragma once


//Other libraries
#include <string>

using namespace std;

class visual_rep_dlg : public CPropertyPage{
	
public:	
	visual_rep_dlg(  ): CPropertyPage( ) {}
	BOOL OnInitDialog( );

	DECLARE_MESSAGE_MAP()
};

class type_and_value_dlg : public CPropertyPage{
	spread_sheet_cell& cell;

public:	
	type_and_value_dlg( spread_sheet_cell& c ): cell(c),CPropertyPage( ) {}
	BOOL OnInitDialog( );

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeEdit1();
};

class cell_prop_sheet : public CPropertySheet{

	type_and_value_dlg m_type_and_value_dlg; 
	visual_rep_dlg m_visual_rep_dlg;
public:
	cell_prop_sheet( spread_sheet_cell& cell );
};

class cell_info_dlg : public CDialog
{
	DECLARE_DYNAMIC(cell_info_dlg)

public:
	cell_info_dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~cell_info_dlg();

	enum { IDD = IDD_DIALOG1 };

protected:
	CDialog * current_dialog;
	
	CTabCtrl m_tab;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
