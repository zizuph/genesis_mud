/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/upper4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{ 	
    object npc = present ("woman", TO);
    if(!objectp(npc))
	{
    		bring_room_mob("woman", CIU_NPC + "ciuwoman", 1, 1);
	}
}

void
create_room()
{
  	set_short("Upper floor in house");  
  	set_long("This is the upper floor of a house in Ci'u'bori. The room "+
           	"is as clean as the bottom floor and is used as bedroom. "+
           	"You can get a great view of the streetlife through a "+
           	"window and there is a large bed in the corner.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item("window","You can see the hustling streets of Ci'u'bori if "+
    		"you look through it.\n");
  	add_item("bed","It's big, and looks nice to sleep in.\n");
  	add_item("view","Through the window you can see the busy citizens of "+
    		"the city running around on the street below.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");

  	INSIDE;

  	add_exit(CIU_HOU + "home4", "down", 0, 1);
  	reset_room();
}
