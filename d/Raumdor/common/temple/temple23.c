/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Circular chamber of a morbid temple");
    set_long(
      "You stand to the east side of the great statue. The room smells " +
      "strongly of death and decay. The walls are made of some old black " +
      "stone. Torches line the walls casting light in this dank dark " +
      "place.\n");
    add_item(({"statue"}),
      "This is a statue of an awful looking demon. It looks humanoid, only " +
      "it has four arms. Its head is that of a skull. In each hand it holds " +
      "a likeness of a human severed head. From its back sprouts nasty " +
      "looking wings, and it has a spiked tail.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_exit(TEMPLE_DIR + "temple24", "northwest", 0);
    add_exit(TEMPLE_DIR + "temple22", "west", 0);
    add_exit(TEMPLE_DIR + "temple19", "southwest", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
