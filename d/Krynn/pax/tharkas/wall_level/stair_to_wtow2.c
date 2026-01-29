/*
   Pax Tharkas, Ground level, stairs to the parapets of the western tower.

   stair_to_wtow2.c
   ----------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/07/28
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
inherit PAXINROOM;

void
create_pax_room()
{
   add_the_lamp();

   set_short("Landing");
   set_long("You are standing on a wide landing between two " +
            "stairwells. One leading up, and the other leading down. " +
            "The walls and stairs look as if they were made of solid " +
            "rock. A draft is coming from above. On the wall a small " +
            "iron lamp flickers with a pale light.\n");

   INSIDE;

   add_item(({"stair", "stairs"}), "These are solid stone stairs. The " +
            "stones of which this stair is build are fitted very " +
            "tightly together, making the stair look as if it were " +
            "carved out of one piece rock.\n");

   add_exit(WALL_LEVEL + "stair_to_wtow3", "up", 0, 1);
   add_exit(WALL_LEVEL + "stair_to_wtow1", "down", 0);
} 

