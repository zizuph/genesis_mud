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
    
    add_extra("To the east a steep cliff rise up, and to the south " +
              "a barricade runs from the cliff and further to the west " +
              "with a small exit out from the camp to the south.\n");

    add_npc(CAMP_NPC + "campwarrior", 2, &->set_me_up(1));

    add_exit(CAMP_ROOM + "camp-4-3", "west", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-3", "northwest", 0, 0, 0);
    add_exit(CAMP_ROOM + "camp-3-4", "north", 0, 0, 0);

    add_exit(CAMP_ROOM + "path-s-2", "south", 0, 0, 0);

    add_item("cliff",
             "It's a steep cliff, impossible to climb.\n");
    add_item("barricade",
             "It's sturdy built, protecting the camp from intruders.\n");
             add_item("exit",
                      "A simple exit in the barricade to the south.\n");
}