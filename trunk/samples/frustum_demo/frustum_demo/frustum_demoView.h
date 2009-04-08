// frustum_demoView.h : interface of the Cfrustum_demoView class
//


#pragma once


class Cfrustum_demoView : public opengl_msvc_view
{
protected: // create from serialization only
	Cfrustum_demoView();
	DECLARE_DYNCREATE(Cfrustum_demoView)

// Attributes
public:
	Cfrustum_demoDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Cfrustum_demoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in frustum_demoView.cpp
inline Cfrustum_demoDoc* Cfrustum_demoView::GetDocument() const
   { return reinterpret_cast<Cfrustum_demoDoc*>(m_pDocument); }
#endif

