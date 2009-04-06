#include <math.h>
#include <iostream>


class spread_sheet_cell_container{
	vector<spread_sheet_cell> cells;
	
public:
	bool contains(const coord& c) const{
		for(size_t i=0; i<cells.size( ); i++)
			if (cells[i].get_coord( ) == c) return true;
		return false;
	}
	size_t size( ) const {return cells.size( );}
	const spread_sheet_cell& operator[](size_t idx)const{
		return cells[idx];
	}


};
class spread_sheet{
friend class CfgView;

protected:	
	spread_sheet_cell_container sp_cells;
	spread_sheet_dimension client_area;	
	GLfloat pos_x( int x ) {return ((GLfloat) x / (GLfloat) client_area.width) * (GLfloat) client_area.num_cols + (GLfloat) real::one( );}
	GLfloat pos_y (int y ) {return (GLfloat)y / (GLfloat) client_area.height * (GLfloat) client_area.num_rows + real::one( );}

	spread_sheet_cell active_cell;
	void draw_2D_vert_lines(  ) const{
		GLfloat pos_x = 0.0f;
		for(int i=0; i <= client_area.num_cols; i++){
			glBegin(GL_LINES);
				glVertex3f(pos_x, 0.0f, 0.0f);
				glVertex3f(pos_x, client_area.height, 0.0f);
			glEnd();
			pos_x += client_area.cell_2D_width();
		}
	}
	void draw_2D_hor_lines( ) const{
		GLfloat pos_y = 0.0f;
		for(int i=0; i <= client_area.num_cols; i++){
			glBegin(GL_LINES);
				glVertex3f(0.0f, pos_y, 0.02f);
				glVertex3f(client_area.width, pos_y, 0.02f);
			glEnd();
			pos_y += client_area.cell_2D_height( );
		}
	}				
	void draw_data( void ){
		::glPushMatrix();  
		//project_three_d( );
		//glTranslatef(win_width/hor_step( ),0.0f,0.0);				// Move Left And Into The Screen
/*		glTranslatef(0.0, 0.0f,-3.0f);				// Move Left And Into The Screen
	
		glBegin(GL_TRIANGLES);					// Start Drawing The Pyramid
			glColor3f(1.0f,0.0f,0.0f);			// Red
	glVertex3f( 0.0f, (GLfloat)vert_step( )/2.0f, 0.0f);			// Top Of Triangle (Front)
	glColor3f(0.0f,1.0f,0.0f);			// Green
	glVertex3f(-hor_step( )/2.0f,-vert_step( )/2.0, 0.0f);			// Left Of Triangle (Front)
	glColor3f(0.0f,0.0f,1.0f);			// Blue
	glVertex3f( (GLfloat)hor_step( )/2.0f,-vert_step( )/2.0, 0.0f);			// Right Of Triangle (Front)

	glEnd();
	::glPopMatrix( );	*/
}

public:
	spread_sheet( ):client_area(5,5){}	
	~spread_sheet( ){}
	void draw(spread_sheet_cell cell) const {
		draw(cell.get_coord( ).get_col( ), cell.get_coord( ).get_row( ));
	}	
	void draw( string col , int row ) const {
	
	}	
	void draw(  )  {
		//draw_data( );
		//glPushMatrix( );
		//glLoadIdentity();		
		glColor3f(0.6f, 0.7f, 0.85f);
		glBegin(GL_LINES);
			glVertex3f(0.0, 10.0f, -1.0f);
			glVertex3f(10.0, 10.0f, -1.0f);
		glEnd();					
	
		//glPopMatrix( );   
	}
	void draw_2D_cell_structure( void ) const {
		glLineWidth(1.0);
		draw_2D_vert_lines(  ); 
		draw_2D_hor_lines(  );
		active_cell.draw_2D_Outline( client_area );
	}
	
	void set_active_cell_wraps_coords( long x, long y)
	{
		active_cell.set_coordinates((int)pos_x( x ), (int)pos_y( y ));
	}
	void inspect_cell_wraps_coords(long x, long y){
		coord c((long)pos_x( x ), (long)pos_y( y));
		if (sp_cells.contains(c)){
			Ccell_info_dlg dlg;
			dlg.DoModal( );
		}
		else{
			spread_sheet_cell new_cell(c);
			cell_prop_sheet dlg(new_cell);
			dlg.DoModal( );
		}
	}




};



