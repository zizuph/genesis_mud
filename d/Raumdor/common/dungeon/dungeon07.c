/* Khiraa Dungeon, Sarr */
#include "defs.h"
inherit DUNGEON_DIR + "dungeon_room";

void
create_room()
{
    ::create_room();
    set_short("A dark dungeon");
    set_long(
      "You are in a corridor lined with cells. The air is damp, cold, and " +
      "filled with despair. Looking around, you pity the poor soul who ever " +
      "had to be traped in here. It is dark and spooky.\n");

    add_exit(DUNGEON_DIR + "dungeon06", "west", 0);
    add_exit(DUNGEON_DIR + "dungeon08", "east", 0);
    clone_object(DUNGEON_OBJ_DIR + "gate_5_outer")->move(TO);
    clone_object(DUNGEON_OBJ_DIR + "gate_6_outer")->move(TO);
}
