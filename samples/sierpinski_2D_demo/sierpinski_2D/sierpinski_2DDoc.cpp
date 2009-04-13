// sierpinski_2DDoc.cpp : implementation of the Csierpinski_2DDoc class
//

#include "stdafx.h"
#include "sierpinski_2D.h"

#include "sierpinski_2DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Csierpinski_2DDoc

IMPLEMENT_DYNCREATE(Csierpinski_2DDoc, CDocument)

BEGIN_MESSAGE_MAP(Csierpinski_2DDoc, CDocument)
END_MESSAGE_MAP()


// Csierpinski_2DDoc construction/destruction

Csierpinski_2DDoc::Csierpinski_2DDoc()
{
	// TODO: add one-time construction code here

}

Csierpinski_2DDoc::~Csierpinski_2DDoc()
{
}

BOOL Csierpinski_2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Csierpinski_2DDoc serialization

void Csierpinski_2DDoc::Serialize(CArchive& ar)
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


// Csierpinski_2DDoc diagnostics

#ifdef _DEBUG
void Csierpinski_2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Csierpinski_2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Csierpinski_2DDoc commands
