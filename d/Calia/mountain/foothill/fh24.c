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
    make_the_room("\n", "north", 0, 1);

    add_exit(FOOTHILL+"fh13", "north");
    add_exit(FOOTHILL+"fh14", "northeast");
    add_exit(FOOTHILL+"fh25", "east");
    add_exit(FOOTHILL+"fh23", "west");
    add_exit(FOOTHILL+"fh12", "northwest");
}
