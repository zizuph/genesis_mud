/*	Created by: 	Sir Toby, 97-07-03
 *	Purpose:	Lizards lair. Guard room.
 *	Location:	/d/Kalad/common/sewers/ll4.c
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

   set_short("Inside a room under the city of Kabal");
   set_long("You find yourself in a guard room. It is scanty decorated, " +
	    "only two chairs and a table. It is cut directly out of the " +
	    "rock and mud. The ground is very dirty. The only exit is " +
	    "south back into the tunnel. " + "@@dwarf_check" );

   add_item("ground", "The ground is cut out of rock and very dirty.\n");
   add_item( ({"wall","walls","mud wall","mud walls"}),
            "The walls are cut directly out of the rock and mud.\n");
   add_item("ceiling","The ceiling is cut directly out of the mud and " +
            "supported by wooden beams.\n");
   add_item( ({"beam","beams","wooden beam","wooden beams"}),
            "The beams are made out of fresh wood and supports the " +
            "ceiling safely.\n");
   add_item( ({"chair","chairs"}),"The chairs are made of wood and they " +
		           	  "look well used.\n");
   add_item("table","The table is made of simple wood. On the table lies " +
		    "a deck of cards.\n");
   add_item( ({"cards","deck of cards","deck"}),"It is simple playing cards.\n");

   add_cmd_item( ({"smell","sniff"}),"air",
		"The air smells damp and feel moisty in your nostrils.\n");

   add_exit(PATH + "ll3.c","south",0,1);
   set_noshow_obvious(1);

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,-1);

return;
}


/* 	Funktion returns different things wether or not the player 
 *  	is a dwarf 	
 */

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return "You notice that the ground is totally flat here.\n"; 

	return"\n";
}