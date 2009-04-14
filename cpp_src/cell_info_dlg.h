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
