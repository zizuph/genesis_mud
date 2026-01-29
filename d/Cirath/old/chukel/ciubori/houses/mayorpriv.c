/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/mayorpriv.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Mayor's Private Quarters");  
  	set_long("This is the mayor's private quarters and you can see "+
           	"that he is a man of expensive tastes. Silk and gold are "+
           	"the dominating materials here. A bed is in one of the "+
           	"corners and in the opposite stands a small desk. A "+
           	"door leads out to a balcony.\n");  

  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("bed","Looks like a very nice place to spend the night in.\n");
  	add_item("desk","Just a small desk made of wood.\n");
  	add_item(({"silk","gold"}),"Yes, the mayor must be a very wealthy man.\n");
  	add_item("door","The door leads out to the balcony.\n");
  	add_item("balcony","Why don't you check it out?\n");

  	INSIDE;

  	add_exit(CIU_HOU + "mayor", "down", 0, 1);
  	add_exit(CIU_HOU + "mayorbalc", "east", 0, 1);
  	reset_room();
}
