// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object ob;

void reset_room();

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    set_long("You now stand at the corner of the hallway. The "+
        "hall here bends to the east alongside the south wall of the "+
        "castle. There is a small wooden stand in the corner underneath "+
        "a window in the wall. A spiral staircase also leads up here "+
        "to the guard towers.\n");

    INSIDE;

    add_item("staircase","The staircase is made of black wood.\n");
    add_item("window","The small window lets in light. You can see "+
        "the royal gardens through it.\n");
    add_item(({"stand","wooden stand"}),"This small wooden stand "+
        "supports a vase with a flower.\n");
    add_item("vase","The vase is made of blue crystal, and a "+
        "beautiful flower pokes out of the top.\n");
    add_item("flower","The flower is a violet rose, dark in the "+
        "center, and light at the edges of the petals.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c28", "north", 0, 0);
    add_exit(NOBLE + "castle/c34", "east", 0, 0);
    add_exit(NOBLE + "castle/c68", "up", 0, 0);

    reset_room();
}


void
reset_room()
{ 
    ob = clone_npcs(ob, NOBLE + "npc/castle_guard");
}

