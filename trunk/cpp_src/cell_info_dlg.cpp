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
IMPLEMENT_DYNAMIC(cell_info_dlg, CDialog)

cell_info_dlg::cell_info_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(cell_info_dlg::IDD, pParent)
{

}

cell_info_dlg::~cell_info_dlg()
{
}

void cell_info_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cell_info_dlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &cell_info_dlg::OnEnChangeEdit1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &cell_info_dlg::OnTcnSelchangeTab1)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()
void cell_info_dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void cell_info_dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{	
	*pResult = 0;
}

int cell_info_dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitCommonControls( );
	return 0;
}

void cell_info_dlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
}

