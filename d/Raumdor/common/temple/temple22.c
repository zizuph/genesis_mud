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
      "You stand right at the base of the great stone statue in the center " +
      "of this round chamber. The air is cold and damp, and smelling of " +
      "death and decay. Only the torches around the room light up this " +
      "otherwise dark and dismal place. To the south you see an archway that " +
      "leads into another large chamber.\n");
    add_item(({"statue"}),
      "This is a statue of an awful looking demon. It looks humanoid, only " +
      "it has four arms. Its head is that of a skull. In each hand it holds " +
      "a likeness of a human severed head. From its back sprouts nasty " +
      "looking wings, and it has a spiked tail.\n");
    add_item(({"archway"}),
      "It leads to the another large chamber. At the top you see a carving " +
      "of a grim-looking skull.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_exit(TEMPLE_DIR + "temple24", "north", 0);
    add_exit(TEMPLE_DIR + "temple23", "east", 0);
    add_exit(TEMPLE_DIR + "temple19", "south", 0);
    add_exit(TEMPLE_DIR + "temple21", "west", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
