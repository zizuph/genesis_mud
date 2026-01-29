/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/rstreet3.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Ruby Street");  
  	set_long("You're standing in a crossroad between the Ruby Street, which leads east and "+
           	"west from here, the Sapphire Street, which leads north to the central parts, "+
           	"and the south gate which leads to the piers on the other side of the city wall.\n");  

 	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
   		 "and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");
  	add_item("gate","The gate is made of steel which protects the city from "+
           	"uninvited guests.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "rstreet4", "east", 0,1);
  	add_exit(CIU_STR + "rstreet2", "west", 0,1);
  	add_exit(CIU_STR + "sstreet2", "north", 0,1);
  	// add_exit(CIUBORI + "gate2", "south, 0,1);
  	reset_room();
}
