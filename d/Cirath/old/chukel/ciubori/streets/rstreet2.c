/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/rstreet2.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Ruby Street");  
  	set_long("This street is called Ruby Street and is places in the southern parts of "+
           	"the cirathian city Ci'u'bori. South of you is th city wall and north lies a "+
           	"rather big buildning.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "rstreet3", "east", 0,1);
  	add_exit(CIU_STR + "rstreet1", "west", 0,1);
  	add_exit(CIU_HOU + "home8", "south", 0,1);
  	reset_room();
}
