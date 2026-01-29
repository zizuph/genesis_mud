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
    
    add_extra("A large cliff stands to the east running in north-south direction, " +
              "providing natural protection to the camp. To the north a barricade " +
              "has been setup.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(2));

    add_exit(CAMP_ROOM + "camp-1-2", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-3", "south", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "southwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-4", "southeast", 0, 0, 0);

    add_item("cliff",
             "It's a steep cliff, impossible to climb.\n");
    add_item("barricade",
             "It's sturdy built, protecting the camp from intruders.\n");
}