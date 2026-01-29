/*

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

   add_exit(WTOWER + "test/test1", "down", 0);
}
