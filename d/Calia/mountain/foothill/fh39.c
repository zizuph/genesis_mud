/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 20/7/95

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

object cat;

void
reset_room()
{
    if (!cat) {
        cat = clone_object(MOUNTAIN_MONSTERS+"m_cat");
        cat->move_living("M", this_object());
        tell_room(this_object(), QCTNAME(cat) + " arrives.\n");
    }
}


void
create_room()
{
    make_the_room("\n", "northeast", 2, 1);

    add_exit(FOOTHILL+"fh30", "north");
    add_exit(FOOTHILL+"fh40", "east");
    add_exit(FOOTHILL+"fh48", "southeast");
    add_exit(FOOTHILL+"fh47", "south");
    add_exit(FOOTHILL+"fh46", "southwest");
    add_exit(FOOTHILL+"fh38", "west");
    add_exit(FOOTHILL+"fh29", "northwest");

    reset_room();
}
