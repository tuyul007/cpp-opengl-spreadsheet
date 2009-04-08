// frustum_demoDoc.h : interface of the Cfrustum_demoDoc class
//


#pragma once


class Cfrustum_demoDoc : public CDocument
{
protected: // create from serialization only
	Cfrustum_demoDoc();
	DECLARE_DYNCREATE(Cfrustum_demoDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cfrustum_demoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


