/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/cstreet3.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Topaz Street");  
  	set_long("This is the Crystal Street in the eastern part of the cirathian "
  		+"city Ci'u'bori. To your west is a very large building where a "
  		+"nice-looking hotel has its entrance. East is another house..\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "cstreet2","north", 0,1);
  	add_exit(CIU_STR + "cstreet4","south", 0,1);
  	add_exit(CIU_HOU + "home6","east", 0,1);
  	add_exit(CIU_HOU + "hotel","west", 0,1);
  	reset_room();
}
