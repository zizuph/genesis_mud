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
    
    add_extra("A barricade runs on the west side and bends towards southeast.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(1));

    add_exit(CAMP_ROOM + "camp-2-1", "north", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "northeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-2", "east", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-2", "southeast", 0, 0, 0);

    add_item("barricade",
             "It's sturdy built, protecting the camp from intruders.\n");
}