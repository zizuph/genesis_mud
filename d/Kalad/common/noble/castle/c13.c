// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You now stand on the soft, red carpet that covers "+
    "this long hall leading south into a room. The walls have torches on "+
    "them to give light when needed. The walls here are "+
    "adorned with serene paintings. To the south, "+
    "you can see and hear the sounds and smells of cooking.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");
    add_item("paintings","The paintings depict scense of "+
    "the wilderness.\n");

    add_exit(NOBLE + "castle/c8", "north", 0, 0);
    add_exit(NOBLE + "castle/c17", "south", 0, 0);
}


