/*
   Pax Tharkas, Ground level, Reception room.

   reception.c
   -----------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/07/27
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
   set_short("Reception room");
   set_long("You are standing in a large room. The room is furnitured " +
            "with several tables, dispersed around the room. At each " +
            "table there's a couple of chairs. In the northwest corner " +
            "there's a huge fireplace. Some chairs are standing " +
            "in a half circle facing the fireplace. There is no " +
            "fire in the fireplace.\n");
	
   INSIDE;

   add_item(({"table", "tables"}), "Wooden tables standing around " +
            "the room. At each table there's a couple of chairs.\n");

   add_item(({"chair", "chairs"}), "These are plain wooden chairs. " +
            "most of them are placed next to the tables in this room. " +
            "Some of them are standing in a half circle near the " +
            "large fireplace. The ones who placed them there " +
            "probably did it to warm themselves by the fire.\n");

   add_item("fireplace", "This is a large fireplace. A thick layer " +
            "of soot covers the inside of the fireplace. The remains " +
            "of a fire lie in here. The fireplace and the remains " +
            "are cold. It has probably been a while since there was " +
             "a fire in this fireplace.\n");



   add_exit(GROUND_LEVEL + "corridor4", "east", 0);
   add_exit(GROUND_LEVEL + "corridor6", "south",0);
}


