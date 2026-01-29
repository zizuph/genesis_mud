/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/home4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{ 	
    object npc = present ("man", TO);
    if(!objectp(npc))
	{
    		bring_room_mob("man", CIU_NPC + "ciuman", 1, 1);
	}
}

void
create_room()
{
  	set_short("a home in Ciubori");  
  	set_long("This is the home of a family. The room looks clean and the "+
           	"furniture is polished. Everything looks neat and well-kept. "+
           	"There are some stairs leading up to the upper floor.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");

  	INSIDE;

  	add_exit(CIU_STR + "dstreet5", "south", 0, 1);
  	add_exit(CIU_HOU + "upper4", "up", 0, 1);
  	reset_room();
}
