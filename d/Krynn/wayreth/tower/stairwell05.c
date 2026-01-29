/*
   Wayreth. Stairwell in tower.

   stairwell05.c
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
   set_short("Stairwell on the fifth level of the tower");
   set_long("You are standing on a landing in a small circular " +
            "stairwell. The spiral stair spins its way upwards, further " +
            "into the tower, and downwards, towards the lower levels. " +
            "The stair rotates around the center of the stairwell, thus " +
            "each step reaches from the wall and to the center of the " +
            "room. There is a doorway leading west.\n");

   set_wall_type(3);

   add_item(({"stair", "stairs"}), "The stairs are carved from the same " +
            "dark obsidian as the tower itself. Each step reaches from " +
            "the wall and to the center of the stairwell, around which " +
            "the spiral stair rotates.\n");

   add_item(({"step", "steps"}), "Steps carved of dark obsidian. The " +
            "steps are very wide at the wall and narrows towards the " +
            "center of the room.\n");

   add_item("doorway", "A doorway leading west, giving access to " +
            "whatever lies on this level of the tower. There is a very " +
            "vague shimmering in the air, screening the doorway.\n");

   add_exit(WTOWER + "lobby", "west", "@@pass_check");
   add_exit(WTOWER + "stairwell06", "up", "@@pass_check");
   add_exit(WTOWER + "stairwell04", "down", 0);
}
