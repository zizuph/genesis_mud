/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/cstreet2.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Crystal Street");  
  	set_long("You are standing on Crystal Street in the eastern part of "+
           	"Ci'u'bori. East is a house belonging to one of the "+
           	"citizens of the city. West of you is an entrance to a very large "+
           	"building. It is the local post office where you can send mail to "+
           	"friends all around the world.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "cstreet1","north", 0,1);
  	add_exit(CIU_STR + "cstreet3","south", 0,1);
  	add_exit(CIU_HOU + "home5","east", 0,1);
  	add_exit(CIU_HOU + "post","west", 0,1);
  	reset_room();
}
