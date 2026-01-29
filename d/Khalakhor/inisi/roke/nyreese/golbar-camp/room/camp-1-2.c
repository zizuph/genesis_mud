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
    
    add_extra("A barricade runs north and west of here, to create a shield "+
              "against intruders.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(2));

    add_exit(CAMP_ROOM + "camp-1-3", "east", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-3", "southeast", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-2", "south", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-2-1", "southwest", 0, 0, 0);
    
    add_item("barricade",
             "It's sturdy built, protecting the camp from intruders.\n");
}