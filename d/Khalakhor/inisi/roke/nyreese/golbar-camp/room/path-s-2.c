 /*
  * Room in the south path to the camp
  */
#pragma strict_types
  
#include <macros.h>
#include "defs.h"

inherit PATH_BASE;

/*
* Checks if the guard is present and will block the player,
* or if it's possible to enter the camp.
*/
int
block()
{
    object guard = present("guard");
    if (guard && CAN_SEE(guard, TP))
    {
        write("The guard stops you from entering the camp.\n");
        return 1;
    }
    return 0;
}

void
create_room()
{
    ::create_room();
    
    add_extra("Someone has built a barricade here to prevent you from going north.\n" +
              "A small path leads south into the green surroundings.\n");

    add_item("barricade",
             "Its very well built. Only a professional squad could " +
             "do this.\n");

    add_npc(CAMP_NPC + "campguard", 1, &->set_me_up());
    add_exit(CAMP_ROOM + "path-s-1", "south", 0, 0, 1);
    add_exit(CAMP_ROOM + "camp-4-4", "north", "@@block", 0, 0);
}