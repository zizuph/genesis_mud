/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 20/7/95

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

object goat;

void
reset_room()
{
    if (!goat) {
        goat = clone_object(MOUNTAIN_MONSTERS+"m_goat");
        goat->move_living("M", this_object());
        tell_room(this_object(), QCTNAME(goat) + " arrives.\n");
    }
}


void
create_room()
{
    make_the_room("\n", "north", 1, 1);

    add_exit(FOOTHILL+"fh05", "north");
    add_exit(FOOTHILL+"fh06", "northeast");
    add_exit(FOOTHILL+"fh15", "east");
    add_exit(FOOTHILL+"fh26", "southeast");
    add_exit(FOOTHILL+"fh25", "south");
    add_exit(FOOTHILL+"fh24", "southwest");
    add_exit(FOOTHILL+"fh13", "west");
    add_exit(FOOTHILL+"fh04", "northwest");

    reset_room();
}
