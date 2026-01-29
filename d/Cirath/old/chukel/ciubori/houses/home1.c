/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/home1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("a home in Ciubori");  
  	set_long("Not done yet...\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");

  	INSIDE;

  	add_exit(CIU_STR + "dstreet1", "south", 0, 1);
  	reset_room();
}
