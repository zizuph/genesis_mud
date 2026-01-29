/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/dstreet1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Diamond Street");  
  	set_long("You're standing at the west end of the Diamond street in the city of "+
           	"Ci'u'bori. To the south, the Topaz street starts. You have houses to your "+
           	"north, southwest and southeast. The southwestern building looks oretty much "+
           	"as a tower, and southeast is a large building.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");
  	add_item("tower","It looks like one anyway, perhaps you should check it out.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet2","east", 0,1);
  	add_exit(CIU_STR + "tstreet1","west", 0,1);
  	add_exit(CIU_HOU + "home1","north", 0,1);
  	reset_room();
}
