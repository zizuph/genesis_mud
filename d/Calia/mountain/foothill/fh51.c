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
    make_the_room("\n", "west", 0, 1);

    add_exit(FOOTHILL+"fh43", "north");
    add_exit(FOOTHILL+"fh44", "northeast");
    add_exit(FOOTHILL+"fh57", "south");
    add_exit(FOOTHILL+"fh56", "southwest");
    add_exit(FOOTHILL+"fh50", "west");
    add_exit(FOOTHILL+"fh42", "northwest");

    reset_room();
}
