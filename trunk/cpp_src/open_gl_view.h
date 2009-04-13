#pragma once
#include <base_numbers.h>
#include <mmsystem.h> 

#include "gl/gl.h"
#include "gl/glu.h"

#include <ctime>
#include <string>

using namespace std;

class gl_point{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	gl_point (GLfloat X=0.0f, GLfloat Y=0.0f, GLfloat Z=0.0f){
		x = X;
		y = Y;
		z = Z;
	}
	bool operator == (const gl_point p) const {
		return (x == p.x && y == p.y && z == p.z);
	}
	gl_point mid_point (const gl_point& pt) const{
		return gl_point((x + pt.x)/2.0f, (y + pt.y)/2.0f, (z + pt.z)/2.0f);
	}
	void vertex( ) const {glVertex3f( x, y, z);}
};
class gl_triangle{

public:	
	gl_point a;
	gl_point b;
	gl_point c;
	gl_triangle( gl_point A, gl_point B, gl_point C)
	{	
		a = A;
		b = B;
		c = C;
	}
	void draw_outlined( )const{
		glBegin(GL_LINE_LOOP);
		a.vertex( );
		b.vertex( );
		c.vertex( );
		glEnd( );
	}
	bool operator==(const gl_triangle t) const {
		return (a == t.a && b == t.b && c == t.c);
	}
};
class opengl_static_scene{
	class color_type {
	public:
		void black( ) const {::glColor3f(0.0f,0.0f,0.0f);}
		void red( ) const {::glColor3f(1.0f, 0.0f, 0.0f);}
		void lime( ) const {::glColor3f(0.0f, 1.0f, 0.0f);}
		void purple( ) const {::glColor3f(1.0f, 0.14f, 0.6667f);}  
		void white( ) const {::glColor3f(1.0f, 1.0f, 1.0f);}
	};
	class shape_type {
	public:
		void triangle( gl_point a, gl_point b, gl_point c) const{
			glBegin(GL_LINE_LOOP);
			a.vertex( );
			b.vertex( );
			c.vertex( );
			glEnd( );
		}
	};
	class projection_type{
		bool switch_projection;
	public:
		void _2D( ) {switch_projection = false;}
		void _3D( ){switch_projection = true;}
		string type( void ) const
		{
			return (string)(switch_projection ? "3D" : "2D");
		}
	};
	projection_type projection;

protected:
	bool m_draw_cartesian_guide;
	vector<GLfloat> O;
	GLdouble frustum_bottom_top_angle;
	

public:
	color_type color;
	opengl_static_scene( GLdouble frustum_bot_top_angle = 45.0f )
		{
			frustum_bottom_top_angle = frustum_bot_top_angle;
			O.resize(3);
		}

	GLdouble get_frustum_bottom_top_angle( void ) const {return frustum_bottom_top_angle;}
	void set_frustum_bottom_top_angle( GLdouble newAngle ) {
		frustum_bottom_top_angle = newAngle;
	}	
	void project_three_d( const CView& v)  {
		projection._3D( );
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
	void project_two_d(  const CView& v ) {
		projection._2D( );	
		RECT r;
		v.GetClientRect(&r);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();	
		glOrtho(0.0f,(GLdouble) r.right, 0.0f, (GLdouble)r.bottom, 0.0, -1.0);
		glViewport(0, 0, r.right, r.bottom);
		glMatrixMode(GL_MODELVIEW);   
		glLoadIdentity(); 
	}			
	virtual void draw_cartesian_guides( ) const;
	virtual void draw( ) const;
};

class opengl_font_handler {
	GLuint	base;		
public:
	GLvoid kill_2D_Fonts(GLvoid){glDeleteLists(base, 96);}
	GLvoid init_2D_font( const HDC& hDC)
	{
		HFONT	font;										
		HFONT	oldfont;									

		base = glGenLists(96);						

		font = CreateFont(	-24,							
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
		oldfont = (HFONT)SelectObject(hDC, font);           
		wglUseFontBitmaps(hDC, 32, 96, base);			
		SelectObject(hDC, oldfont);							
		DeleteObject(font);								
	}
	GLvoid glPrint(real::dimension dim, const char *fmt, ...) const				
	{
		glRasterPos2i((GLint)dim.left, (GLint)dim.bottom);
											
		char		text[256];								
		va_list		ap;										

		if (fmt == NULL) return;											
		va_start(ap, fmt);									// Parses The String For Variables
			vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
		va_end(ap);											// Results Are Stored In Text
		glPushAttrib(GL_LIST_BIT);		
		glPushMatrix( );
		glListBase(base - 32);									// Sets The Base Character to 0
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
		glPopMatrix( );
		glPopAttrib( );										
	}
};
class opengl_animation {
	bool animation_running;
	DWORD m_previousElapsedTime; 
	size_t fps_rate;
public:
	void set_fps( int fps ){
		if (fps > 0) fps_rate = fps;
	}
	size_t get_fps( void ) const {return fps_rate;}


	opengl_animation( int fps=24, bool ar =  false):fps_rate(fps),animation_running(ar){}
	bool is_running( ) const {return animation_running;}
	void turn_on( ) 
	{
		animation_running = true;
		m_previousElapsedTime = time( NULL );
	}
	void turn_off( ) 
	{
		animation_running = false;
		m_previousElapsedTime = time( NULL );
	}

	DWORD	time_to_redraw(  )
		{ 
			if (!animation_running) return false;
			DWORD m_ElapsedTime = timeGetTime( );
			if (m_ElapsedTime - m_previousElapsedTime > fps_rate){
				m_previousElapsedTime = m_ElapsedTime ;
				return true;
			}
			return false;
		}
};
class opengl_msvc_view : public CView{
protected:	
	opengl_animation animation;
	
	BOOL init_openGL( void );
	HGLRC m_hrc;
    CDC*    m_pDC;
	BOOL SetupPixelFormat( void );
	
protected: // create from serialization only
	opengl_msvc_view();
	virtual void DRAW_SCENE( ) {};
	virtual void PREPARE_ANIMATE( ){};
	DECLARE_DYNCREATE(opengl_msvc_view)

public:
	virtual ~opengl_msvc_view(){}
	virtual void OnDraw(CDC* pDC); 
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	
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





