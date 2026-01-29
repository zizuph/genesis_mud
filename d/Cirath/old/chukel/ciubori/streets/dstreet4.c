/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/dstreet4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Diamond Street");  
  	set_long("You are travelling the hustling Diamond Street in the northern part "+
           	"of the cirathian city, Ci'u'bori. North is a house owned by one of "+
           	"the quite wealthy citizens living here. South is a very large building "+
           	"and east is a crossroad.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet5","east", 0,1);
  	add_exit(CIU_STR + "dstreet3","west", 0,1);
  	add_exit(CIU_HOU + "home3","north", 0,1);
  	reset_room();
}
