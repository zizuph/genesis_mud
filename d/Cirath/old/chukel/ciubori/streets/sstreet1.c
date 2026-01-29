/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/sstreet1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Sapphire Street");  
  	set_long("You are standing on Sapphire Street in the central part of "+
           	"Ci'u'bori. West lies an entrance to a strange shop in a large building. "+
           	"East is a crowded entrance to Ciubori Library. A quite popular place "+
           	"here. North is a crossroad.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet3", "north", 0,1);
  	add_exit(CIU_STR + "sstreet2", "south", 0,1);
  	//add_exit(CIU_HOU + "ringshop", "west", 0,1);
  	//add_exit(CIU_HOU + "library", "east", 0,1);
  	reset_room();
}
