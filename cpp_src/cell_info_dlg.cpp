#include "stdafx.h"
#include "cell_info_dlg.h"

BEGIN_MESSAGE_MAP(visual_rep_dlg, CPropertyPage)
END_MESSAGE_MAP()


BOOL visual_rep_dlg::OnInitDialog( ){
	return (!CPropertyPage::OnInitDialog( ));
}


BEGIN_MESSAGE_MAP(type_and_value_dlg, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT1, &type_and_value_dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

BOOL type_and_value_dlg::OnInitDialog( ){
	if (!CPropertyPage::OnInitDialog( )) return false;
	
	CStatic * colEdit = (CStatic*) GetDlgItem(IDC_COL);
	CString col(cell.get_coord( ).get_col( ).c_str( ));
	colEdit->SetWindowTextW(col);
	
	CStatic * rowEdit = (CStatic*) GetDlgItem(IDC_ROW);
	CString cstring_row;
	cstring_row.Format(_T("%d"), cell.get_coord( ).get_row( ));
	rowEdit->SetWindowTextW(cstring_row);
	
	CEdit* valEdit = (CEdit*) GetDlgItem (IDC_EDIT1);
	CString cstring_val_string_rep;
	cstring_val_string_rep.Format(_T("%d"), cell.get_datum( ));
	valEdit->SetWindowTextW(cstring_val_string_rep);
	return true;
}
void type_and_value_dlg::OnEnChangeEdit1()
{
	CEdit* valEdit = (CEdit*) GetDlgItem (IDC_EDIT1);
	CString val;
	valEdit->GetWindowTextW(val);
}


cell_prop_sheet::cell_prop_sheet( spread_sheet_cell& cell):CPropertySheet( ),
m_type_and_value_dlg( cell ){
		m_type_and_value_dlg.Construct(_T("type_and_value_dlg"), 0);
		AddPage(&m_type_and_value_dlg);

		m_visual_rep_dlg.Construct(_T("visual_rep_dlg"), 0);
		AddPage(&m_visual_rep_dlg);
	}

