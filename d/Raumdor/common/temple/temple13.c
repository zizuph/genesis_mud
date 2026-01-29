/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Alcove of a morbid temple");
    set_long(
      "You are in a small little alcove shadowed in darkness. A single torch " +
      "burns on the wall here.\n");
    add_item(({"torch"}), "It lights the small area.\n");
    add_exit(TEMPLE_DIR + "temple14", "east", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}

