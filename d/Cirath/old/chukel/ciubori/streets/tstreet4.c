/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/tstreet4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Southwestern corner");  
  	set_long("This is the crossing between Topaz and Ruby Street. Topaz "
+"street leads north of here and Ruby, east.  There are buildings "
+"to the northeast and northwest.  A small street leads to "
+"one of the guard towers that protects the city from attackers.\n");

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
add_item("street","The street is made of bricked stones, fit precisely together.\n");
add_item(({"tower","guard tower"}),"The guard tower looms above the buildings and seems to protect the city well.\n");
  	OUTSIDE;

  	add_exit(CIU_STR + "rstreet1", "east", 0,1);
  	add_exit(CIU_STR + "tstreet3", "north", 0,1);
  	add_exit(CIU_GUA + "g4", "southwest", 0,1);
  	reset_room();
}
