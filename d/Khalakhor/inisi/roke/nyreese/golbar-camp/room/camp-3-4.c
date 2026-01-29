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
    
    add_extra("To the east a large cliff rise up, providing " +
              "natural protection to the camp.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(2));
    
    add_exit(CAMP_ROOM + "camp-3-3", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-3", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-4", "north", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-4", "south", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-3", "southwest", 0, 0, 0);

    add_item("cliff",
             "It's a steep cliff, impossible to climb.\n");
}