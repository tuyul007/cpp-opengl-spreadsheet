// sierpinski_2DView.cpp : implementation of the Csierpinski_2DView class
//

#include "stdafx.h"
#include "sierpinski_2D.h"

#include "sierpinski_2DDoc.h"
#include "sierpinski_2DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void opengl_scene::draw( const CView& v ) {
	opengl_static_scene::draw( );
	RECT r;
	v.GetClientRect(&r);
	gl_point a(0.0f, 0.0f);
	gl_point b(((GLfloat)r.right)/2.0f, (GLfloat)r.bottom/2.0f);
	gl_point c((GLfloat)r.right, 0.0f);
	color.purple( );
	if(rand( ) % 2) s1.draw(gl_triangle(a,b,c));
	
	
	gl_point _a(0.0f, (GLfloat)r.bottom);
	gl_point _b(((GLfloat)r.right)/2.0f, (GLfloat)r.bottom/2.0f);
	gl_point _c((GLfloat)r.right, (GLfloat)r.bottom);
	color.red( );
	if(rand( ) % 2) s2.draw( gl_triangle(_a, _b, _c));

	
	gl_point A(((GLfloat)r.right)/2.0f, (GLfloat)r.bottom/2.0f);
	gl_point B(((GLfloat)r.right), (GLfloat)r.bottom);
	gl_point C((GLfloat)r.right, 0.0f);
	color.lime( );
	if(rand( ) % 2) s3.draw( gl_triangle(A, B, C));



}

IMPLEMENT_DYNCREATE(Csierpinski_2DView, opengl_msvc_view)

BEGIN_MESSAGE_MAP(Csierpinski_2DView, opengl_msvc_view)
	ON_COMMAND(ID_ANIMATION_SPEEDP, speed_up)
	ON_COMMAND(ID_ANIMATION_SPEEDM, slow_down)
	ON_COMMAND(ID_APP_ABOUT, stop_animation)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void Csierpinski_2DView::stop_animation( ){
	animation.turn_off( );
	theApp.OnAppAbout( );
	animation.turn_on( );
	refresh_window( );
}
void Csierpinski_2DView::speed_up( ){
	if(animation.get_fps( ) > 10)
		animation.set_fps(animation.get_fps( ) - 10);
	}
void Csierpinski_2DView::slow_down( ){
	animation.set_fps(animation.get_fps( ) + 10);
}


Csierpinski_2DView::Csierpinski_2DView()
{
	animation.turn_on( );
	animation.set_fps( 200 );
}

Csierpinski_2DView::~Csierpinski_2DView()
{
}

BOOL Csierpinski_2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return opengl_msvc_view::PreCreateWindow(cs);
}

#ifdef _DEBUG
void Csierpinski_2DView::AssertValid() const
{
	opengl_msvc_view::AssertValid();
}

void Csierpinski_2DView::Dump(CDumpContext& dc) const
{
	opengl_msvc_view::Dump(dc);
}

Csierpinski_2DDoc* Csierpinski_2DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Csierpinski_2DDoc)));
	return (Csierpinski_2DDoc*)m_pDocument;
}
#endif //_DEBUG

void Csierpinski_2DView::DRAW_SCENE( ){
	scene.project_two_d(  *this );
	scene.draw( *this );
	RECT r;
	GetClientRect(&r);
	scene.color.white( );
	screen_writer.glPrint(real::dimension(0.0f, 0.0f, 10.0f, (GLfloat)r.bottom/2.0f), "fps = %d", animation.get_fps( ));
}
void Csierpinski_2DView::PREPARE_ANIMATE( ){


}

int Csierpinski_2DView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (opengl_msvc_view::OnCreate(lpCreateStruct) == -1)
		return -1;
	screen_writer.init_2D_font(m_pDC->GetSafeHdc( ));
	return 0;
}

void Csierpinski_2DView::OnDestroy()
{
	opengl_msvc_view::OnDestroy();
	screen_writer.kill_2D_Fonts( );
}
