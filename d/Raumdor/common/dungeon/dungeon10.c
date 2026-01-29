/* Khiraa Dungeon, Sarr */
#include "defs.h"
inherit DUNGEON_DIR + "dungeon_room";

void
create_room()
{
    ::create_room();
    set_short("A dark dungeon");
    set_long(
      "This certainly looks like a dungeon. The ceiling is dripping cold " +
      "water. The air is filled with a coldness that sinks into your bones. " +
      "You are overcome with a great feeling of despair that this place " +
      "radiates. The corridor continues down to the west.\n");

    add_exit(DUNGEON_DIR + "dungeon09", "west", 0);
    add_exit(PLAINS_DIR + "beastruin2", "up", 0);
}
