/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 20/7/95

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

void
create_room()
{
    make_the_room("\n", "northwest", 1, 1);

    add_exit(FOOTHILL+"fh32", "north");
    add_exit(FOOTHILL+"fh33", "northeast");
    add_exit(FOOTHILL+"fh43", "east");
    add_exit(FOOTHILL+"fh51", "southeast");
    add_exit(FOOTHILL+"fh50", "south");
    add_exit(FOOTHILL+"fh49", "southwest");
    add_exit(FOOTHILL+"fh41", "west");
    add_exit(FOOTHILL+"fh31", "northwest");
}
