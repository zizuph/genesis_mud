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
    
    //add_extra("The extra...\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(2));
    
    add_exit(CAMP_ROOM + "camp-3-2", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-3", "north", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-4", "northeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-4", "east", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-4", "southeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-3", "south", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-2", "southwest", 0, 0, 0);
}