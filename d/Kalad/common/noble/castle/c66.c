// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object  *guard = allocate(3);

void reset_room();

void
create_noble_room()
{
    set_short("The guards' barracks");
    set_long("These are the unusually lavish 'barracks' of the "+
        "castle guards. The floor is made of polished pine wood, with "+
        "sections of it covered in lush fur rugs. The ceiling has a "+
        "large window in it, letting the Kalad sun shine through. The "+
        "east half of the wall is lined with chests and dressers. The "+
        "room is dotted with comfortable looking cots. A stuffed "+
        "dummy stands here.\n");

    INSIDE;

    add_item("dummy","The dummy is shaped like a dwarf; short, "+
        "fat and bearded. There are numerous holes in it.\n");
    add_item("floor","The floor is very clean.\n");
    add_item("rugs","The rugs are made of valuable furs.\n");
    add_item("window","You can see the blue sky and the yellow, hot "+
        "sun through it. A bird flies by overhead.\n");
    add_item("chests","The chests are all locked, but you suspect they "+
        "contain the possessions of the different guards here.\n");
    add_item("dressers","They have various bits of clothes and armour "+
        "in them.\n");
    add_item("cots","The cots have big fluffy pillows as well as "+
        "cozy white sheets.\n");

    add_exit(NOBLE + "castle/c61", "north", 0, 0);

    reset_room();
}

void
reset_room()
{
    guard = clone_npcs(guard, NOBLE + "npc/castle_guard");
    guard[0]->team_join(guard[1]);
    guard[0]->team_join(guard[2]);
}
