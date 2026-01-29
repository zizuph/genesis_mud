/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/tstreet2.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Topaz Street");  
  	set_long("You are standing on Topaz Street in the western part of "+
           	"Ci'u'bori. The street is very crowdy and to your east you "+
           	"can see a large building which has an entrance to a shop. "+
           	"To your west is a tower-like building where some kind of "+
           	"club has their quarters.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");
  	add_item("shop","It looks that way anyway.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "tstreet1", "north", 0,1);
  	add_exit(CIU_STR + "tstreet3", "south", 0,1);
  	//add_exit(CIU_HOU + "richclub", "west", 0,1);
  	add_exit(CIU_HOU + "shop", "east", 0,1);
  	reset_room();
}
