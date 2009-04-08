#pragma once

#include "gl/gl.h"
#include "gl/glu.h"
#include <string>

using namespace std;

class opengl_static_scene{
	GLdouble frustum_bottom_top_angle;
	
public:
	GLdouble get_frustum_bottom_top_angle( void ) const {return frustum_bottom_top_angle;}
	void set_frustum_bottom_top_angle( GLdouble newAngle ) {
		frustum_bottom_top_angle = newAngle;
	}
	
	opengl_static_scene( GLdouble frustum_bot_top_angle = 45.0f):
	  frustum_bottom_top_angle(frustum_bot_top_angle){}
	void project_three_d( const CView& v) const {
		RECT r;
		v.GetClientRect(&r);
		glMatrixMode(GL_PROJECTION);						
		glLoadIdentity();  
		GLdouble gldAspect (r.bottom ? (GLdouble) r.right/ (GLdouble) r.bottom : 0.0f);
		gluPerspective(frustum_bottom_top_angle, gldAspect, 0.1f,100.0f);	
		glViewport(0,0,r.right,r.bottom);						
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity(); 
	}
	void project_two_d(  const CView& v ) const {
		RECT r;
		v.GetClientRect(&r);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();	
		glOrtho(0.0f,(GLdouble) r.right, 0.0f, (GLdouble)r.bottom, 0.0, -1.0);
		glViewport(0, 0, r.right, r.bottom);
		glMatrixMode(GL_MODELVIEW);   
	}		
	virtual void draw( ) const{
		::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		::glPushMatrix();
			::glTranslatef(0.0f, 0.0f, -20.0f);
			::glRotatef(30.0f,0.0f,1.0f,0.0f);
			
			::glBegin(GL_TRIANGLES);
			::glColor3f(1.0,0.0,0.0);
			::glVertex3f(-5.0f, 0.0f, 5.0f);
			::glColor3f(0.0,1.0,0.0);
			::glVertex3f(0.0f, 5.0f, 0.0f);
			::glVertex3f(5.0f, 0.0f, 5.0f);

			::glColor3f(1.0,0.0,0.0);
			::glVertex3f(-5.0f, 0.0f, -5.0f);
			::glColor3f(0.0,1.0,0.0);
			::glVertex3f(0.0f, 5.0f, 0.0f);
			::glVertex3f(5.0f, 0.0f, -5.0f);
	::glEnd( );
	::glPopMatrix();
    ::glFinish();

	}
};

class opengl_font_handler {
	GLuint	base;		
public:
	GLvoid kill_2D_Fonts(GLvoid){glDeleteLists(base, 96);}
	GLvoid init_2D_font( const HDC& hDC)
	{
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
	GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
	{
	float		length=0;								// Used To Find The Length Of The Text
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	/*for (unsigned int loop=0;loop<(strlen(text));loop++)	// Loop To Find Text Length
	{
		length+=gmf[text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width
	}
      
    glTranslatef(-length/2,0.0f,0.0f);					// Center Our Text On The Screen*/
					
	
	glPushAttrib(GL_LIST_BIT);		
	glPushMatrix( );
	glListBase(base - 32);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopMatrix( );
	glPopAttrib();										// Pops The Display List Bits
	}
};


class opengl_msvc_view : public CView{
protected:	
	opengl_static_scene scene;	
	opengl_font_handler writer;	
	
	GLYPHMETRICSFLOAT gmf[256];	
	/*GLvoid init_3D_font(GLvoid)								
	{
		HDC hDC = m_pDC->GetSafeHdc( );
		HFONT	font;										// Windows Font ID
		base = glGenLists(256);								// Storage For 256 Characters
		font = CreateFont(	-12,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						_T("Comic Sans MS"));				// Font Name

		SelectObject(hDC, font);							// Selects The Font We Created

		wglUseFontOutlines(	hDC,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						base,							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);							// Address Of Buffer To Recieve Data
	}*/
	/*GLvoid kill_3D_Font(GLvoid)									// Delete The Font
	{
		glDeleteLists(base, 256);								// Delete All 256 Characters
	}*/


	BOOL init_openGL( void );
	HGLRC m_hrc;
    CDC*    m_pDC;
	BOOL SetupPixelFormat( void );
	

protected: // create from serialization only
	opengl_msvc_view();
	DECLARE_DYNCREATE(opengl_msvc_view)

public:
	virtual ~opengl_msvc_view(){}
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	

	/*void print_txt(string text, int x, int y){
		glPushMatrix( );
		scene.project_two_d( *this );
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
	}	*/
	

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





