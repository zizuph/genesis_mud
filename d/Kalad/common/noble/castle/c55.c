// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are now within a great hall that heads north "+
    "and south. You see many guards gathered to the north, while "+
    "south, you see nothing but the endless hallway. West, however, "+
    "you see a set of stairs leading down.\n");
    add_item("guards","They look to be royal guards of the Castle.\n");
    add_item("carpet","The red carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c50", "north", 0, 0);
    add_exit(NOBLE + "castle/c54", "west", 0, 0);
    add_exit(NOBLE + "castle/c60", "south", 0, 0);
}


