/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/rstreet1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void create_room()
{
  	set_short("Ruby Street");  
set_long(" You are travelling down Ruby Street in the southwestern part of Ci'u'bori. "
+"You see the city wall to the south. From beyond the wall, you can hear the salty sea pounding on it from "+
"the other side. To the north is a large building and to the west you can see a crossroad.\n");

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
add_item("street","The street is made of bricked stones, put precisely together.\n");
add_item(({"wall","city wall"}),"The wall is made of polished stone, and it seems to be of Dwarven construction.\n");
add_item("crossroad","In the distance you see a crossroad.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "rstreet2", "east", 0,1);
  	add_exit(CIU_STR + "tstreet4", "west", 0,1);
  	add_exit(CIU_HOU + "home7", "south", 0,1);
  	reset_room();
}
