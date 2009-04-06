#pragma once
#include "stdafx.h"
#include "open_gl_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(opengl_msvc_view, CView)

BEGIN_MESSAGE_MAP(opengl_msvc_view, CView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()
opengl_msvc_view::opengl_msvc_view()
{
}

#ifdef _DEBUG
void opengl_msvc_view::AssertValid() const
{
	CView::AssertValid();
}

void opengl_msvc_view::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif

void opengl_msvc_view::refresh_window( ){
	InvalidateRect(NULL,TRUE);
    UpdateWindow();	
}
opengl_msvc_view::~opengl_msvc_view()
{
}
BOOL opengl_msvc_view::init_openGL(){

    this->m_pDC = new CClientDC(this) ;
    if ( NULL == m_pDC ) 
    {
        TRACE("failure to get DC") ;
        return false;
    }
    if (!SetupPixelFormat())
    {
        return false;
    }

    if ( 0 == (m_hrc = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) )
        {
        return false;
        }

    if ( FALSE == ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hrc ) )
        {
        
            return false;
        }   
    ::glClearColor(1.0f, 1.0f, 1.0f, 0.0f) ;
    ::glClearDepth( 1.0f );
    ::glEnable( GL_DEPTH_TEST );
    ::glEnable(GL_LIGHTING) ;
    ::glEnable(GL_LIGHT0) ;
    ::glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
    ::glEnable(GL_COLOR_MATERIAL) ;
	this->init_OpenGL_font( );
    return true;
}
BOOL opengl_msvc_view::SetupPixelFormat( void ){

  static PIXELFORMATDESCRIPTOR pfd = 
    {
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
        PFD_SUPPORT_OPENGL |            // support OpenGL
        PFD_DOUBLEBUFFER,               // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
//        32,                             // 32-bit z-buffer
        16, // NOTE: better performance with 16-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;

    if ( 0 == (pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) )
        {
            return FALSE;
        }

    if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) )
        {
            return FALSE;
        }
    return TRUE;
}

BOOL opengl_msvc_view::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}
void opengl_msvc_view::OnDraw(CDC* pDC)
{
	BOOL bResult = wglMakeCurrent (pDC->m_hDC, m_hrc);
    if (!bResult)
    {
          TRACE("wglMakeCurrent Failed %x\r\n", GetLastError() ) ;
    }

    
    ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    ::glPushMatrix();

	//Add app specific code here
 
	::glPopMatrix();
    ::glFinish();


    if ( FALSE == ::SwapBuffers( m_pDC->GetSafeHdc() ) )
        {

        } 
}
void opengl_msvc_view::OnSize(UINT nType, int cx, int cy) 
{
  	CView::OnSize(nType, cx, cy);
	CClientDC dc(this);
    BOOL bResult = wglMakeCurrent (dc.m_hDC, m_hrc);
    if (!bResult){
      TRACE("wglMakeCurrent Failed %x\r\n", GetLastError() ) ;
      return ;
    }
	GLdouble gldAspect (cy ? (GLdouble) cx/ (GLdouble) cy : 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective(45.0f,gldAspect,0.1f,100.0f);
    glViewport(0, 0, cx, cy);
    glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
    glLoadIdentity();                                   // Reset The Modelview Matrix                 // Reset The Modelview Matrix
}

void opengl_msvc_view::OnDestroy() 
{
	CView::OnDestroy();
	
	wglMakeCurrent(NULL, NULL) ;
    if (m_hrc){
        wglDeleteContext(m_hrc) ;
        m_hrc = NULL ;
    }
	if( m_pDC ) delete m_pDC;
	KillFont( );
}
int opengl_msvc_view::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	init_openGL( );
	return 0;
}
BOOL opengl_msvc_view::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}
