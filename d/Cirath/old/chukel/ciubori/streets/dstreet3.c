/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/streets/dstreet3.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Diamond Street");  
  	set_long("You're standing in a crossroad, close to the northern gate in Ci'u'bori. "+
           	"East and west leads the Diamond Street, while south is the Sapphire "+
           	"Street which leads into the central parts of the city.. North lies the "+
           	"northern gate..\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("street","The street is made by bricked stones, neatly put together.\n");
  	add_item("gate","The gate consists of a draw-bridge that protects the city from "+
           	"uninvited guests.\n");

  	OUTSIDE;

  	add_exit(CIU_STR + "dstreet4","east", 0,1);
  	add_exit(CIU_STR + "dstreet2","west", 0,1);
  	// add_exit(CIUBORI + "gate","north", 0,1);
  	add_exit(CIU_STR + "sstreet1","south", 0,1);
  	reset_room();
}
