/*	Created by: 	Sir Toby, 97-07-02
 *	Purpose:	Lizards lair.
 *	Location:	/d/Kalad/common/sewers/ll7.c
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

   set_short("Inside a tunnel under the city of Kabal");
   set_long("You are in a dimly lit underground tunnel. It is cut " +
	    "directly out of the rock, there are torches placed in steel " +
	    "holders at the floor that provides the dim light. The " +
	    "tunnel continues to the north, looking south you see a " +
	    "hallway. To the east there seem to be a room. " + 
	    "@@dwarf_check" );

   add_item("ground", "The ground is cut out of rock and very clean.\n");
   add_item( ({"wall","walls","rock wall","rock walls"}),
	     "The walls are cut out of the rock.\n");
   add_item("ceiling","The ceiling is cut directly out of the rock.\n");
   add_item( ({"torch","torches"}),
	    "They are regular torches, providing the dim light.\n");
   add_item( ({"holder","holders","steel holder","steel holders"}),
	    "The holders are made of two black steel bars twined " +
	    "around eachother like two snakes. The top end of the " +
	    "holders are shaped like snake heads.\n");
   
   add_cmd_item( ({"smell","sniff"}),"air",
		"The air smells damp and feel moisty in your nostrils.\n");

   add_exit(PATH + "ll18.c","north",0,1);
   add_exit(PATH + "ll12.c","south",0,1);
   add_exit(PATH + "ll24.c","east",0,1);
   set_noshow_obvious(1);

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,1);

return;
}


/* 	Funktion returns different things wether or not the player 
 *  	is a dwarf 	
 */

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return "The proud dwarf you are, you notice that the ground " +
	       "is totally flat here and that you must be deep under " +
	       "the surface of Kabal.\n"; 

	return"\n";
}