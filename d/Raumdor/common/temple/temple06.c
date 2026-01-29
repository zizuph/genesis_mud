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
      "otherwise dark and dismal place. To the north you see an archway that " +
      "leads into another large chamber.\n");
    add_item(({"statue"}),
      "This is a figure wraped in black robes. As you look closer, is is " +
      "holding a staff in a skeletal hand. In the darkhood, you think you " +
      "can make out a rather grim-looking skull.\n");
    add_item(({"archway"}),
      "It leads to the another large chamber. At the top you see a carving " +
      "of a menacing skull.\n");
    add_exit(TEMPLE_DIR + "temple10", "north", 0);
    add_exit(TEMPLE_DIR + "temple07", "east", 0);
    add_exit(TEMPLE_DIR + "temple03", "south", 0);
    add_exit(TEMPLE_DIR + "temple05", "west", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
