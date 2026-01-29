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
    
    add_extra("A barricade stands to the west and south, with an exit out from " +
              "camp to the southwest.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(1));

    add_exit(CAMP_ROOM + "camp-3-1", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-2", "north", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-3", "northeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-3", "east", 0, 0, 0);

    add_exit(CAMP_ROOM + "path-sw-2", "southwest", 0, 0, 0);

    add_item("barricade",
             "It's sturdy built, protecting the camp from intruders.\n");
    add_item("exit",
             "A simple exit in the barricade to the southwest.\n");
}