/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/cstreet1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Northeastern corner");  
  	set_long("Here, Diamond and Crystal streets intersect. Diamond Street "
  		+"goes off to the east and Crystal Street to the south. There "
  		+"are houses to the northwest and southwest. There is also a narrow "
  		+"street which leads towards one of the many guard towers which are "
		+"placed about the city to secure it from unwanted intruders.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
	add_item("street","The street is made of cobblestones, skillfully put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet5","west", 0,1);
  	add_exit(CIU_STR + "cstreet2","south", 0,1);
  	add_exit(CIU_GUA + "g2","northeast", 0,1);
  	reset_room();
}
