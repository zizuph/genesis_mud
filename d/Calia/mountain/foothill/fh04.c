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
    make_the_room("\n", "north", 2, 1);

    add_exit(FOOTHILL+"fh05", "east");
    add_exit(FOOTHILL+"fh14", "southeast");
    add_exit(FOOTHILL+"fh13", "south");
    add_exit(FOOTHILL+"fh12", "southwest");
    add_exit(FOOTHILL+"fh03", "west");
}
