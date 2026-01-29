 /*
  * Room in the Golbar camp.
  * Rooms are named 'camp-<row>-<column>'
  */
#pragma strict_types
  
#include "defs.h"

inherit CAMP_BASE;

void
create_room()
{
    ::create_room();
    
    add_extra("A barricade is next to you, with an exit west out from the camp.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(1));

    add_exit(CAMP_ROOM + "camp-1-2", "northeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "east", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-2", "southeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-1", "south", 0, 0, 0);
    
    add_exit(CAMP_ROOM + "path-n-6", "west", 0, 0, 0);

    add_item("barricade",
             "It's sturdy built, protecting the camp from intruders.\n");
    add_item("exit",
             "A simple exit in the barricade to the west.\n");
}