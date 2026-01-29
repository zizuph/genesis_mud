/*
   Wayreth. Wizard Sleeping Quarters

   wizsleep.c
   -----------

   Coded ........: February 1997
   By ...........: Kentari

   Latest update : April 1997
   By........... : Kentari

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;


public void
create_tower_room()
{
   set_short("Wizard Sleeping Quarters");
   set_long("Separated from the raucous apprentice bunks, " +
	"these are the sleeping quarters for the full Wizards " +
	"of Wayreth Tower. All types of beds are evident, from " +
	"hard cots, to plush feather beds, and even some strange, "+
	"water-filled beds. The exit is south through the curtain.\n"); 
	
   AI(({"curtain","large curtain","middle","red black and white curtain"}),
	"Patterned with the three colors of the magic orders, this " +
	"curtain separates the chamber from the apprentice bunks, " +
	"giving the privacy and respect due to full mages of Wayreth Tower.\n");

   add_exit(WTOWER + "bunks", "south", 0);
   add_prop(OBJ_I_LIGHT, 2);
}

public int
query_start_room() 
{
	return 1;
}

