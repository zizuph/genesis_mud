/* Khiraa Dungeon, Sarr */
#include "defs.h"
inherit DUNGEON_DIR + "dungeon_room";

object npc;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("A dark dungeon");
    set_long(
      "You are in a corridor lined with cells. The air is damp, cold, and " +
      "filled with despair. Looking around, you pity the poor soul who ever " +
      "had to be trapped in here.\n");
    add_exit(DUNGEON_DIR + "dungeon08", "west", 0);
    add_exit(DUNGEON_DIR + "dungeon10", "east", 0);
    clone_object(DUNGEON_OBJ_DIR + "gate_1_outer")->move(TO);
    clone_object(DUNGEON_OBJ_DIR + "gate_2_outer")->move(TO);
    reset_room();
}

void
reset_room()
{
    if (!npc)
    {
        npc = clone_object(COMMON_NPC_DIR + "blord");
        npc->move_living("xxx", TO);
    }
}
