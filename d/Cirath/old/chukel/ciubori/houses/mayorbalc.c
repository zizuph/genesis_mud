/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/mayorbalc.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("Mayor's Balcony");  
  	set_long("You are standing on the mayor's private balcony, where "+
           	"he uses to hold his speaks to the citizens every now "+
           	"and then. The view is great. You can see the whole "+
           	"city from here. West is a door that leads into the "+
           	"apartment.\n");  

 	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_item("balcony","It's made of the same material as the house and it's "+
    		"decorated with figures of dragons, soldiers and weapons?\n");
  	add_item("figures","Nicely made in stone.\n");
  	add_item("house","It has two floors and is made of grey stone.\n");
  	add_item("door","The door leads into the mayor's private flat.\n");
  	add_item("view","Yes, it's great, but if you jump, you will have a "+
    		"great close-up of the street below.\n");

  	INSIDE;

  	add_exit(CIU_HOU + "mayorpriv", "west", 0, 1);
  	reset_room();
}

void
init()
{
  	::init();  
  	add_action("jumper","jump");
}

int
jumper()
{
  	write("You jump off the balcony and...\n");
  	say(QCTNAME(TP)+" jumps off the balcony, you can see "+HIM_HER(TP)+
    		"hit the concrete below.\n");
  	tell_room(CIU_STR + "tstreet3","CRASH!!! "+QCTNAME(TP)+" falls "+
    		"down from above, hitting the concrete hard.\n"+QCTNAME(TP)+" looks "+
    		"quite hurt.\n");
  	TP->move(CIU_STR + "tstreet3");
  	write("SPLAT!!! You hit the ground hard, it hurts.\n");

  	TP->heal_hp(-(random(300)+200));

  	if (TP->query_hp() <= 0)
  	{
    		TP->do_die(CIU_HOU + "mayorbalc");
    		write("You were killed by the fall.\n");
    		tell_room(CIU_STR + "tstreet3",QCTNAME(TP)+" was killed by the fall.\n");
  	}
 	return 1;
}