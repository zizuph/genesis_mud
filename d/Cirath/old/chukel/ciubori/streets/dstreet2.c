/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/dstreet2.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Diamond Street");  
  	set_long("This is the Diamond street that leads in east-west direction in the "+
           	"northern parts of the city Ci'u'bori. You have buildnings to the north "+
           	"and south. The south buildning i very large. There's a crossroad to your"+
           	"east\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet3","east", 0,1);
  	add_exit(CIU_STR + "dstreet1","west", 0,1);
  	add_exit(CIU_HOU + "home2","north", 0,1);
  	reset_room();
}
