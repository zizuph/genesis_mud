/*
   Pax Tharkas, Wall level, Stairway to tower, and exit to wall 
   battlements 

   stairwell.c
   -----------

   Coded ........: 95/02/15
   By ...........: Jeremiah

   Latest update : 95/04/07
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
inherit PAXINROOM;

create_pax_room()
{
   add_the_lamp();

   set_short("stairwell");
   set_long("You are standing on a wide landing. A stairwell leads " +
            "up from here. The dark cold stone walls feels even " +
            "colder in the draft coming from above. A small oil lamp " +
            "shines with a vague flickering light.\n");

   INSIDE;

   add_item(({"stair", "stairs", "stairwell"}), "A flight of stone " +
            "stairs leads upwards to a higher level of the tower.\n");


   add_exit(WALL_LEVEL + "gallery4", "east", 0);
   add_exit(WALL_LEVEL + "stair_to_etow1", "up", 0, 1);
}      


