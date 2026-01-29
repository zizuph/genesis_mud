// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are at an intersection of halls. The "+
    "walls are cold and hard, and the smell of old "+
    "furniture fills the air. You walk on a red carpet "+
    "on the ground. There are a few torches on the wall here "+
    "as well. To the west, you see a set of stairs leading "+
    "up and around. To the south, the hall continues for "+
    "a long ways, and east is the bend in the hall.\n");
    add_item("stairs","They are grand white marble stairs "+
    "with oak railings.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c21", "east", 0, 0);
    add_exit(NOBLE + "castle/c25", "south", 0, 0);
    add_exit(NOBLE + "castle/c19", "west", 0, 0);
}
