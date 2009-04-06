#pragma once

#include "gl/gl.h"
#include "gl/glu.h"
#include <string>

using namespace std;

class opengl_msvc_view : public CView{
protected:	
	
	GLuint	base;			
	GLvoid KillFont(GLvoid){glDeleteLists(base, 96);}
	GLvoid init_OpenGL_font( )
	{
		HDC hDC = m_pDC->GetSafeHdc( );
		HFONT	font;										// Windows Font ID
		HFONT	oldfont;									// Used For Good House Keeping

		base = glGenLists(96);								// Storage For 96 Characters

		font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						TRUE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						_T("Courier New"));					// Font Name
		oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
		wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
		SelectObject(hDC, oldfont);							// Selects The Font We Want
		DeleteObject(font);									// Delete The Font
	}

	BOOL init_openGL( void );
	HGLRC m_hrc;
    CDC*    m_pDC;
	BOOL SetupPixelFormat( void );
	

protected: // create from serialization only
	opengl_msvc_view();
	DECLARE_DYNCREATE(opengl_msvc_view)

public:
	virtual ~opengl_msvc_view();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void project_three_d( ) const {
		RECT r;
		GetClientRect(&r);
		glMatrixMode(GL_PROJECTION);						
		glLoadIdentity();                                   
		gluPerspective(45.0f,(GLfloat)r.right/r.top,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);							
	}
	void project_two_d( ) const {
		RECT r;
		GetClientRect(&r);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();	
		glOrtho(0.0f,(GLdouble) r.right, 0.0f, (GLdouble)r.bottom, 0.0, -1.0);
		glMatrixMode(GL_MODELVIEW);   
		glViewport(0, 0, r.right, r.bottom);
	}		
	void print_txt(string text, int x, int y){
		glPushMatrix( );
		project_two_d( );
		glColor3f(0.0f,0.0f,0.0f);
		glRasterPos2i(x, y);
		glPrint(text);
		glPopMatrix( );
	}	
	GLvoid glPrint(string text) const
	{
		glPushAttrib(GL_LIST_BIT);
		glPushMatrix( );

		glListBase(base - 32);	
		glCallLists(text.size( ), GL_UNSIGNED_BYTE, text.c_str( ));

		glPopMatrix( );
		glPopAttrib( );	
	}	

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void refresh_window( );
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

};



