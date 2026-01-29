/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/tstreet3.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Topaz Street");  
  	set_long("You're travelling on the Topaz Street in the western region of the "+
           	"cirathian city of Ci'u'bori. The street is quite crowdy here, propably "+
           	"because there is a pub to the east. West is the mayors office and "+
           	"northwest is a tower-like building.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");
  	add_item("pub","A place for joy and money spending.\n");
  	add_item("tower","Looks like one, since it so high. Why not check it out.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "tstreet2", "north", 0,1);
  	add_exit(CIU_STR + "tstreet4", "south", 0,1);
  	add_exit(CIU_HOU + "mayor", "west", 0,1);
  	add_exit(CIU_HOU + "pub", "east", 0,1);
  	reset_room();
}
