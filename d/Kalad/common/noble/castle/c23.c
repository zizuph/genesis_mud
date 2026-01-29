// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You find yourself walking along the cold, stone "+
    "corridors of the Castle of the High-Lord. The ground is "+
    "covered with a red carpet, and the walls are decorated with "+
    "simple wooden torches. This hallways continues both north and "+
    "south.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls casting light.\n");

    add_exit(NOBLE + "castle/c18", "north", 0, 0);
    add_exit(NOBLE + "castle/c28", "south", 0, 0);
}
