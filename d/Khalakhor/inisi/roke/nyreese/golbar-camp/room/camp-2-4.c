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
    
    add_extra("A large cliff stands to the north and east, " +
              "providing natural protection to the camp.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(3));
    
    add_exit(CAMP_ROOM + "camp-1-3", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-3", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-3", "southwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-4", "south", 0, 0, 0);
    
    add_exit(CAMP_ROOM + "camp-3-2", "south", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-1", "southwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-1", "west", 0, 0, 0);

    add_item("cliff",
             "It's a steep cliff, impossible to climb.\n");
}