/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/rstreet5.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Ruby Street");  
  	set_long("You're travelling on the Ruby Street which is placed in the southern parts "+
           	"Ci'u'bori. To the south lies the impressive city wall, and you can hear the "+
		"ocean's fierce attempt to break it down from the other side. East you see "+
           	"a crossroad and north is a large building.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "rstreet4", "west", 0,1);
  	add_exit(CIU_STR + "cstreet4", "east", 0,1);
  	reset_room();
}
