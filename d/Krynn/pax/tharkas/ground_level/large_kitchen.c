/*
   Pax Tharkas, Ground level, large kitchen.

   large_kitchen.c
   ---------------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/07/28
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;


void
create_pax_room()
{
   set_short("large kitchen");
   set_long("You are standing in a large kitchen. Six large ovens are " +
            "lined up along the north wall. Large tables run along the " +
            "east and west walls. Most of this place is in a terrible " +
            "mess, not much has been done to keep this room clean. Stale " +
            "food covers parts of the tables and the floor. There's a " +
            "large circular hole in the floor in the northwest corner.\n"); 
	
   INSIDE;

   add_item(({"oven", "ovens"}), "The ovens are large iron cast ovens. " +
            "Each of them can be heated by lighting a fire in the lower " +
            "part of the it. The upper part is for preparing food. " +
            "The ovens are empty, but they look as if they're still in " +
            "use. Yuck! the ovens havn't been cleaned for quite a while. " +
            "The ones who eat the food prepared in here must have " +
            "have pretty strong stomachs.\n");

   add_item(({"table", "tables"}), "These are large featureless " +
            "tables running along the eastern and western wall. They " +
            "are filthy with leftovers from someone preparing food.\n");

   add_item("floor", "A solid stone floor. Stale food has been left " +
            "lying around. There's a large circular hole in the north" +
            "west part corner of the room.\n");

   add_item("hole", "It's a well! You can just vaguely distinguish the " +
            "surface of the water somewhere down in the dark. This well " +
            "probably supports the fortress with water during a siege.\n");


   add_exit(GROUND_LEVEL + "supply_room1", "south",0);
   add_exit(GROUND_LEVEL + "mess_hall2", "east", 0);
}



