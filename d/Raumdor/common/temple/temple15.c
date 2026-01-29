/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Square chamber of a morbid temple");
    set_long(
      "You stand in the center of a grand chamber. It is square in shape, " +
      "with pillars lining the sides of the room. At the very front, there " +
      "is an exit to another chamber, while to the east and west are exits " +
      "leading into hallways. The walls are lined with torches that cast " +
      "dark, long shadows across the chamber. The walls are all made of " +
      "black stone. The ceiling soars high into the air, and you can see " +
      "ugly little gargoyles hanging from there. The air here stinks with " +
      "death and decay.\n");
    add_item(({"pillars"}),
      "They support the high celing. They are also decorated with a carving " +
      "of a grim-looking skull.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_item(({"gargoyles"}), "Ugly little bastards.\n");
    add_exit(TEMPLE_DIR + "temple19", "north", 0);
    add_exit(TEMPLE_DIR + "temple14", "west", 0);
    add_exit(TEMPLE_DIR + "temple16", "east", 0);
    add_exit(TEMPLE_DIR + "temple10", "south", 0);
    
    add_npc(REGULAR_DKNIGHT, 3);
}
