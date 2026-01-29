/* Khiraa Dungeon, Sarr */
#include "defs.h"
inherit DUNGEON_DIR + "dungeon_room";

void
create_room()
{
    ::create_room();
    set_short("A dark dungeon");
    set_long(
      "This is a small, dingy dirty old cell. The walls are made of stone, " +
      "and in some spots you see dried blood. There is a small bench here, " +
      "and some old shackles on the wall.\n");

    add_item(({"bench"}),
      "A rotting piece of wood, cracking and splitting in some places.\n");
    add_item(({"shackles"}), "They are old and rusted.\n");

    clone_object(DUNGEON_OBJ_DIR + "gate_2_inner")->move(TO);
}
