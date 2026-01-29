/*	Created by: 	Sir Toby, 97-07-02
 *	Purpose:	Lizards lair.
 *	Location:	/d/Kalad/common/sewers/ll10.c
 *	Modified:	
 */

#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"

void
create_room()
{
::create_room();

   set_short("Inside a lair under the city of Kabal");
   set_long("You find yourself within a dimly lit lair " +
	    "under the city of Kabal. The air is moist " +
	    "and chilly. On the walls you see burned out " +
	    "torches stuck into holes in the walls. You " +
	    "notice a dimly flickering light from the " +
	    "northeastern hallway. To the southeast is " +
	    "a dark passage. To the west you can enter " +
	    "a dark tunnel. " + "@@dwarf_check");

   add_item("ground", "The ground is made of rock and very dirty.\n");
   add_item( ({"wall","walls","rock wall","rock walls"}),
	     "The walls are cut out of the rock. They are moisty.\n");
   add_item("ceiling","The ceiling is cut directly out of the rock.\n");
   add_item( ({"torch","torches","burned torch","burned torches"}),
	    "They are regular torches, though already burned out and " +
	    "of no use.\n");
   add_item( ({"hole","holes"}),"The holes are made to hold torches.\n");
   
   add_cmd_item( ({"smell","sniff"}),"air",
		"The air smells damp and feel moisty in your nostrils.\n");
   add_cmd_item("touch",({"wall","walls","rock wall","rock walls"}),
		"The walls are dripping from water and your hand get wet.\n");

   add_exit(PATH + "ll9.c","west",0,1);
   add_exit(PATH + "ll11.c","northeast",0,1);
   add_exit(PATH + "ll14.c","southeast",0,1);
   set_noshow_obvious(1);

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,-1);

return;
}


/* 	Function returns different things wether or not the player 
 *  	is a dwarf 	
 */

string
dwarf_check()
{
    if(TP->query_race() == "dwarf")
        return"The proud dwarf you are, you notice that the ground " +
	      "is totally flat here and that you must be deep under " +
	      "the surface of Kabal.\n"; 
	
	return"\n";
}
