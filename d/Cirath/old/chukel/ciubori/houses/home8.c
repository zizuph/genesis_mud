/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/home8.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("a home in Ciubori");  
  	set_long("Not coded yet, this is supposed to be the mayors house. (Feel free to "+
           	"come up with ideas or quests we can put here).\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");

  	INSIDE;

  	add_exit(CIU_STR + "rstreet2", "north", 0, 1);
  	reset_room();
}
