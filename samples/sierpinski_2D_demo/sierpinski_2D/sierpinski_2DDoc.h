// sierpinski_2DDoc.h : interface of the Csierpinski_2DDoc class
//


#pragma once


class Csierpinski_2DDoc : public CDocument
{
protected: // create from serialization only
	Csierpinski_2DDoc();
	DECLARE_DYNCREATE(Csierpinski_2DDoc)

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
	virtual ~Csierpinski_2DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


