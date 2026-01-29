/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/dstreet5.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Diamond Street");  
  	set_long("You are standing on Diamond Street in the northeastern part of "+
           	"Ciubori. North lies one a house belonging to one of the "+
           	"citizens. South lies a large, impressive building, which you "+
           	"can't enter from here. East you see a crossroad.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "cstreet1", "east", 0,1);
  	add_exit(CIU_STR + "dstreet4", "west", 0,1);
  	add_exit(CIU_HOU + "home4", "north", 0,1);
  	reset_room();
}
