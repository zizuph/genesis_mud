/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 20/7/95

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

object g;

void
reset_room()
{
    if (!g) {
        g = clone_object(MOUNTAIN_MONSTERS+"gopheroo");
        g->move_living("M", this_object());
        tell_room(this_object(), QCTNAME(g) + " arrives.\n");
    }
}

void
create_room()
{
    make_the_room("\n", "southwest", 2, 1);

    add_exit(FOOTHILL+"fh82", "north");
    add_exit(FOOTHILL+"fh83", "northeast");
    add_exit(FOOTHILL+"fh92", "east");
    add_exit(FOOTHILL+"fh103", "southeast");
    add_exit(FOOTHILL+"fh81", "northwest");

    reset_room();
}
