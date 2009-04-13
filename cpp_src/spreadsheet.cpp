#pragma once
#include "stdafx.h"
#include <spreadsheet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void spread_sheet::draw_2D_cell_structure(  ) const {
		glLineWidth(1.0);
		glColor3f(0.3f,0.3f,0.3f);
		draw_2D_vert_lines(  ); 
		draw_2D_hor_lines(  );
		active_cell.draw_2D_Outline( client_area );
		writer.glPrint(real::dimension(0,0,0,0), "Yo mama");	
	}	