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
    set_long("You are at the end of a hall here. The hall branches "+
        "off to the east and west. To the north, the hall continues to "+
        "the center of the castle. There is a large window on the south "+
        "wall. The red carpet covers the ground.\n");

    INSIDE;

    add_item("window","You can make out the streets of the noble "+
        "district through this window.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c36", "east", 0, 0);
    add_exit(NOBLE + "castle/c30", "north", 0, 0);
    add_exit(NOBLE + "castle/c34", "west", 0, 0);

    reset_room();
}

void
reset_room()
{
    ob = clone_npcs(ob, NOBLE + "npc/castle_knight");
}

