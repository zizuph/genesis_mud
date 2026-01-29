// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a kitchen of the Castle of the High-Lord");
    INSIDE;
    set_long("You now find yourself in a smoke-filled room. "+
    "The ground here is bare, and you see many stains and "+
    "food debris. The kitchen is massive, and stretches all "+
    "the way to the west. Here, there are many storage "+
    "barrels and sacks of sugar and salt. The ground is littered "+
    "with trash and scraps of food, and there are rats running "+
    "around eating them.\n");
    add_item("barrels","Large wooden barrels full of stuff.\n");
    add_item("sacks","They are huge burlap sacks of cooking "+
    "materials.\n");
    add_item("ground","It is a mess.\n");
    add_item("rats","Squeek!\n");

    add_exit(NOBLE + "castle/c13", "north", 0, 0);
    add_exit(NOBLE + "castle/c22", "south", 0, 0);
    add_exit(NOBLE + "castle/c16", "west", 0, 0);
}


