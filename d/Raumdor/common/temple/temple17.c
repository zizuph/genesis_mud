/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Hallway of a morbid temple");
    set_long(
      "You are in a short hallway leading south into a small chamber, and " +
      "west into a huge chamber. The walls are lined with torches that cast " +
      "shadows around everywhere. The stench of death and decay is strong " +
      "here, and even stronger to the south.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_exit(TEMPLE_DIR + "temple12", "south", 0);
    add_exit(TEMPLE_DIR + "temple16", "west", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
