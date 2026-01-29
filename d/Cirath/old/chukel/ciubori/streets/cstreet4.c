/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/cstreet4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Southeastern corner");  
  	set_long("The intersection of Crystal Street and Ruby Street. There are "
  		+"buildings to your northeast and northwest. A narrow street goes "
  		+"off southeast to one of the guard towers which have been placed "
  		+"there in order to protect the city.\n");  
  		
    	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "rstreet5","west", 0,1);
  	add_exit(CIU_STR + "cstreet3","north", 0,1);
  	add_exit(CIU_GUA + "g3","southeast", 0,1);
  	reset_room();
}
