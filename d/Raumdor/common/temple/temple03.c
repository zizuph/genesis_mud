/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Circlular chamber of a morbid temple");
    set_long(
      "You stand in the lower part of this large circular chamber. In the " +
      "center, just to your north, is a large and intresting looking statue. " +
      "The air here is damp and gives you the chills. The stench of death is " +
      "strong. Further north, behind the statue, you see another passageway " +
      "leading into what looks like another chamber of some kind.\n");
    add_item(({"statue"}),
      "This is a figure wraped in black robes. As you look closer, is is " +
      "holding a staff in a skeletal hand. In its hood, you can make out a " +
      "rather grim-looking skull.\n");
    add_item("staff", "It is held by the statue.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_exit(TEMPLE_DIR + "temple01", "south", 0);
    add_exit(TEMPLE_DIR + "temple06", "north", 0);
    add_exit(TEMPLE_DIR + "temple05", "northwest", 0);
    add_exit(TEMPLE_DIR + "temple07", "northeast", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
