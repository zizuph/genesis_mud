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
    make_the_room("\n", "west", 1, 1);

    add_exit(FOOTHILL+"fh50", "north");
    add_exit(FOOTHILL+"fh51", "northeast");
    add_exit(FOOTHILL+"fh57", "east");
    add_exit(FOOTHILL+"fh63", "southeast");
    add_exit(FOOTHILL+"fh62", "south");
    add_exit(FOOTHILL+"fh61", "southwest");
    add_exit(FOOTHILL+"fh55", "west");
    add_exit(FOOTHILL+"fh49", "northwest");
}
