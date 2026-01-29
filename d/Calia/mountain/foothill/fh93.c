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
    make_the_room("\n", "southwest", 1, 1);

    add_exit(FOOTHILL+"fh84", "north");
    add_exit(FOOTHILL+"fh85", "northeast");
    add_exit(FOOTHILL+"fh94", "east");
    add_exit(FOOTHILL+"fh105", "southeast");
    add_exit(FOOTHILL+"fh104", "south");
    add_exit(FOOTHILL+"fh103", "southwest");
    add_exit(FOOTHILL+"fh92", "west");
    add_exit(FOOTHILL+"fh83", "northwest");
}
