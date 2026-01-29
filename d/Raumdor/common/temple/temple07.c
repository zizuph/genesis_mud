/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Circular chamber of a temple");
    set_long(
      "You stand to the east side of the great statue. The room smells " +
      "strongly of death and decay. The walls are made of some old black " +
      "stone. Torches line the walls casting light in this dank dark " +
      "place.\n");
    add_item(({"statue"}),
      "This is a figure wraped in black robes. As you look closer, is is " +
      "holding a staff in a skeletal hand. In the darkhood, you think you " +
      "can make out a rather grim-looking skull.\n");
    add_item(({"stairs"}), "They are to the south.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_exit(TEMPLE_DIR + "temple10", "northwest", 0);
    add_exit(TEMPLE_DIR + "temple06", "west", 0);
    add_exit(TEMPLE_DIR + "temple03", "southwest", 0);
    add_exit(TEMPLE_DIR + "temple04", "south", 0);
    clone_object(TEMPLE_OBJ_DIR + "eastern_door_outer")->move(TO, 1);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
