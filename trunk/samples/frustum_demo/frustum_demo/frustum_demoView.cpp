// frustum_demoView.cpp : implementation of the Cfrustum_demoView class
//

#include "stdafx.h"
#include "frustum_demo.h"

#include "frustum_demoDoc.h"
#include "frustum_demoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cfrustum_demoView

IMPLEMENT_DYNCREATE(Cfrustum_demoView, opengl_msvc_view)

BEGIN_MESSAGE_MAP(Cfrustum_demoView, opengl_msvc_view)
END_MESSAGE_MAP()

// Cfrustum_demoView construction/destruction

Cfrustum_demoView::Cfrustum_demoView()
{
	// TODO: add construction code here

}

Cfrustum_demoView::~Cfrustum_demoView()
{
}

BOOL Cfrustum_demoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return opengl_msvc_view::PreCreateWindow(cs);
}

// Cfrustum_demoView drawing

void Cfrustum_demoView::OnDraw(CDC* pDC)
{
	BOOL bResult = wglMakeCurrent (pDC->m_hDC, m_hrc);
    if (!bResult)
    {
          TRACE("wglMakeCurrent Failed %x\r\n", GetLastError() ) ;
    }
	GLdouble newAngle = scene.get_frustum_bottom_top_angle( );
	newAngle = newAngle + 5.0f;

	glLoadIdentity( );
	scene.project_three_d( *this );
	scene.draw( );
	
	glLoadIdentity( );
	scene.project_two_d( *this );
	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos2i(0, 0);
	writer.glPrint("frustum angle= %f",newAngle);
	//glPopMatrix( );
	
	scene.set_frustum_bottom_top_angle( (newAngle >= 360.0f)? 0.0f : newAngle); 
	
	if ( FALSE == ::SwapBuffers( m_pDC->GetSafeHdc() ) )
        {

        } 
	refresh_window( );

}


// Cfrustum_demoView diagnostics

#ifdef _DEBUG
void Cfrustum_demoView::AssertValid() const
{
	opengl_msvc_view::AssertValid();
}

void Cfrustum_demoView::Dump(CDumpContext& dc) const
{
	opengl_msvc_view::Dump(dc);
}

Cfrustum_demoDoc* Cfrustum_demoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cfrustum_demoDoc)));
	return (Cfrustum_demoDoc*)m_pDocument;
}
#endif //_DEBUG


// Cfrustum_demoView message handlers
