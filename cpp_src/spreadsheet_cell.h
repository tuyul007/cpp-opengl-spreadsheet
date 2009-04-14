
//Other libraries
#include "gl/gl.h"
#include "gl/glu.h"

#include <string>
#include <vector>


using namespace std;

class data{
public:
	typedef char* address;
};
class data_chunk{
	data::address begin;
	data::address end;
public:
	data_chunk( data::address b=NULL, data::address e=NULL ):begin(b),end(e){}
};
class spread_sheet_dimension : public real::dimension, public integral::grid{


public:
	spread_sheet_dimension(int ncols, int nrows):grid(ncols, nrows){}
	
	GLfloat cell_2D_width( )const{
		return (GLfloat)width / (GLfloat) num_cols;
	}
	GLfloat cell_2D_height( )const{
		return (GLfloat) height / (GLfloat) num_rows;
	}

	void remLastRow( ){ if (num_rows > 1) num_rows--;}
	void remLastCol( ){if (num_cols > 1) num_cols--;}
};

class coord {
	protected:
		string col;
		int row;
		int depth;

	public:

		coord (string c=string("A"), int r = 1):col(c),row(r),depth(0){}
		coord (long l, long r = 1):row(r),depth(0){
			col = to_col_coordinates( l );
		}	
		bool operator ==(const coord& c){
			return (c.row == row && c.col == col);
		}
		string get_col( void )const {return col;}
		int get_row( void )const {return row;}

		
		static int excel_column_numerical(string ExcelValue) {
			int acc = 0;
			for (int idx = (ExcelValue.size( ) - 1) ; idx >= 0 ; --idx){
				//Add base 26 digit converted to decimal to accumulator
				int exp = ExcelValue.size( ) - 1 - idx;
				acc +=  (ExcelValue[idx] - 'A' + 1) * ((int)pow(26.0, exp));
			}
			return acc;
		}
		static string to_col_coordinates( int x ) 
		{
			int temp = ((int) x) - 1;
			vector<char> char_vec(1, 'A' + (char)(temp % 26));
			temp = temp / 26;
			while(temp  > 0){
				temp = temp - 1;
				char_vec.push_back('A' + (char)(temp % 26));
				temp = temp / 26;
			}

			string new_col;
			for(int i = char_vec.size( ) - 1; i >= 0; i--) 
				new_col += char_vec[i];
			return new_col;
		}
		friend class spread_sheet_cell;
};	


class spread_sheet_cell  {
protected:
	coord cell_coord;
	data_chunk datum;	
	string string_view;

public:
	spread_sheet_cell( coord c = coord( )):cell_coord(c){}
	coord get_coord( )const {return cell_coord;}
	
	string get_string( )const {return string_view;}
	data_chunk get_datum( ) const {return datum;}
	//void set_datum( int d ) {datum = d;}

	void set_coordinates(int x, int y)
	{
		cell_coord.col = coord::to_col_coordinates( x );
		cell_coord.row = y;		
	}
	real::dimension get_dimension(const spread_sheet_dimension& client_area) const{
		GLfloat row_idx = (GLfloat)cell_coord.get_row( );
		GLfloat col_idx = (GLfloat)coord::excel_column_numerical(cell_coord.get_col( ));
		
		GLfloat bottom = (GLfloat)client_area.height - (row_idx * client_area.cell_2D_height( ));
		GLfloat left = (col_idx - 1.0f)* client_area.cell_2D_width( );

		return real::dimension(client_area.cell_2D_width( ),client_area.cell_2D_height( ),left, bottom);


	}
	void draw_2D_Outline( const spread_sheet_dimension& client_area ) const{
		real::dimension dim(get_dimension( client_area ));
		glLineWidth(5.0);
		glBegin(GL_LINES);
				glColor3f(1.0f, 0.0f, 0.0f);			

				glVertex3f(dim.left, dim.bottom, 0.01f);
				glVertex3f(dim.left + dim.width, dim.bottom, 0.01f);

				glVertex3f(dim.left, dim.bottom + dim.height, 0.01f);
				glVertex3f(dim.left + dim.width, dim.bottom + dim.height, 0.01f);
		
				glVertex3f(dim.left, dim.bottom, 0.01f);
				glVertex3f(dim.left, dim.bottom + dim.height, 0.01f);

				glVertex3f(dim.left + dim.width, dim.bottom, 0.01f);
				glVertex3f(dim.left + dim.width, dim.bottom + dim.height, 0.01f);
		glEnd();	
	}
	void draw( ) const{}

};