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
    
    add_exit(CAMP_ROOM + "camp-3-1", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-1", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "north", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-3", "northeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-3", "east", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-3", "southeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-4-2", "south", 0, 0, 0);
}