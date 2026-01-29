/*	Created by: 	Sir Toby, 97-07-02
 *	Purpose:	Lizards lair.
 *	Location:	/d/Kalad/common/sewers/ll9.c
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
   set_long("You find yourself within yet another tunnel " +
	    "under the city of Kabal. The air is moisty " +
	    "and chilly. The tunnel is cut directly out of " +
	    "the rock. " + "@@dwarf_check" );

   add_item("ground", "The ground is made of rock and very dirty.\n");
   add_item( ({"wall","walls","rock wall","rock walls"}),
	     "The walls are cut out of the rock. They are moisty.\n");
   add_item("ceiling","The ceiling is cut directly out of the rock.\n");

   add_cmd_item( ({"smell","sniff"}),"air",
		"The air smells damp and feel moisty in your nostrils.\n");
   add_cmd_item("touch",({"wall","walls","rock wall","rock walls"}),
		"The walls are dripping from water and your hand get wet.\n");

   add_exit(PATH + "ll8.c","west",0,1);
   add_exit(PATH + "ll10.c","east",0,1);
   set_noshow_obvious(1);

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,-2);

return;
}


/* 	Function returns different things wether or not the player 
 *  	is a dwarf 	
 */

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return"The tunnel leads to the east and up to the west. You " +
	      "notice that the ground is flat here.\n"; 
	
   return"The tunnel leads to the east and west.\n";
}