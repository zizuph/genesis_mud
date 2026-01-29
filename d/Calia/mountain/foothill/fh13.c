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
    make_the_room("\n", "north", 1, 1);

    add_exit(FOOTHILL+"fh04", "north");
    add_exit(FOOTHILL+"fh05", "northeast");
    add_exit(FOOTHILL+"fh14", "east");
    add_exit(FOOTHILL+"fh25", "southeast");
    add_exit(FOOTHILL+"fh24", "south");
    add_exit(FOOTHILL+"fh23", "southwest");
    add_exit(FOOTHILL+"fh12", "west");
    add_exit(FOOTHILL+"fh03", "northwest");
}
