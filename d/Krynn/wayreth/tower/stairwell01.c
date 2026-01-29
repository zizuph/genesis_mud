/*
   Wayreth. Stairwell in tower.

   stairwell01.c
   -------------

   Coded ........: 95/06/01
   By ...........: Jeremiah

   Latest update : 95/06/14
   By ...........: Jeremiah

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;


void
create_tower_room()
{
   set_short("Stairwell on the first level in tower");
   set_long("You are standing at the foot of a spiral stair in a small " +
            "circular stairwell. The spiral stair rotates upwards " +
            "around the center of the room, thus each step reaches " +
            "from the wall and to the center of the room. There is an " +
            "opening to your southeast to a small chamber. The stairs lead " +
            "up further into the tower.\n"); 

   set_wall_type(3);

   add_item(({"stair", "stairs"}), "The stairs are carved from the same " +
            "dark obsidian as the tower itself. Each step reaches from " +
            "the wall and to the center of the stairwell, around which " +
            "the spiral stair rotates.\n");

   add_item(({"step", "steps"}), "Steps carved of dark obsidian. The " +
            "steps are very wide at the wall and narrows towards the " +
            "center of the room.\n");

   add_item(({"opening","chamber","small chamber"}), 
            "An opening to your southeast leads to a small chamber.\n");
   
   add_exit(WTOWER + "foretower", "southeast", 0);
   add_exit(WTOWER + "stairwell02", "up", 0);
}
