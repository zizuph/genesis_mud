/*
   Wayreth. Stairwell in tower.

   stairwell09.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/06/14
   By ...........: Jeremiah

*/

#include "../guild.h"
inherit TOWERROOM;

void
create_tower_room()
{
   set_short("Stairwell on the ninth level in the tower");
   set_long("You are standing on a spiral stair in a small circular " +
            "stairwell. The spiral stair rotates upwards, and downwards, " +
            "around the center of the stairwell, thus each step reaches " +
            "from the wall and to the center of the room. The stairs " +
            "lead up and down.\n");

   set_wall_type(3);

   add_item(({"stair", "stairs"}), "The stairs are carved from the same " +
            "dark obsidian as the tower itself. Each step reaches from " +
            "the wall and to the center of the stairwell, around which " +
            "the spiral stair rotates.\n");

   add_item(({"step", "steps"}), "Steps carved of dark obsidian. The " +
            "steps are very wide at the wall and narrows towards the " +
            "center of the room.\n");

   add_exit("stairwell10", "up", 0);
   add_exit("stairwell08", "down", 0);
}
