/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/tstreet1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Northwestern corner");  
  	set_long("You're standing in the crossing between Diamond Street and Topaz Street. "+
           	"Diamond STreet leaves east of here and Topaz Street leaves south. You have "+
           	"houses to your northeast, southeast and a tower-like building to your "+
           	"southwest. Northeast is a small street which leads to one of the guard "+
           	"towers that surrounds the city. North is a stairway that leads up to "+
           	"the upper floor of the norteastern house..\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");
  	add_item("tower","It looks like one anyway. Why don't you check it up?\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet1", "east", 0,1);
  	add_exit(CIU_STR + "tstreet2", "south", 0,1);
  	add_exit(CIU_GUA + "g1", "northwest", 0,1);
  	reset_room();
}
