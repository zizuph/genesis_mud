 /*
  * Room in the northern path to the camp
  */
#pragma strict_types
  
#include "defs.h"

inherit PATH_BASE;

void
create_room()
{
    ::create_room();
    
    add_extra("The path continues to the east and from the northwest you hear a bustling noise of people.\n");

    add_exit(NYREESEDIR + "cadu_p4", "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM + "path-n-1", "east", 0, 0, 1);

    add_npc(CAMP_NPC + "camp-scout-1", 1, &->set_me_up());
    add_npc(CAMP_NPC + "camp-scout-2", 1, &->set_me_up());
}