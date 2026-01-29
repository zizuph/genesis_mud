 /*
  * Room in the Golbar camp.
  * Rooms are named 'camp-<row>-<column>'
  *
  * Center of the camp, exit to leader's tent
  */
#pragma strict_types
  
#include <macros.h>
#include "defs.h"

inherit CAMP_BASE;

/*
* Checks if the guard is present and will block the player,
* or if it's possible to enter the leader's tent.
*/
int
block()
{
    object guard = present("guard");
    if (guard && CAN_SEE(guard, TP))
    {
        write("The guard stops you from entering the tent.\n");
        return 1;
    }
    return 0;
}

void
create_room()
{
    ::create_room();
    
    add_extra("To the northeast a cliff cuts into the camp and rises above you, " +
              "creating a natural protection to the camp in that direction. A " +
              "larger fire is setup here and just beside the fire there is a larger tent. " +
              "It is probably the leader's tent.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(3));
    add_npc(CAMP_NPC + "campguard", 1, &->set_me_up(0));

    add_exit(CAMP_ROOM + "camp-1-2", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-1-3", "north", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-4", "east", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-2", "southwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-3", "south", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-4", "southeast", 0, 0, 0);

    add_exit(CAMP_ROOM + "tent", "tent", "@@block", 0, 0);

    add_prop(OBJ_I_HAS_FIRE, 1);

    add_item(({"fire", "campfire", "large fire"}),
             "It's a really large fire, providing warmth and light to the " +
             "entire centre of the camp.\n");
    add_item(({"tent", "large tent"}),
             "The large tent is different than the smaller tents in the camp. " +
             "Taller, wider and thicker canvas. Clearly belongs to the leader " +
             "of the camp.\n");
    add_item("cliff",
             "It's a steep cliff, impossible to climb.\n");
}

void
init()
{
  ::init();
}