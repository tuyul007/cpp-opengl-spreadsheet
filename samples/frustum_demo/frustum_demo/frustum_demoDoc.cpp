// frustum_demoDoc.cpp : implementation of the Cfrustum_demoDoc class
//

#include "stdafx.h"
#include "frustum_demo.h"

#include "frustum_demoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cfrustum_demoDoc

IMPLEMENT_DYNCREATE(Cfrustum_demoDoc, CDocument)

BEGIN_MESSAGE_MAP(Cfrustum_demoDoc, CDocument)
END_MESSAGE_MAP()


// Cfrustum_demoDoc construction/destruction

Cfrustum_demoDoc::Cfrustum_demoDoc()
{
	// TODO: add one-time construction code here

}

Cfrustum_demoDoc::~Cfrustum_demoDoc()
{
}

BOOL Cfrustum_demoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cfrustum_demoDoc serialization

void Cfrustum_demoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cfrustum_demoDoc diagnostics

#ifdef _DEBUG
void Cfrustum_demoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cfrustum_demoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cfrustum_demoDoc commands
