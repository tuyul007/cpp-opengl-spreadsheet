// sierpinski_2DView.h : interface of the Csierpinski_2DView class
// must be linked to objects defined in
// google project cpp-spreadsheet/cpp-src


#pragma once

class sierpinski {
	vector<sierpinski*> sub_triangles;
	gl_triangle* outline;

public:
	sierpinski( ):outline(NULL){
		sub_triangles.resize(3);
	}
	~sierpinski( ){
		if(outline) delete outline;
		vector<sierpinski*>::iterator it = sub_triangles.begin( );
		while(it != sub_triangles.end( )){
			if (*it) {
				delete *it;
				*it = NULL;
			}
			it++;
		}
	}

	
	void recurse(size_t idx, gl_point a, gl_point b, gl_point c, size_t depth){
		if (depth == 0) return;
		if(sub_triangles[idx] == NULL)
		{
			sub_triangles[idx] = new sierpinski;
		}
		else
		{	
			sub_triangles[idx]->draw(gl_triangle (a, b, c), depth - 1);
			return;
		}
	}
	void draw( gl_triangle t, size_t depth = 7) {
		if (outline == NULL )
		{
			outline = new gl_triangle(t);
		
		}
		if (*outline == t){
			outline->draw_outlined( );
			recurse(0, t.a, t.a.mid_point(t.b), t.a.mid_point(t.c), depth);
			recurse(1, t.a.mid_point(t.b), t.b, t.b.mid_point(t.c), depth);
			recurse(2, t.a.mid_point(t.c), t.b.mid_point(t.c), t.c, depth);
		}
		else
		{
			outline->a = t.a;
			outline->b = t.b;
			outline->c = t.c;
			outline->draw_outlined( );
			return;
		}
	}
};
class opengl_scene : public opengl_static_scene{
public:
	sierpinski s1;
	sierpinski s2;
	sierpinski s3;
	void draw( const CView& v ) ;
};
class Csierpinski_2DView : public opengl_msvc_view
{
protected: 

	Csierpinski_2DView();
	DECLARE_DYNCREATE(Csierpinski_2DView)
	
	opengl_font_handler screen_writer;
	opengl_scene scene;
	void DRAW_SCENE( );
	void PREPARE_ANIMATE( );

public:
	Csierpinski_2DDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~Csierpinski_2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void speed_up( );
	afx_msg void slow_down( );
	afx_msg void stop_animation( );
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in sierpinski_2DView.cpp
inline Csierpinski_2DDoc* Csierpinski_2DView::GetDocument() const
   { return reinterpret_cast<Csierpinski_2DDoc*>(m_pDocument); }
#endif

